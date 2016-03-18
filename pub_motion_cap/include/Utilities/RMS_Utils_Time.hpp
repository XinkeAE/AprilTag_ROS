#ifndef _RMS_UTILS_TIME
#define _RMS_UTILS_TIME

/*
//====================================================================//
 
 ==========================
 Joseph DeGol
 UIUC Fall 2012
 ==========================
 RMS_Utils_Time: Version 1.0
 ==========================
 
 ================================================================
 RMS_Utils_Time.hpp
 This is a series of functions for use in other projects relating
 to time stamps, timers, stopwatch, etc
 ================================================================
 
 List of Functions:
 
 ----- Constructors -----
	
	Time();
			
 --- end Constructors ---

 ----- Sleep Methods -----
 
	struct timespec sleep(time_t sec, long nano);
	void sleep_Nano(long nano);
	void sleep_Micro(long micro);
	void sleep_Milli(long milli);
	void sleep_Seconds(long seconds);

 --- end Sleep Methods ---
		
 ----- Time Stamp Methods -----

	int64_t timestamp();
	int64_t timestamp_seconds(int64_t v);
	int64_t timestamp_useconds(int64_t v);
	void timestamp_to_timeval(int64_t v, struct timeval *tv);
	void timestamp_to_timespec(int64_t v, struct timespec *ts);
 
 --- end Time Stamp Methods ---
			
 ----- Stop Watch Methods -----
	
	void reset();
	long long int elapsedTimeMilliSeconds();
	double elapsedTimeSeconds();
	
 --- end Stop Watch Methosd ---
 
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
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

//---------------------------------------------------------------//
//----------------------- end Includes --------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//----------------------- Namespaces ----------------------------//
//---------------------------------------------------------------//

//namespaces
using namespace std;

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
class Time
{
	
	//---------------------------------------------------------------//
	//------------------------- Private -----------------------------//
	//---------------------------------------------------------------//
	private:
		timeval start;
		timeval current;
	//---------------------------------------------------------------//
	//----------------------- end Private ---------------------------//
	//---------------------------------------------------------------//


	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	public:
	
		/*----- Constructors -----*/
		Time();
		/*--- end Constructors ---*/
		
		/*----- Destructors -----*/
		~Time();
		/*--- end Destructors ---*/
		
		/*----- Sleep Methods -----*/
		struct timespec sleep(time_t sec, long nano);
		void sleep_Nano(long nano);
		void sleep_Micro(long micro);
		void sleep_Milli(long milli);
		void sleep_Seconds(long seconds);
		/*--- end Sleep Methods ---*/
		
		/*----- Time Stamp Methods -----*/
		int64_t timestamp();
		int64_t timestamp_seconds(int64_t v);
		int64_t timestamp_useconds(int64_t v);
		void timestamp_to_timeval(int64_t v, struct timeval *tv);
		void timestamp_to_timespec(int64_t v, struct timespec *ts);
		/*--- end Time Stamp Methods ---*/
		
		/*----- Stop Watch Methods -----*/
		void reset();
		long long int elapsedTimeMilliSeconds();
		double elapsedTimeSeconds();
		/*--- end Stop Watch Methosd ---*/

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
//==================== Time Class Implementation =====================//
//====================================================================//
//====================================================================//

	//---------------------------------------------------------------//
	//-------------------------- Private ----------------------------//
	//---------------------------------------------------------------//

	//---------------------------------------------------------------//
	//------------------------ end Private --------------------------//
	//---------------------------------------------------------------//
	
	
	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	
	/*----- Constructors -----*/
	Time::Time() { gettimeofday(&start,NULL); }
	/*--- end Constructors ---*/
	
	
	/*----- Destructors -----*/
	Time::~Time() {	}
	/*--- end Destructors ---*/
	
	
	/*----- Sleep Methods -----*/
	struct timespec Time::sleep(time_t sec, long nano)
	{
		//set up struct
		struct timespec sleepT, remT;
		sleepT.tv_sec = sec;
		sleepT.tv_nsec = nano;
		
		//sleep
		nanosleep(&sleepT, &remT);
		
		return remT;
	}
	void Time::sleep_Nano(long nano) { sleep(0,nano); }
	void Time::sleep_Micro(long micro) { sleep(0, micro * 1000L); }
	void Time::sleep_Milli(long milli) { sleep(0, milli * 1000000L); }
	void Time::sleep_Seconds(time_t seconds) { sleep(seconds,0L); }
	/*--- end Sleep Methods ---*/
	
	
	/*----- Time Stamp Methods -----*/
	int64_t Time::timestamp()
	{
	    struct timeval tv;
	    gettimeofday (&tv, NULL);
	    return (int64_t) tv.tv_sec * 1000000 + tv.tv_usec;
	}
	
	//convert to magnitude value
	int64_t Time::timestamp_seconds(int64_t v) { return v/1000000; }
	int64_t Time::timestamp_useconds(int64_t v) { return v%1000000; }
	
	//convert to structs
	void Time::timestamp_to_timeval(int64_t v, struct timeval *tv) { tv->tv_sec  = timestamp_seconds(v); tv->tv_usec = timestamp_useconds(v); }
	void Time::timestamp_to_timespec(int64_t v, struct timespec *ts) { ts->tv_sec  = timestamp_seconds(v); ts->tv_nsec = timestamp_useconds(v)*1000; }
	
	/*--- end Time Stamp Methods ---*/
	
		
	/*----- Stop Watch Methods -----*/
	
	//reset timer
	void Time::reset() { gettimeofday(&start,NULL); }
	
	//return elapsed time in milliseconds
	long long int Time::elapsedTimeMilliSeconds()
	{
		gettimeofday(&current,NULL);
		timeval delta;
		timersub(&current,&start,&delta);
		long long int msecs = delta.tv_sec*1000 + delta.tv_usec/1000;
		return msecs;
	}
	
	//return elapsed time in seconds
	double Time::elapsedTimeSeconds() {
		gettimeofday(&current,NULL);
		timeval delta;
		timersub(&current,&start,&delta);
		double secs=double(delta.tv_sec);
		secs += double(delta.tv_usec)/1000000.0;
		return secs;
	}
	/*--- end Stop Watch Methods ---*/
	
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
