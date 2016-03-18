/*
 * ClientRecorder.cpp
 * Client receive position and orientation data from motive and record it
 * Based on NatNetLinux
 * Xinke Deng(UIUC)
 * 2015.1.14
 */

#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <iostream>
#include <sstream>
#include <iterator>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include <time.h>

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <NatNetLinux/NatNet.h>
#include <NatNetLinux/CommandListener.h>
#include <NatNetLinux/FrameListener.h>

#include <boost/program_options.hpp>
#include <time.h>
#include "./include/Utilities/RMS_Utils_Basics.hpp"
#include "./include/Utilities/RMS_Utils_Time.hpp"

using namespace std;

/********** Globals **********/
float pos_x, pos_y, pos_z, roll, pitch, yaw;
float QuadDesiredx, QuadDesiredy, QuadDesiredz;
/******** End Globals ********/





/******** DataLog **********/
int num_sample = 60;
vector<vector<double> > var_his;
vector<int64_t> time_his;
int sample_iter = 0;
int display_iter = 0;
ofstream output_file;
int64_t timestamp = 0;

Robots::Time Timer;

void log_data()
{
  time_his.push_back(timestamp);
    
  var_his.push_back(vector<double>());

  var_his[sample_iter].push_back(pos_x);
  var_his[sample_iter].push_back(pos_y);
  var_his[sample_iter].push_back(pos_z);
  var_his[sample_iter].push_back(roll);
  var_his[sample_iter].push_back(pitch);
  var_his[sample_iter].push_back(yaw);
  sample_iter++;
      
}

void log_write()
{
  if(sample_iter == num_sample)
    {
      cout<<"output data"<<endl;
      for(int i=0; i<num_sample; i++)
      	{
	  output_file<<time_his.at(i)<<" ";
      	  ostream_iterator<double> output_iterator(output_file," ");
      	  copy(var_his[i].begin(),var_his[i].end(),output_iterator);
      	  output_file << endl;
      	}
      var_his.clear();
      sample_iter = 0;      
    }
  
}
/***** End DataLog *********/



class Globals
{
public:
   
   // Parameters read from the command line
   static uint32_t localAddress;
   static uint32_t serverAddress;
   
   // State of the main() thread.
   static bool run;
};
uint32_t Globals::localAddress = 0;
uint32_t Globals::serverAddress = 0;
bool Globals::run = false;

#define PI_f 3.14159265f
#define PI   3.14159265

//Transform Quaternions to Euler angles
void Planner_Quat2Euler_f(Quaternion4f& quat_param, Euler& euler_param)
{
	//variables
	float sqw = quat_param.qw*quat_param.qw;
    float sqx = quat_param.qx*quat_param.qx;
    float sqy = quat_param.qy*quat_param.qy;
    float sqz = quat_param.qz*quat_param.qz;
	float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor

	//singularity tests
	float test = quat_param.qx*quat_param.qy + quat_param.qz*quat_param.qw;
	if (test > 0.499*unit) { // singularity at north pole
		euler_param.pitch = 2 * atan2f(quat_param.qx,quat_param.qw);
		euler_param.yaw = PI_f/2;
		euler_param.roll = 0;
		return;
	}
	if (test < -0.499*unit) { // singularity at south pole
		euler_param.pitch = -2 * atan2f(quat_param.qx,quat_param.qw);
		euler_param.yaw = -PI_f/2;
		euler_param.roll = 0;
		return;
	}

	//no singularity
    euler_param.pitch = atan2f(2*quat_param.qy*quat_param.qw-2*quat_param.qx*quat_param.qz , sqx - sqy - sqz + sqw);
	euler_param.yaw = asinf(2*test/unit);
	euler_param.roll = atan2f(2*quat_param.qx*quat_param.qw-2*quat_param.qy*quat_param.qz , -sqx + sqy - sqz + sqw);
}




// End the program gracefully.
void terminate(int)
{
   // Tell the main() thread to close.
   Globals::run = false;
   ros::shutdown();
   exit(0);
}

// Set the global addresses from the command line.
void readOpts( int argc, char* argv[] )
{
   namespace po = boost::program_options;
   
   po::options_description desc("simple-example: demonstrates using NatNetLinux\nOptions");
   desc.add_options()
      ("help", "Display help message")
      ("local-addr,l", po::value<std::string>(), "Local IPv4 address")
      ("server-addr,s", po::value<std::string>(), "Server IPv4 address")
   ;
   
   po::variables_map vm;
   po::store(po::parse_command_line(argc,argv,desc), vm);
   
   if(
      argc < 5 || vm.count("help") ||
      !vm.count("local-addr") ||
      !vm.count("server-addr")
   )
   {
      std::cout << desc << std::endl;
      exit(1);
   }
   
   Globals::localAddress = inet_addr( vm["local-addr"].as<std::string>().c_str() );
   Globals::serverAddress = inet_addr( vm["server-addr"].as<std::string>().c_str() );
}

