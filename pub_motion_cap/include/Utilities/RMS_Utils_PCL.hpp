#ifndef _RMS_UTILS_PCL
#define _RMS_UTILS_PCL

/*
//--------------------------------------------------------------------//
 
 --------------------------
 Joseph DeGol
 UIUC Fall 2012
 --------------------------
 RMS_Utils_PCL: Version 1.0
 --------------------------
 
 ----------------------------------------------------------------
 RMS_Utils_PCL.hpp
 This is a series of functions for use in other projects relating
 to PointCloudLibrary (PCL)
 ----------------------------------------------------------------
 
 List of Functions:
 
//--------------------------------------------------------------------//
*/




//--------------------------------------------------------------------//
//---------------------------- Includes ------------------------------//
//--------------------------------------------------------------------//

//system
#include <iostream>
#include <vector>

//pcl
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

//namespaces
using namespace std;
using namespace pcl;

//--------------------------------------------------------------------//
//--------------------------------------------------------------------//
//--------------------------------------------------------------------//





//namespace
namespace Robots 
{
	
	//--------------------------------------------------------------------//
	//----------------------- Function Prototypes ------------------------//
	//--------------------------------------------------------------------//
	
	/*----- Point Cloud Conversions -----*/
	
	//XYZ
	float* PointCloudXYZToFloatArrayXYZ( PointCloud<PointXYZ>::Ptr inCloud );
	float* PointCloudXYZToFloatArrayXYZ( PointCloud<PointXYZ>::ConstPtr inCloud );
	
	//XYZRGB
	float* PointCloudXYZRGBToFloatArrayXYZRGB( PointCloud<PointXYZ>::Ptr inCloud);
	
	//XYZ
	PointCloud<PointXYZ>::Ptr FloatArrayXYZToPointCloudPtrXYZ(float *PointCloudDataXYZ, int size);
	PointCloud<PointXYZ>::Ptr FloatArrayXYZToPointCloudPtrXYZ(vector<float> PointCloudDataXYZ);
	
	//XYZRGB
	PointCloud<PointXYZ>::Ptr FloatArrayXYZRGBToPointCloudPtrXYZRGB(float *PointCloudDataXYZRGB);
	
	/*--- end Point Cloud Conversions ---*/
	
	/*----- Print Functions -----*/
	
	void printPointCloudXYZ( PointCloud<PointXYZ>::Ptr inCloud );
	void printPointCloudXYZ( PointCloud<PointXYZ>::ConstPtr inCloud );
	void printFloatXYZ(float *inCloud,int size);
	void printFloatXYZ(vector<float> *inCloud);
	
	/*----- end Print Functions ---*/
	
	//--------------------------------------------------------------------//
	//--------------------- End Function Prototypes ----------------------//
	//--------------------------------------------------------------------//
	
	
	
	
	
	//--------------------------------------------------------------------//
	//--------------------- Point Cloud Conversions ----------------------//
	//--------------------------------------------------------------------//

	float* PointCloudXYZToFloatArrayXYZ( PointCloud<PointXYZ>::Ptr inCloud )
	{
		//create float array
		float *FloatArrayXYZ = new float[(*inCloud).points.size() * 3];
		
		//add points to float array
		int pt = 0;
		for ( int i = 0; i < ((*inCloud).points.size()*3); i++)
		{
			FloatArrayXYZ[i++] = (*inCloud).points[pt].x;
			FloatArrayXYZ[i++] = (*inCloud).points[pt].y;
			FloatArrayXYZ[i] = (*inCloud).points[pt].z;
			pt++;
		}
		
		//return float array
		return FloatArrayXYZ;
	}
	float* PointCloudXYZToFloatArrayXYZ( PointCloud<PointXYZ>::ConstPtr inCloud )
	{
		//create float array
		int size = (*inCloud).points.size() * 3;
		float *FloatArrayXYZ = new float[size];

		//add points to float array
		int pt = 0;
		for ( int i = 0; i < size; i++)
		{
			FloatArrayXYZ[i++] = (*inCloud).points[pt].x;
			FloatArrayXYZ[i++] = (*inCloud).points[pt].y;
			FloatArrayXYZ[i] = (*inCloud).points[pt].z;
			pt++;
		}
		
		//return float array
		return FloatArrayXYZ;

	}
	
