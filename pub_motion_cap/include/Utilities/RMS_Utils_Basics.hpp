#ifndef _RMS_UTILS_BASICS
#define _RMS_UTILS_BASICS

/*
//--------------------------------------------------------------------//
 
 --------------------------
 Joseph DeGol
 UIUC Fall 2012
 --------------------------
 RMS_Utils_Basics: Version 1.0
 --------------------------
 
 ----------------------------------------------------------------
 RMS_Utils_Basics.hpp
 This is a series of functions for use in other projects relating
 to conversion, file i/o, ...
 ----------------------------------------------------------------
 
 List of Functions:
 
 ----- File I/O -----
 
	//write Image
	
	//read Image
	
	//split PGM
	inline bool splitPGMGivenFile_FStream(string fileName, int height, int width);
	inline bool splitPGMGivenFile_FStream(char* fileName, int height, int width);
	inline bool splitPGMGivenFile_STDIO(string fileName, int height, int width);
	inline bool splitPGMGivenFile_STDIO(char* fileName, int height, int width);

 --- end File I/O ---
 
 
 ----- Array Copying -----
	
 --- end Array Copying ---
 
 
 ----- To String Conversions -----
 
	//templates
	template <typename T> inline string numberToString(T number);
	template <typename T> inline string numberToString(T number, int precision);
	
	//explicit calls
	inline string boolToString(bool b);
	inline string intToString(int number);
	inline string floatToString(float number);
	inline string floatToString(float number, int precision);
	inline string doubleToString(double number);
	inline string doubleToString(double number, int precision);

 --- end To String Conversions ---
  
  
 ----- From String Conversions -----
	
	//templates
	template <typename T> T stringToNumber( const string &text, T defValue = T() );
	
	//explicit calls
	inline bool stringToBool( const string &text );
	inline int stringToInt( const string &text );
	inline float stringToFloat( const string &text );
	inline double stringToDouble( const string &text );
	inline string stringToUpperString( string text );
	inline string stringToLowerString( string text );
	* 
 --- end From String Conversions ---
 
//--------------------------------------------------------------------//
*/




//--------------------------------------------------------------------//
//---------------------------- Includes ------------------------------//
//--------------------------------------------------------------------//

//system
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <stdio.h>

//namespaces
using namespace std;

//--------------------------------------------------------------------//
//--------------------------------------------------------------------//
//--------------------------------------------------------------------//





//namespace
namespace Robots 
{
	
	//--------------------------------------------------------------------//
	//----------------------- Function Prototypes ------------------------//
	//--------------------------------------------------------------------//
	
	/*----- File I/O -----*/
	
	//write Image
	inline bool writePGM();
	inline bool writeJPG();
	inline bool writePNG();
	inline bool writeBMP();
	
	//read Image
	inline bool readPGM();
	inline bool readJPG();
	inline bool readPNG();
	inline bool readBMP();
	
	//split PGM
	inline bool splitPGMGivenFile_FStream(string fileName, int height, int width);
	inline bool splitPGMGivenFile_FStream(char* fileName, int height, int width);
	inline bool splitPGMGivenFile_STDIO(string fileName, int height, int width);
	inline bool splitPGMGivenFile_STDIO(char* fileName, int height, int width);
	
	/*--- end File I/O ---*/
	
	
	/*----- To String Conversions -----*/
	
	//templates
	template <typename T> inline string numberToString(T number);
	template <typename T> inline string numberToString(T number, int precision);
	
	//explicit calls
	inline string boolToString(bool b);
	inline string intToString(int number);
	inline string int64ToString(int64_t number);
	inline string floatToString(float number);
	inline string floatToString(float number, int precision);
	inline string doubleToString(double number);
	inline string doubleToString(double number, int precision);
	
	/*--- End To String Conversions ---*/
	
	
	/*----- From String Conversions -----*/
	
	//templates
	template <typename T> T stringToNumber( const string &text, T defValue = T() );
	
	//explicit calls
	inline bool stringToBool( const string &text );
	inline int stringToInt( const string &text );
	inline float stringToFloat( const string &text );
	inline double stringToDouble( const string &text );
	inline string stringToUpperString( string text );
	inline string stringToLowerString( string text );
	
	/*--- End From String Conversions ---*/
	
	//--------------------------------------------------------------------//
	//--------------------- End Function Prototypes ----------------------//
	//--------------------------------------------------------------------//
	
	
	
	
	
	//--------------------------------------------------------------------//
	//---------------------------- File I/O ------------------------------//
	//--------------------------------------------------------------------//
	
	/*----- Write Image -----*/
	inline bool writePGM() { return false; }
	inline bool writeJPG() { return false; }
	inline bool writePNG() { return false; }
	inline bool writeBMP() { return false; }
	/*--- end Write Image ---*/
	
	
	/*----- Read Image -----*/
	inline bool readPGM() { return false; }
	inline bool readJPG() { return false; }
	inline bool readPNG() { return false; }
	inline bool readBMP() { return false; }
	/*--- end Read Image ---*/
	
	
	/*----- Split PGM -----*/
	inline bool splitPGMGivenFile_FStream(string fileName, int height, int width)
	{
		return splitPGMGivenFile_FStream(fileName.c_str(), height, width);
	}
	