// This thread loop just prints frames as they arrive.
void ReceiveFrames(FrameListener& frameListener, ros::Publisher pub_mocap_data)
{
   bool valid;
   MocapFrame frame;
   Globals::run = true;
   geometry_msgs::PoseWithCovarianceStamped msg;

   while(Globals::run)
   {
      while( true )
      {
         // Try to get a new frame from the listener.
         MocapFrame frame(frameListener.pop(&valid).first);
         // Quit if the listener has no more frames.
         if( !valid )
            break;
            
            
	 //Combination with ACI
         RigidBody quadrotor = frame.rigidBodies().at(0);
         
         Point3f quad_loc = quadrotor.location();
         Quaternion4f quad_qtn = quadrotor.orientation();
         Quaternion4f quad_qtn_real;
         Euler euler_cur, euler_real;
         
         quad_loc.x = quadrotor.location().z;
         quad_loc.y = -quadrotor.location().x;
         quad_loc.z = -quadrotor.location().y;
         
         quad_qtn_real.qx = quad_qtn.qz;
         quad_qtn_real.qy = -quad_qtn.qx;
         quad_qtn_real.qz = -quad_qtn.qy;
         quad_qtn_real.qw = quad_qtn.qw;
         
         Planner_Quat2Euler_f(quad_qtn_real, euler_real);
         
         pos_x = quad_loc.x;
         pos_y = quad_loc.y;
         pos_z = quad_loc.z;
         roll = euler_real.roll;
         pitch = euler_real.pitch;
         yaw = euler_real.yaw;
         msg.pose.pose.position.x = pos_x;
         msg.pose.pose.position.y = pos_y;
         msg.pose.pose.position.z = pos_z;
         msg.pose.pose.orientation.x = quad_qtn.qx;
         msg.pose.pose.orientation.y = quad_qtn.qy;
         msg.pose.pose.orientation.z = quad_qtn.qz;
         msg.pose.pose.orientation.w = quad_qtn.qw;
         msg.header.seq ++;
         ros::Time temp_t = ros::Time::now();
         msg.header.stamp.sec = temp_t.sec;
         msg.header.stamp.nsec = temp_t.nsec;

         pub_mocap_data.publish(msg);
         QuadDesiredx = 0;
         QuadDesiredy = 0;
         QuadDesiredz = -1;
         //std::cout << "Position: " << pos_x << " " << pos_y << " " << pos_z << std::endl; 
         //std::cout << "Orientation: " << roll << " " << pitch << " " << yaw << std::endl;

         //std::cout << "Position: " << pos_x <<"  lalala"<<ros::Time::now()<< std::endl;
         //ROS_INFO_STREAM("msg's pose.position.x is"<<msg.pose.pose.position.x);

	 timestamp = Timer.timestamp();
         //publish data here
	 


	 //log_data();
	 //log_write();
         
         std::cout << euler_real.roll << " " << euler_real.pitch << " "  << euler_real.yaw << std::endl;
         
      }
      
      
      // Sleep for a little while to simulate work :)
      usleep(1000);
   }
}


int main(int argc, char* argv[])
{
  // Initialization
  ros::init(argc, argv, "pub_mocap_data");
  ros::NodeHandle nh;
  ros::Publisher pub_mocap_data = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("pub_mocap_data/data", 1000); 
  pos_x = 0;
  pos_y = 0;
  pos_z = 0;
	
  roll = 0;
  pitch = 0;
  yaw = 0;
  
  /*************************** Data Log ****************************/
  //Create the name of data log
  /*char text[200];
  time_t now  = time(NULL);
  struct tm *t  = localtime(&now);
  strftime(text,sizeof(text)-1,"%Y%m%d-%H%M%S",t);
  ostringstream fn;
  fn << "./" << text << ".txt";
  string filename = fn.str();

  // Convert string to char array
  char* fnstr  = new char[filename.size()+1];
  fnstr[filename.size()] = 0;
  memcpy(fnstr,filename.c_str(),filename.size());
  output_file.open(fnstr);
  * /
  /************************** End Data Log *************************/

	
  // Version number of the NatNet protocol, as reported by the server.
  unsigned char natNetMajor;
  unsigned char natNetMinor;
  
  // Sockets
  int sdCommand;
  int sdData;
   
  // Catch ctrl-c and terminate gracefully.
  signal(SIGINT, terminate);
  
  // Set addresses
  readOpts( argc, argv );
  // Use this socket address to send commands to the server.
  struct sockaddr_in serverCommands = NatNet::createAddress(Globals::serverAddress, NatNet::commandPort);
  
  // Create sockets
  sdCommand = NatNet::createCommandSocket( Globals::localAddress );
  sdData = NatNet::createDataSocket( Globals::localAddress );
  
  // Start the CommandListener in a new thread.
  CommandListener commandListener(sdCommand);
  commandListener.start();
  
  // Send a ping packet to the server so that it sends us the NatNet version
  // in its response to commandListener.
  NatNetPacket ping = NatNetPacket::pingPacket();
  ping.send(sdCommand, serverCommands);
   
  // Wait here for ping response to give us the NatNet version.
  commandListener.getNatNetVersion(natNetMajor, natNetMinor);
   
  // Start up a FrameListener in a new thread.
  FrameListener frameListener(sdData, natNetMajor, natNetMinor);
  frameListener.start();
  
  // This infinite loop simulates a "worker" thread that reads the frame
  // buffer each time through, and exits when ctrl-c is pressed.
  ReceiveFrames(frameListener,pub_mocap_data);
  //timeStats(frameListener);
   
  // Wait for threads to finish.
  frameListener.stop();
  commandListener.stop();
  frameListener.join();
  commandListener.join();
  
  // Epilogue
  close(sdData);
  close(sdCommand);
  
  return 0;
}
