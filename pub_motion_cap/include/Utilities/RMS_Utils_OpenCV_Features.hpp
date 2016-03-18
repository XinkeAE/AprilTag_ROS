#ifndef _RMS_UTILS_OPENCV_FEATURES
#define _RMS_UTILS_OPENCV_FEATURES

/*
//====================================================================//
 
 ==========================
 Joseph DeGol
 UIUC Fall 2012
 ==========================
 RMS_Utils_OpenCV_Features.hpp: Version 1.0
 ==========================
 
 ================================================================
 RMS_Utils_OpenCV_Features.hpp
 Wrapper class for opencv's feature detectors
 ================================================================
 
 List of Functions:
 
//====================================================================//
*/





//====================================================================//
//====================================================================//
//============================ Preamble ==============================//
//====================================================================//
//====================================================================//


//--------------------------------------------------------------------//
//---------------------------- Includes ------------------------------//
//--------------------------------------------------------------------//

//system
#include <iostream>
#include <vector>

//opencv
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

//---------------------------------------------------------------//
//----------------------- end Includes --------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//----------------------- Namespaces ----------------------------//
//---------------------------------------------------------------//

//namespaces
using namespace std;
using namespace cv;

//---------------------------------------------------------------//
//---------------------- end Namespaces -------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//------------------------- Globals -----------------------------//
//---------------------------------------------------------------//
//---------------------------------------------------------------//
//------------------------ end Globals --------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//------------------- Function Prototypes -----------------------//
//---------------------------------------------------------------//
//---------------------------------------------------------------//
//------------------ end Function Prototypes --------------------//
//---------------------------------------------------------------//

//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//







namespace Robots {
//====================================================================//
//====================================================================//
//====================== Time Class Definition =======================//
//====================================================================//
//====================================================================//
class OpenCV_Features
{
	
	//---------------------------------------------------------------//
	//------------------------- Private -----------------------------//
	//---------------------------------------------------------------//
	private:
	
	/*----- Flags -----*/
	bool Detector_Primed;
	bool Extractor_Primed;
	bool Matcher_Primed;
	
	bool Verbose;
	/*--- end Flags ---*/
	
	/*----- Feature Detection Ptr -----*/
	Ptr<FeatureDetector> Feature_Detector;
	Ptr<DescriptorExtractor> Feature_Extractor;
	Ptr<DescriptorMatcher> Feature_Matcher;
	/*--- end Feature Detection Ptr ---*/
	
	/*----- Private Init -----*/
	void OpenCV_Features_Init( );
	/*--- end Private Init ---*/
	
	/*----- Helpers -----*/
	bool Point_Is_Unique( int i, vector<Point2f> *keypoints_param, int window_param );
	int Calculate_Min_Distance( vector<DMatch> *matches_param, Mat *descriptors_param );
	/*--- end Helpers ---*/
	
	//---------------------------------------------------------------//
	//----------------------- end Private ---------------------------//
	//---------------------------------------------------------------//


	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	public:
	
		/*----- Constructors -----*/
		OpenCV_Features( );
		/*--- end Constructors ---*/
		
		/*----- Destructors -----*/
		~OpenCV_Features();
		/*--- end Destructors ---*/
		
		/*----- Primers -----*/
		
		//modes
		void Prime_Mode_Verbose( bool verbose_param );
		
		//detectors
		bool Prime_Detector( string detector_type_param );
		bool Prime_Detector_Sift( int feature_param = 0, int octave_layers_param = 3, double contrast_threshold_param = 0.04, double edge_threshold_param = 10, double sigma_param = 1.6 );
		bool Prime_Detector_Surf( double hessian_param, int octaves_param = 4, int octave_layers_param = 2, bool extended = true, bool upright = false );
		bool Prime_Detector_Orb( int features_param = 500, float scale_param = 1.2f, int levels_param = 8, int edge_threshold_param = 31, int first_level_param = 0, int WTA_K_param = 2, int score_type_param = ORB::HARRIS_SCORE, int patch_size_param = 31 );
		//bool Prime_Detector_FREAK( bool orientation_norm_param, bool scale_norm_param, float pattern_scale_param, int octaves_param, const vector<int>& selected_pairs_param=vector<int>() );
		
		//extractors
		bool Prime_Extractor( string extractor_type_param );
		bool Prime_Extractor_Sift(  );
		bool Prime_Extractor_Surf(  );
		bool Prime_Extractor_Orb(  );
		bool Prime_Extractor_FREAK(  );
		