	inline bool splitPGMGivenFile_FStream(char* fileName, int height, int width)
	{
		//open file
		ifstream myFile;
		myFile.open(fileName, ios::in | ios::binary);
		
		//read file
		if ( myFile.is_open() )
		{
			int imageSize = height * width;
			char *buffer = new char [imageSize];
			
			while( myFile.good() )
			{
				myFile.read(buffer,imageSize);
				cout << buffer << endl;
			}
		}
		else { cout << "RMS_Utils_Basics::splitPGMGivenFile_FStream - Error Opening file: " << fileName << endl; return false; }
		
		//close file
		myFile.close();
		
		//return
		return true;
	}
	
	inline bool splitPGMGivenFile_STDIO(string fileName, int height, int width)
	{
		return splitPGMGivenFile_STDIO(fileName.c_str(), height, width);
	}
	
	inline bool splitPGMGivenFile_STDIO(char* fileName, int height, int width)
	{
		//open file
		FILE *pFile;
		pFile = fopen(fileName, "r");
		if ( pFile == NULL ) {	cout << "RMS_Utils_Basics::splitPGMGivenFile_STDIO - Error Opening file: " << fileName << endl; return false; }
		
		//read files
		//int imageSize = height * width;
		//char buffer[imageSize];
		
		//while( fread(buffer,sizeof(char),imageSize,pFile) != EOF )
		//{
		//	cout << buffer << endl;
		//}
		
		//return
		return true;
		
	}
	/*--- end Split PGM ---*/
	
	//--------------------------------------------------------------------//
	//-------------------------- End File I/O ----------------------------//
	//--------------------------------------------------------------------//

	
	
	//--------------------------------------------------------------------//
	//----------------------- To String Conversion -----------------------//
	//--------------------------------------------------------------------//
	
	/*----- numberToString -----*/
	template <typename T> inline string numberToString(T number)
	{
		stringstream ss;
		ss << number;
		return ss.str();
	}
	template <typename T> inline string numberToString(T number, int precision)
	{
		stringstream ss;
		ss << std::setprecision(precision) << number;
		return ss.str();
	}
	/*--- end numberToString -----*/
	
	/*----- boolToString -----*/
	inline string boolToString(bool b)
	{
		return b ? "true" : "false";
	}
	/*--- end boolToString ---*/
	
	/*----- intToString -----*/
	inline string intToString(int number)
	{
		stringstream ss;
		ss << number;
		return ss.str();
	}
	inline string int64ToString(int64_t number)
	{
		stringstream ss;
		ss << number;
		return ss.str();
	}
	/*--- end intToString ---*/
	
	/*----- floatToString -----*/
	inline string floatToString(float number)
	{
		stringstream ss;
		ss << std::setprecision(10) << number;
		return ss.str();
	}
	inline string floatToString(float number, int precision)
	{
		stringstream ss;
		ss << std::setprecision(precision) << number;
		return ss.str();
	}
	/*--- end floatToString ---*/
	
	/*----- doubleToString -----*/
	inline string doubleToString(double number)
	{
		stringstream ss;
		ss << std::setprecision(10) << number;
		return ss.str();
	}
	inline string doubleToString(double number, int precision)
	{
		stringstream ss;
		ss << std::setprecision(precision) << number;
		return ss.str();
	}
	/*--- end doubleToString ---*/
	
	//--------------------------------------------------------------------//
	//--------------------- End To String Conversion ---------------------//
	//--------------------------------------------------------------------//
	
	
	
	//--------------------------------------------------------------------//
	//---------------------- From String Conversion ----------------------//
	//--------------------------------------------------------------------//
	
	/*----- stringToNumber -----*/
	template <typename T> T stringToNumber( const string &text, T defValue = T() )
	{
		stringstream ss(text);
		T result;
		return ss >> result ? result : defValue;
	}
	/*--- end stringToNumber -----*/
	
	/*----- stringToBool -----*/
	inline bool stringToBool( const string &text )
	{
		return stringToUpperString(text).compare("TRUE") == 0 ? true : false;
	}
	/*--- end boolToString ---*/
	
	/*----- stringToInt -----*/
	inline int stringToInt( const string &text )
	{
		stringstream ss(text);
		int result;
		return ss >> result ? result : 0;
	}
	/*--- end stringToInt ---*/
	
	/*----- stringToFloat -----*/
	inline float stringToFloat( const string &text )
	{
		stringstream ss(text);
		float result;
		return ss >> result ? result : 0.0f;
	}
	/*--- end stringToFloat ---*/
	
	/*----- stringToDouble -----*/
	inline double stringToDouble( const string &text )
	{
		stringstream ss(text);
		double result;
		return ss >> result ? result : 0.0;
	}
	/*--- end stringToDouble ---*/
	
	/*----- stringToUpperString -----*/
	inline string stringToUpperString( string text )
	{
		transform(text.begin(),text.end(),text.begin(), ::toupper);
		
		return text;
	}
	/*--- end stringToUpperString ---*/
	
	/*----- stringToLowerString -----*/
	inline string stringToLowerString( string text )
	{
		transform(text.begin(),text.end(),text.begin(), ::tolower);
		
		return text;
	}
	/*--- end stringToLowerString ---*/
	
	//--------------------------------------------------------------------//
	//-------------------- End From String Conversion --------------------//
	//--------------------------------------------------------------------//
	
	
}

#endif
