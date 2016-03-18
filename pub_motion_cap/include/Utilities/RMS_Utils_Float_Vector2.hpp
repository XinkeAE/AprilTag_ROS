#ifndef _RMS_UTILS_FLOAT_VECTOR2
#define _RMS_UTILS_FLOAT_VECTOR2

/*
//====================================================================//
 
 ==========================
 Joseph DeGol
 UIUC Fall 2012
 ==========================
 RMS_Utils_Float_Vector2: Version 1.0
 ==========================
 
 ================================================================
 RMS_Utils_Float_Vector2.hpp
 This is a class for 2-dim vectors
 ================================================================
 
 List of Functions:
 
 ----- Constructors -----
	
	
			
 --- end Constructors ---

 
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
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

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
//================= Float Vector2 Class Definition ===================//
//====================================================================//
//====================================================================//
class Float_Vector2
{
	
	//---------------------------------------------------------------//
	//------------------------- Private -----------------------------//
	//---------------------------------------------------------------//
	private:
		float Data[2];
	//---------------------------------------------------------------//
	//----------------------- end Private ---------------------------//
	//---------------------------------------------------------------//


	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	public:
	
		/*----- Constructors -----*/
		Float_Vector2();
		Float_Vector2( const Float_Vector2 &float_vector2_param );
		Float_Vector2( float x_param, float y_param );
		Float_Vector2( const Float_Vector2 float_vector2_point1_param, const Float_Vector2 float_vector2_point2_param );
		/*--- end Constructors ---*/
		
		/*----- Destructors -----*/
		~Float_Vector2();
		/*--- end Destructors ---*/
		
		/*----- Getters -----*/
		void Get( float &x_param, float &y_param );
		float* Get( );
		float Get_X( );
		float Get_Y( );
		/*--- end Getters ---*/
		
		/*----- Setters -----*/
		void Set( float x_param, float y_param );
		/*--- end Setters ---*/
		
		/*----- Mods -----*/
		float Length();
		void ScaleByFloats( float scale_x, float scale_y );
		void DivideByFloats( float divide_x, float divide_y );
		void Negate( );
		float Dot2( const Float_Vector2 &float_vector2_param ) const;
		/*--- end Mods ---*/
		
		/*----- Static Operations -----*/
		friend void Add( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, const Float_Vector2 &float_vector2_b_param );
		friend void Subtract( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, const Float_Vector2 &float_vector2_b_param );
		
		friend void CopyScale( Float_Vector2 &float_vector2_destination_param, const Float_Vector2 &float_vector2_source_param, float scale_param );
		friend void AddScale( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, const Float_Vector2 &float_vector2_b_param, float scale_param );
		friend void Average( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, const Float_Vector2 &float_vector2_b_param );
		friend void WeightedAdd( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, float scale_a_param ,const Float_Vector2 &float_vector2_b_param, float scale_b_param );
		/*--- end Static Operations ---*/
		
		/*----- Operator Overloads -----*/
		float operator[](int i) const;
		Float_Vector2& operator=(const Float_Vector2 &float_vector2_param);
		int operator==(const Float_Vector2 &float_vector2_param) const;
		int operator!=(const Float_Vector2 &float_vecto2_param);
		Float_Vector2& operator+=(const Float_Vector2 &float_vector2_param);
		Float_Vector2& operator-=(const Float_Vector2 &float_vector2_param);
		Float_Vector2& operator*=(float f_param);
		Float_Vector2& operator/=(float f_param);
		/*--- end Operator Overloads ---*/
		
		/*----- Output -----*/
		//void Write( File *F = stdout );
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
//=============== Float Vector2 Class Implementation =================//
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
	Float_Vector2::Float_Vector2() 
	{ 
		Data[0] = 0; 
		Data[1] = 0; 
	}
	Float_Vector2::Float_Vector2( const Float_Vector2 &float_vector2_param ) 
	{ 
		Data[0] = float_vector2_param.Data[0]; 
		Data[1] = float_vector2_param.Data[1]; 
	}
	Float_Vector2::Float_Vector2( float x_param, float y_param ) 
	{ 
		Data[0] = x_param; 
		Data[1] = y_param; 
	}
	Float_Vector2::Float_Vector2( const Float_Vector2 float_vector2_point1_param, const Float_Vector2 float_vector2_point2_param )
	{
		Data[0] = float_vector2_point1_param.Data[0] - float_vector2_point2_param.Data[0];
		Data[1] = float_vector2_point1_param.Data[1] - float_vector2_point2_param.Data[1];
	}
	/*--- end Constructors ---*/
	
	
	/*----- Destructors -----*/
	Float_Vector2::~Float_Vector2() {	}
	/*--- end Destructors ---*/
	
	
	/*----- Getters -----*/
	void Float_Vector2::Get( float &x_param, float &y_param ) { x_param = Data[0]; y_param = Data[1]; }
	float* Float_Vector2::Get( ) { return Data; };
	float Float_Vector2::Get_X( ) { return Data[0]; }
	float Float_Vector2::Get_Y( ) { return Data[1]; }
	/*--- end Getters ---*/
	
	
	/*----- Setters -----*/
	void Float_Vector2::Set( float x_param, float y_param ) { Data[0] = x_param; Data[1] = y_param; }
	/*--- end Setters ---*/
		
		
	/*----- Mods -----*/
	float Float_Vector2::Length() { return sqrt( Data[0] * Data[0] + Data[1] * Data[1] ); }
	void Float_Vector2::ScaleByFloats( float scale_x_param, float scale_y_param ) { Data[0] *= scale_x_param; Data[1] *= scale_y_param; }
	void Float_Vector2::DivideByFloats( float divide_x_param, float divide_y_param ) 
	{
		if ( divide_x_param == 0 || divide_y_param == 0 ) { cout << "RMS_Utils_Float_Vector2 :: DivideByFloats : Can't divide by zero... skipping method call." << endl; } 
		Data[0] /= divide_x_param; 
		Data[1] /= divide_y_param; 
	}
	void Float_Vector2::Negate( ) { Data[0] = -Data[0]; Data[1] = -Data[1]; }
	float Float_Vector2::Dot2( const Float_Vector2 &float_vector2_param ) const { return Data[0]*float_vector2_param.Data[0] + Data[1]*float_vector2_param.Data[1]; }
	/*--- end Mods ---*/
	
	
	/*----- Static Operations -----*/
	void Add( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, const Float_Vector2 &float_vector2_b_param )
	{ 
		float_vector2_result_param.Data[0] = float_vector2_a_param.Data[0] + float_vector2_b_param.Data[0];
		float_vector2_result_param.Data[1] = float_vector2_a_param.Data[1] + float_vector2_b_param.Data[1];
	}
	void Subtract( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, const Float_Vector2 &float_vector2_b_param )
	{
		float_vector2_result_param.Data[0] = float_vector2_a_param.Data[0] - float_vector2_b_param.Data[0];
		float_vector2_result_param.Data[1] = float_vector2_a_param.Data[1] - float_vector2_b_param.Data[1];
	}
		
	void CopyScale( Float_Vector2 &float_vector2_destination_param, const Float_Vector2 &float_vector2_source_param, float scale_param )
	{
		float_vector2_destination_param.Data[0] = float_vector2_source_param.Data[0] * scale_param;
		float_vector2_destination_param.Data[1] = float_vector2_source_param.Data[1] * scale_param;
	}
	void AddScale( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, const Float_Vector2 &float_vector2_b_param, float scale_param )
	{
		float_vector2_result_param.Data[0] = float_vector2_a_param.Data[0] + float_vector2_b_param.Data[0] * scale_param;
		float_vector2_result_param.Data[1] = float_vector2_a_param.Data[1] + float_vector2_b_param.Data[1] * scale_param;
	}
	void Average( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, const Float_Vector2 &float_vector2_b_param )
	{
		float_vector2_result_param.Data[0] = ( float_vector2_a_param.Data[0] + float_vector2_b_param.Data[0] ) * 0.5f;
		float_vector2_result_param.Data[1] = ( float_vector2_a_param.Data[1] + float_vector2_b_param.Data[1] ) * 0.5f;
	}
	void WeightedAdd( Float_Vector2 &float_vector2_result_param, const Float_Vector2 &float_vector2_a_param, float scale_a_param ,const Float_Vector2 &float_vector2_b_param, float scale_b_param )
	{
		float_vector2_result_param.Data[0] = float_vector2_a_param.Data[0] * scale_a_param + float_vector2_b_param.Data[0] * scale_b_param;
		float_vector2_result_param.Data[1] = float_vector2_a_param.Data[1] * scale_a_param + float_vector2_b_param.Data[1] * scale_b_param;
	}
	/*--- end Static Operations ---*/
		
		
	/*----- Operator Overloads -----*/
	float Float_Vector2::operator[](int i) const
	{
		assert ( i >= 0 && i < 2 );
		return Data[i];
	}
	Float_Vector2& Float_Vector2::operator=(const Float_Vector2 &float_vector2_param)
	{
		Data[0] = float_vector2_param.Data[0];
		Data[1] = float_vector2_param.Data[1];
		return *this;
	}
	int Float_Vector2::operator==(const Float_Vector2 &float_vector2_param) const
	{
		return ( (Data[0] == float_vector2_param.Data[0]) && (Data[1] == float_vector2_param.Data[1]) );
	}
	int Float_Vector2::operator!=(const Float_Vector2 &float_vector2_param)
	{
		return ( (Data[0] != float_vector2_param.Data[0]) || (Data[1] != float_vector2_param.Data[1]) );
	}
	Float_Vector2& Float_Vector2::operator+=(const Float_Vector2 &float_vector2_param)
	{
		Data[0] += float_vector2_param.Data[0];
		Data[1] += float_vector2_param.Data[1];
		return *this;
	}
	Float_Vector2& Float_Vector2::operator-=(const Float_Vector2 &float_vector2_param)
	{
		Data[0] -= float_vector2_param.Data[0];
		Data[1] -= float_vector2_param.Data[1];
		return *this;
	}
	Float_Vector2& Float_Vector2::operator*=(float f_param)
	{
		Data[0] *= f_param;
		Data[1] *= f_param;
		return *this;
	}
	Float_Vector2& Float_Vector2::operator/=(float f_param)
	{
		Data[0] /= f_param;
		Data[1] /= f_param;
		return *this;
	}
	/*--- end Operator Overloads ---*/
		
		
	/*----- Output -----*/
	//void Write( File *F = stdout )
	//{
	//	fprintf ( F, "%f %f\n", Data[0], Data[1] );
	//}
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