		//matchers
		bool Prime_Matcher( string matcher_type_param );
		bool Prime_Matcher_Flann( );
		bool Prime_Matcher_BruteForce( );
		
		//tracker
		bool Prime_Tracker( Mat *image_param, vector<Point2f> *features_param, vector<uchar> *status_param, vector<float> *err_param, int max_param = 50, int min_param = 10, double quality_param = .1, double distance_param = 50, int block_size_param = 3, bool use_harris_param = false, double harris_k_param = 0.04 );
		/*--- end Primers ---*/
		
		/*----- Actions -----*/
		
		//detect
		void Detect( Mat *image_param, vector<KeyPoint> *keypoints_param);
		
		//compute
		void Compute( Mat *image_param, vector<KeyPoint> *keypoints_param, Mat *descriptors_param );
		
		//match
		void Match( Mat *descriptors1_param, Mat *descriptors2_param, vector<DMatch> *matches_param );
		void Match_Radius( Mat *descriptors1_param, Mat *descriptors2_param, vector< vector<DMatch> > *matches_param, float radius_param );
		void Match_KNN( Mat *descriptors1_param, Mat *descriptors2_param, vector< vector<DMatch> > *matches_param, int n_param );
		
		//track
		void Track( );
		int Track_Step( Mat *image_prev_param, Mat *image_next_param, vector<Point2f> *points_prev_param, vector<Point2f> *points_next_param, vector<uchar> *status_param, vector<float> *err_param, int window_param = 10 );
		
		/*--- end Actions ---*/
		
		/*----- Auxiliary Methods -----*/
		void Get_Good_Matches( vector<DMatch> *matches_param, Mat *descriptors_param, vector<DMatch> *good_matches_param, int min_dist_param = -999, float threshold_param = 3.0f );
		/*--- end Auxiliary Methods ---*/
		
		/*----- Output -----*/
		void DrawPoints( Mat *frame_param, vector<KeyPoint> *keypoint_param );
		void DrawPoints( Mat *frame_param, vector<Point2f> *keypoint_param, int radius_param = 6 );
		void DrawFlow( Mat *frame_param, vector<Point2f> *keypoint_prev_param, vector<Point2f> *keypoint_next_param, int radius_param = 6 );
		/*--- end Output ---*/
		
	//---------------------------------------------------------------//
	//------------------------ end Public ---------------------------//
	//---------------------------------------------------------------//
	
	
};
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//





//====================================================================//
//====================================================================//
//============== OpenCV_Features Class Implementation ================//
//====================================================================//
//====================================================================//

	//---------------------------------------------------------------//
	//-------------------------- Private ----------------------------//
	//---------------------------------------------------------------//
	
	/*----- Private Init -----*/
	void OpenCV_Features::OpenCV_Features_Init( )
	{
		//for using Sift and Surf
		initModule_nonfree();
		
		//set flags
		Detector_Primed = false;
		Extractor_Primed = false;
		Matcher_Primed = false;
	}
	/*--- end Private Init ---*/
	
	
	/*----- Helpers -----*/
	bool OpenCV_Features::Point_Is_Unique( int i, vector<Point2f> *keypoints_param, int window_param )
	{
		//chosen point
		vector<Point2f>::iterator ptIt = keypoints_param->begin() + i;
		
		//iterate over
		for( vector<Point2f>::iterator it = (ptIt+1) ; it != keypoints_param->end(); ++it)
		{
			if( abs(it->x - ptIt->x) < window_param && abs(it->y - ptIt->y) < window_param )
			{
				//"same point"
				return false;
			}
		}
		return true;
	}
	
	int OpenCV_Features::Calculate_Min_Distance( vector<DMatch> *matches_param, Mat *descriptors_param )
	{
		int dist, min_dist = 10000;
		
  		for( int i = 0; i < descriptors_param->rows; i++ )
  		{ 
			dist = (*matches_param)[i].distance;
    		if( dist < min_dist ) { min_dist = dist; }
  		}
  		
  		return min_dist;
	}
	/*--- end Helpers ---*/
	
	//---------------------------------------------------------------//
	//------------------------ end Private --------------------------//
	//---------------------------------------------------------------//
	
	
	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	
	/*----- Constructors -----*/
	OpenCV_Features::OpenCV_Features( )
	{
		//private init
		OpenCV_Features_Init( );
	}
	/*--- end Constructors ---*/
	
	
	/*----- Destructors -----*/
	OpenCV_Features::~OpenCV_Features( ) {	}
	/*--- end Destructors ---*/
	
	
	/*----- Primers -----*/
	
