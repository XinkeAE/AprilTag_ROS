#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <iomanip> //for std::setprecision and std::fix

#include <iostream>
#include <sstream>
#include <iterator>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

using namespace std;


int num_sample = 60;
vector<vector<double> > var_his_mocap;
vector<vector<double> > var_his_apriltag;
vector<int64_t> time_his_mocap;
vector<int64_t> time_his_apriltag;
int sample_iter_mocap = 0;
int sample_iter_apriltag = 0;
ofstream output_file_mocap;
ofstream output_file_apriltag;


/************************Data log mocap***************************/
void log_data_mocap(const geometry_msgs::PoseWithCovarianceStamped & msg)
{
  time_his_mocap.push_back(msg.header.stamp.toSec() * 1.0e6);
    
  var_his_mocap.push_back(vector<double>());

  var_his_mocap[sample_iter_mocap].push_back(msg.pose.pose.position.x);
  var_his_mocap[sample_iter_mocap].push_back(msg.pose.pose.position.y);
  var_his_mocap[sample_iter_mocap].push_back(msg.pose.pose.position.z);
  var_his_mocap[sample_iter_mocap].push_back(msg.pose.pose.orientation.x);
  var_his_mocap[sample_iter_mocap].push_back(msg.pose.pose.orientation.y);
  var_his_mocap[sample_iter_mocap].push_back(msg.pose.pose.orientation.z);
  var_his_mocap[sample_iter_mocap].push_back(msg.pose.pose.orientation.w);

  sample_iter_mocap++;
      
}

void log_write_mocap()
{
  if(sample_iter_mocap == num_sample)
    {
      cout<<"output data"<<endl;
      for(int i=0; i<num_sample; i++)
      	{
	  	output_file_mocap<<time_his_mocap.at(i)<<" ";
      	  ostream_iterator<double> output_iterator(output_file_mocap," ");
      	  copy(var_his_mocap[i].begin(),var_his_mocap[i].end(),output_iterator);
      	  output_file_mocap << endl;
      	}
      var_his_mocap.clear();
      sample_iter_mocap = 0;      
    }
  
}
/********************* End DataLog mocap ***************************/


/************************Data log apriltag***************************/
void log_data_apriltag(const geometry_msgs::PoseWithCovarianceStamped & msg)
{
  time_his_apriltag.push_back(msg.header.stamp.toSec() * 1.0e6);
    
  var_his_apriltag.push_back(vector<double>());

  var_his_apriltag[sample_iter_apriltag].push_back(msg.pose.pose.position.x);
  var_his_apriltag[sample_iter_apriltag].push_back(msg.pose.pose.position.y);
  var_his_apriltag[sample_iter_apriltag].push_back(msg.pose.pose.position.z);
  var_his_apriltag[sample_iter_apriltag].push_back(msg.pose.pose.orientation.x);
  var_his_apriltag[sample_iter_apriltag].push_back(msg.pose.pose.orientation.y);
  var_his_apriltag[sample_iter_apriltag].push_back(msg.pose.pose.orientation.z);
  var_his_apriltag[sample_iter_apriltag].push_back(msg.pose.pose.orientation.w);

  sample_iter_apriltag++;
      
}

void log_write_apriltag()
{
  if(sample_iter_apriltag == num_sample)
    {
      cout<<"output data"<<endl;
      for(int i=0; i<num_sample; i++)
      	{
	  output_file_apriltag<<time_his_apriltag.at(i)<<" ";
      	  ostream_iterator<double> output_iterator(output_file_apriltag," ");
      	  copy(var_his_apriltag[i].begin(),var_his_apriltag[i].end(),output_iterator);
      	  output_file_apriltag << endl;
      	}
      var_his_apriltag.clear();
      sample_iter_apriltag = 0;      
    }
  
}
/********************** End DataLog apriltag************************/

void poseMessageRecieved_mocap(const geometry_msgs::PoseWithCovarianceStamped & msg)
{
	ROS_INFO_STREAM(std::setprecision(2)<<std::fixed<<"position.x=("<<msg.pose.pose.position.x<<")");
	log_data_mocap(msg);
	log_write_mocap();

}

void poseMessageRecieved_apriltag(const geometry_msgs::PoseWithCovarianceStamped & msg)
{
	ROS_INFO_STREAM(std::setprecision(2)<<std::fixed<<"position.x=("<<msg.pose.pose.position.x<<")");
	log_data_apriltag(msg);
	log_write_apriltag();
}






int main(int argc, char** argv)
{
	ros::init(argc, argv, "sub_apriltag_and_mocap");
	ros::NodeHandle nh;
	ros::NodeHandle nh_apriltag;

	/**********out_put_mocap.txt*************/
	char text[200];
  	time_t now  = time(NULL);
  	struct tm *t  = localtime(&now);
  	strftime(text,sizeof(text)-1,"%Y%m%d-%H%M%S",t);
  	ostringstream fn;
  	fn << "./" << text << "_mocap.txt";
  	string filename = fn.str();

  	// Convert string to char array
  	char* fnstr  = new char[filename.size()+1];
  	fnstr[filename.size()] = 0;
  	memcpy(fnstr,filename.c_str(),filename.size());
  	output_file_mocap.open(fnstr);
  	/**********end of out_put_mocap.txt*************/

  	/**********out_put_apriltag.txt*************/
	char text_apriltag[200];
  	now  = time(NULL);
  	t  = localtime(&now);
  	strftime(text_apriltag,sizeof(text)-1,"%Y%m%d-%H%M%S",t);
  	ostringstream fn_apriltag;
  	fn_apriltag << "./" << text_apriltag << "_apriltag.txt";
  	filename = fn_apriltag.str();

  	// Convert string to char array
  	char* fnstr_apriltag  = new char[filename.size()+1];
  	fnstr_apriltag[filename.size()] = 0;
  	memcpy(fnstr_apriltag,filename.c_str(),filename.size());
  	output_file_apriltag.open(fnstr_apriltag);
  	/**********end of out_put_apriltag.txt*************/


	ros::Subscriber sub = nh.subscribe("pub_mocap_data/data", 1000, & poseMessageRecieved_mocap);
	ros::Subscriber sub_apriltag = nh_apriltag.subscribe("apriltag_pose/pose", 1000, &poseMessageRecieved_apriltag);

	//for above line, subscribe is actually templated, but complier knows it by
	//looking at the callback function, so no need to worry
	//let ros take over
	ros::spin();
}