	float* PointCloudXYZRGBToFloatArrayXYZRGB( PointCloud<PointXYZ>::Ptr inCloud)
	{}
	
	PointCloud<PointXYZ>::Ptr FloatArrayXYZToPointCloudPtrXYZ(float *PointCloudDataXYZ, int size)
	{
		
		//create point cloud
		PointCloud<PointXYZ>::Ptr cloud;
		
		//resize cloud
		(*cloud).width = size / 3;
		(*cloud).height = 1;
		(*cloud).is_dense = false;
		(*cloud).points.resize( (*cloud).width * (*cloud).height );
		
		//populate cloud
		int pt = 0;
		for ( int i = 0; i < size; i++ )
		{
			(*cloud).points[pt].x = PointCloudDataXYZ[i++];
			(*cloud).points[pt].y = PointCloudDataXYZ[i++];
			(*cloud).points[pt].z = PointCloudDataXYZ[i];
			pt++;
		}
		
		//return
		return cloud;
	}
	PointCloud<PointXYZ>::Ptr FloatArrayXYZToPointCloudPtrXYZ(vector<float> PointCloudDataXYZ)
	{
		
		//create point cloud
		int length = PointCloudDataXYZ.size();
		PointCloud<PointXYZ>::Ptr cloud(new PointCloud<PointXYZ>);
		
		//resize cloud
		(*cloud).width = length / 3;
		(*cloud).height = 1;
		(*cloud).is_dense = false;
		(*cloud).points.resize( (*cloud).width * (*cloud).height );
		
		//populate cloud
		int pt = 0;
		for ( int i = 0; i < length; i++ )
		{
			(*cloud).points[pt].x = PointCloudDataXYZ[i++];
			(*cloud).points[pt].y = PointCloudDataXYZ[i++];
			(*cloud).points[pt].z = PointCloudDataXYZ[i];
			pt++;
		}
		
		//return
		return cloud;
	}
	
	PointCloud<PointXYZ>::Ptr FloatArrayXYZRGBToPointCloudPtrXYZRGB(float *PointCloudDataXYZRGB)
	{}
	
	//--------------------------------------------------------------------//
	//------------------- End Point Cloud Conversions --------------------//
	//--------------------------------------------------------------------//
	
	
	
	
	
	//--------------------------------------------------------------------//
	//------------------------- Print Functions --------------------------//
	//--------------------------------------------------------------------//
	void printPointCloudXYZ( PointCloud<PointXYZ>::Ptr inCloud )
	{
		for (int i = 0; i < (*inCloud).points.size (); i++)
		{
			cout << "X = " << (*inCloud).points[i].x << ". Y = " << (*inCloud).points[i].y << ". Z = " << (*inCloud).points[i].z << endl;
		}
	}
	void printPointCloudXYZ( PointCloud<PointXYZ>::ConstPtr inCloud )
	{
		for (int i = 0; i < (*inCloud).points.size (); i++)
		{
			cout << "X = " << (*inCloud).points[i].x << ". Y = " << (*inCloud).points[i].y << ". Z = " << (*inCloud).points[i].z << endl;
		}
	}
	void printFloatXYZ(float *inCloud, int size)
	{
		for (int i = 0; i < size; i++)
		{
			cout << "X = " << inCloud[i];
			cout << ". Y = " << inCloud[++i];
			cout << ". Z = " << inCloud[++i] << endl;
		}
	}
	void printFloatXYZ(vector<float> inCloud)
	{
		for (int i = 0; i < inCloud.size(); i++)
		{
			cout << "X = " << inCloud[i];
			cout << ". Y = " << inCloud[++i];
			cout << ". Z = " << inCloud[++i] << endl;
		}
	}
	//--------------------------------------------------------------------//
	//----------------------- End Print Functions ------------------------//
	//--------------------------------------------------------------------//
}

#endif