	//modes
	void OpenCV_Features::Prime_Mode_Verbose( bool verbose_param ) { Verbose = verbose_param; }
	
	//Detectors
	bool OpenCV_Features::Prime_Detector( string detector_type_param ) 
	{	
		//create detector if possible
		Feature_Detector = FeatureDetector::create( detector_type_param );
		if( !Feature_Detector.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector() Note : Changed to " << detector_type_param << endl;
			Detector_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector() Error : Invalid Feature Detection Type: " << detector_type_param << endl;
			Detector_Primed = false;
		}
		
		//return
		return Detector_Primed;
	}
	bool OpenCV_Features::Prime_Detector_Sift( int feature_param, int octave_layers_param, double contrast_threshold_param, double edge_threshold_param, double sigma_param )
	{
		//create sift detector
		Feature_Detector = Ptr<FeatureDetector>(new SiftFeatureDetector( feature_param, octave_layers_param, contrast_threshold_param, edge_threshold_param, sigma_param ));
		if( !Feature_Detector.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector_Sift() Note : Changed to Sift." << endl;
			Detector_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector_Sift() Error." << endl;
			Detector_Primed = false;
		}
		
		//return
		return Detector_Primed;
	}
	bool OpenCV_Features::Prime_Detector_Surf( double hessian_param, int octaves_param, int octave_layers_param, bool extended, bool upright )
	{
		//create surf detector
		Feature_Detector = Ptr<FeatureDetector>(new SurfFeatureDetector( hessian_param, octaves_param, octave_layers_param, extended, upright ));
		if( !Feature_Detector.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector_Surf() Note : Changed to Surf." << endl;
			Detector_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector_Surf() Error." << endl;
			Detector_Primed = false;
		}
		
		//return
		return Detector_Primed;
	}
	bool OpenCV_Features::Prime_Detector_Orb( int features_param, float scale_param, int levels_param, int edge_threshold_param, int first_level_param, int WTA_K_param, int score_type_param, int patch_size_param )
	{
		//create surf detector
		Feature_Detector = Ptr<FeatureDetector>(new OrbFeatureDetector( features_param, scale_param, levels_param, edge_threshold_param, first_level_param, WTA_K_param, score_type_param, patch_size_param ));
		if( !Feature_Detector.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector_Orb() Note : Changed to Orb." << endl;
			Detector_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector_Orb() Error." << endl;
			Detector_Primed = false;
		}
		
		//return
		return Detector_Primed;
	}
	/*bool OpenCV_Features::Prime_Detector_FREAK( bool orientation_norm_param, bool scale_norm_param, float pattern_scale_param, int octaves_param, const vector<int>& selected_pairs_param )
	{
		//create FREAK detector
		Feature_Detector = Ptr<FeatureDetector>(new FREAKFeatureDetector( orientation_norm_param, scale_norm_param, pattern_scale_param, octaves_param, selected_pairs_param ));
		if( !Feature_Detector.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector_FREAK() Note : Changed to FREAK." << endl;
			Detector_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Detector_FREAK() Error." << endl;
			Detector_Primed = false;
		}
		
		//return
		return Detector_Primed;
	}*/
	
	//Extractors
	bool OpenCV_Features::Prime_Extractor( string extractor_type_param )
	{
		//create extractor if possible
		Feature_Extractor = DescriptorExtractor::create( extractor_type_param );
		if( !Feature_Extractor.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor() Note : Changed to " << extractor_type_param << endl;
			Extractor_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor() Error : Invalid Feature Detection Type: " << extractor_type_param << endl;
			Extractor_Primed = false;
		}
		
		//return
		return Extractor_Primed;
	}
	bool OpenCV_Features::Prime_Extractor_Sift( )
	{
		//create sift descriptors
		Feature_Extractor = Ptr<DescriptorExtractor>(new SiftDescriptorExtractor( ));
		if( !Feature_Detector.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor_Sift() Note : Changed to Sift." << endl;
			Extractor_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor_Sift() Error." << endl;
			Extractor_Primed = false;
		}
		
		//return
		return Extractor_Primed;
	}
	bool OpenCV_Features::Prime_Extractor_Surf(  )
	{
		//create surf descriptors
		Feature_Extractor = Ptr<DescriptorExtractor>(new SurfDescriptorExtractor( ));
		if( !Feature_Detector.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor_Surf() Note : Changed to Sift." << endl;
			Extractor_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor_Surf() Error." << endl;
			Extractor_Primed = false;
		}
		
		//return
		return Extractor_Primed;
	}
	bool OpenCV_Features::Prime_Extractor_Orb(  )
	{
		//create orb descriptors
		Feature_Extractor = Ptr<DescriptorExtractor>(new OrbDescriptorExtractor( ));
		if( !Feature_Detector.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor_Orb() Note : Changed to Sift." << endl;
			Extractor_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor_Orb() Error." << endl;
			Extractor_Primed = false;
		}
		
		//return
		return Extractor_Primed;
	}
	bool OpenCV_Features::Prime_Extractor_FREAK(  )
	{
		//create orb descriptors
		Feature_Extractor = Ptr<DescriptorExtractor>(new FREAK( ));
		if( !Feature_Detector.empty() ) 
		{ 
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor_FREAK() Note : Changed to FREAK." << endl;
			Extractor_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Extractor_FREAK() Error." << endl;
			Extractor_Primed = false;
		}
		
		//return
		return Extractor_Primed;
	}
	
	//matcher
	bool OpenCV_Features::Prime_Matcher( string matcher_type_param )
	{
		//create matcher if possible
		Feature_Matcher = DescriptorMatcher::create( matcher_type_param );
		if( !Feature_Matcher.empty() )
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Matcher() Note : Changed to " << matcher_type_param << endl;
			Matcher_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Matcher() Error : Invalid Feature Detection Type: " << matcher_type_param << endl;
			Matcher_Primed = false;
		}
		
		//return
		return Matcher_Primed;
	}
	bool OpenCV_Features::Prime_Matcher_Flann( )
	{
		//create matcher
		Feature_Matcher = Ptr<DescriptorMatcher>(new FlannBasedMatcher( ));
		if( !Feature_Matcher.empty() )
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Matcher_Flann() Note : Changed to FlannBased Matcher." << endl;
			Matcher_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Matcher_Flann() Error." << endl;
			Matcher_Primed = false;
		}
		
		//return
		return Matcher_Primed;
	}
	bool OpenCV_Features::Prime_Matcher_BruteForce( )
	{
		//create matcher
		Feature_Matcher = Ptr<DescriptorMatcher>(new BFMatcher( ));
		if( !Feature_Matcher.empty() )
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Matcher_BruteForce() Note : Changed to BruteForce Matcher." << endl;
			Matcher_Primed = true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Matcher() Error." << endl;
			Matcher_Primed = false;
		}
		
		//return
		return Matcher_Primed;
	}
	
	//tracker
	bool OpenCV_Features::Prime_Tracker( Mat *image_param, vector<Point2f> *features_param, vector<uchar> *status_param, vector<float> *err_param, int max_param, int min_param, double quality_param, double distance_param, int block_size_param, bool use_harris_param, double harris_k_param )
	{
		goodFeaturesToTrack( *image_param, *features_param, max_param, quality_param, distance_param, Mat(), block_size_param, use_harris_param, harris_k_param );
		if( min_param <= features_param->size() )
		{
			status_param->reserve( features_param->size() );
			err_param->reserve( features_param->size() );
			return true;
		}
		else
		{
			cout << "RMS_Utils_OpenCV_Features :: Prime_Tracker() Warning : goodFeaturesToTrack returned less than " << min_param << " trackable points." << endl;
			return false;
		}
	}
	/*--- end Primers ---*/
	
	
	/*----- Actions -----*/
	
	//detect
	void OpenCV_Features::Detect( Mat *image_param, vector<KeyPoint> *keypoints_param)
	{
		if( Detector_Primed ) { Feature_Detector->detect( *image_param,*keypoints_param ); }
		else { cout << "RMS_Utils_OpenCV_Features :: Detect() Error : Detector not Primed. No Effect." << endl; }
	}
	
	//compute
	void OpenCV_Features::Compute( Mat *image_param, vector<KeyPoint> *keypoints_param, Mat *descriptors_param )
	{
		if( Extractor_Primed ) { Feature_Extractor->compute( *image_param, *keypoints_param, *descriptors_param ); }
		else { cout << "RMS_Utils_OpenCV_Features :: Compute() Error : Extractor not Primed. No Effect." << endl; }
	}
	
	//match
	void OpenCV_Features::Match( Mat *descriptors1_param, Mat *descriptors2_param, vector<DMatch> *matches_param )
	{
		if( Matcher_Primed ) { Feature_Matcher->match( *descriptors1_param, *descriptors2_param, *matches_param ); }
		else { cout << "RMS_Utils_OpenCV_Features :: Match() Error : Matcher not Primed. No Effect." << endl; }
	}
	void OpenCV_Features::Match_Radius( Mat *descriptors1_param, Mat *descriptors2_param, vector< vector<DMatch> > *matches_param, float radius_param )
	{
		if( Matcher_Primed ) { Feature_Matcher->radiusMatch( *descriptors1_param, *descriptors2_param, *matches_param, radius_param ); }
		else { cout << "RMS_Utils_OpenCV_Features :: Match() Error : Matcher not Primed. No Effect." << endl; }
	}
	void OpenCV_Features::Match_KNN( Mat *descriptors1_param, Mat *descriptors2_param, vector< vector<DMatch> > *matches_param, int n_param )
	{
		if( Matcher_Primed ) { Feature_Matcher->knnMatch( *descriptors1_param, *descriptors2_param, *matches_param, n_param ); }
		else { cout << "RMS_Utils_OpenCV_Features :: Match() Error : Matcher not Primed. No Effect." << endl; }
	}
	
	//track
	void OpenCV_Features::Track()
	{
		
	}
	int OpenCV_Features::Track_Step( Mat *image_prev_param, Mat *image_next_param, vector<Point2f> *points_prev_param, vector<Point2f> *points_next_param, vector<uchar> *status_param, vector<float> *err_param, int window_param )
	{
		//calculate optic flow
		calcOpticalFlowPyrLK( *image_prev_param, *image_next_param, *points_prev_param, *points_next_param, *status_param, *err_param );
		
		//return found points
		int found_points = 0, i = 0;
		for ( vector<uchar>::iterator it = status_param->begin() ; it != status_param->end(); ++it) 
		{ 
			if( (*it) && Point_Is_Unique(i, points_next_param, window_param) ) 
			{ 
				found_points++; 
			} 
			i++;
		}
		return found_points;
    
	}
	/*--- end Actions ---*/
	
	
	/*----- Auxiliary Methods -----*/
	void OpenCV_Features::Get_Good_Matches( vector<DMatch> *matches_param, Mat *descriptors_param, vector<DMatch> *good_matches_param, int min_dist_param, float threshold_param )
	{
		//get minimum matched distance
		if( min_dist_param == -999 ) { min_dist_param = Calculate_Min_Distance( matches_param, descriptors_param ); }
		
		if( Verbose ) { cout << "||| VERBOSE ||| RMS_Utils_OpenCV_Features :: Get_Good_Matches() : min_dist_param = " << min_dist_param << " ||| VERBOSE |||"<< endl; }
		
		//only keep matches close to min_dist
		good_matches_param->clear();
		for( int i = 0; i < descriptors_param->rows; i++ )
		{ 
			if( (*matches_param)[i].distance < threshold_param*min_dist_param ) { good_matches_param->push_back( (*matches_param)[i]); }
  		}
  			
	}
	/*--- end Auxiliary Methods ---*/
		
		
	/*----- Output -----*/
	void OpenCV_Features::DrawPoints( Mat *frame_param, vector<KeyPoint> *keypoint_param )
	{
		drawKeypoints( *frame_param, (*keypoint_param), *frame_param );
	}
	void OpenCV_Features::DrawPoints( Mat *frame_param, vector<Point2f> *keypoint_param, int radius_param )
	{
        for( int i = 0; i < keypoint_param->size(); i++ ) 
        {	
            circle( (*frame_param), (*keypoint_param)[i], radius_param, Scalar(255,0,0), 2, 8, 0 );
        }
	}
	void OpenCV_Features::DrawFlow( Mat *frame_param, vector<Point2f> *keypoint_prev_param, vector<Point2f> *keypoint_next_param, int radius_param)
	{
        for( int i = 0; i < keypoint_next_param->size(); i++ ) { 
            
            circle( (*frame_param), (*keypoint_next_param)[i], radius_param, Scalar(255,0,0), 2, 8, 0 );
            
            Point p0( (*keypoint_next_param)[i].x, (*keypoint_next_param)[i].y );
            Point p1( (*keypoint_prev_param)[i].x, (*keypoint_prev_param)[i].y );
            line( (*frame_param), p0, p1, CV_RGB(0,255,0), 2);
        }
	}
	/*--- end Output ---*/
	
	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	
	
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//

}//end namespace Robots


#endif
