#ifndef _RMS_UTILS_FLOAT_VECTOR3
#define _RMS_UTILS_FLOAT_VECTOR3

/*
//====================================================================//
 
 ==========================
 Joseph DeGol
 UIUC Fall 2012
 ==========================
 RMS_Utils_Float_Vector3: Version 1.0
 ==========================
 
 ================================================================
 RMS_Utils_Float_Vector3.hpp
 This is a class for 3-dim vectors
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
//================= Float Vector3 Class Definition ===================//
//====================================================================//
//====================================================================//
class Float_Vector3
{
	
	//---------------------------------------------------------------//
	//------------------------- Private -----------------------------//
	//---------------------------------------------------------------//
	private:
		float Data[3];
	//---------------------------------------------------------------//
	//----------------------- end Private ---------------------------//
	//---------------------------------------------------------------//


	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	public:
	
		/*----- Constructors -----*/
		Float_Vector3();
		Float_Vector3( const Float_Vector3 &float_vector3_param );
		Float_Vector3( float x_param, float y_param, float z_param );
		Float_Vector3( const Float_Vector3 float_vector3_point1_param, const Float_Vector3 float_vector3_point2_param );
		/*--- end Constructors ---*/
		
		/*----- Destructors -----*/
		~Float_Vector3();
		/*--- end Destructors ---*/
		
		/*----- Getters -----*/
		void Get( float &x_param, float &y_param, float &z_param );
		float* Get( );
		float Get_X( );
		float Get_Y( );
		float Get_Z( );
		float Get_R( );
		float Get_G( );
		float Get_B( );
		/*--- end Getters ---*/
		
		/*----- Setters -----*/
		void Set( float x_param, float y_param, float z_param );
		void Set_X( float x_param );
		void Set_Y( float y_param );
		void Set_Z( float z_param );
		/*--- end Setters ---*/
		
		/*----- Mods -----*/
		float Length();
		void ScaleByFloats( float scale_x, float scale_y, float scale_z );
		void DivideByFloats( float divide_x, float divide_y, float divide_z );
		void Negate( );
		void Normalize( );
		float Dot3( const Float_Vector3 &float_vector3_param ) const;
		static void Cross3 ( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param );
		/*--- end Mods ---*/
		
		/*----- Static Operations -----*/
		friend void Add( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param );
		friend void Subtract( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param );
		
		friend void CopyScale( Float_Vector3 &float_vector3_destination_param, const Float_Vector3 &float_vector3_source_param, float scale_param );
		friend void AddScale( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param, float scale_param );
		friend void Average( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param );
		friend void WeightedAdd( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, float scale_a_param ,const Float_Vector3 &float_vector3_b_param, float scale_b_param );
		/*--- end Static Operations ---*/
		
		/*----- Operator Overloads -----*/
		float operator[](int i) const;
		Float_Vector3& operator=(const Float_Vector3 &float_vector3_param);
		int operator==(const Float_Vector3 &float_vector3_param);
		int operator!=(const Float_Vector3 &float_vector3_param);
		Float_Vector3& operator+=(const Float_Vector3 &float_vector3_param);
		Float_Vector3& operator-=(const Float_Vector3 &float_vector3_param);
		Float_Vector3& operator*=(float f_param);
		Float_Vector3& operator/=(float f_param);
		friend Float_Vector3 operator+(const Float_Vector3 &float_vector3_1_param, const Float_Vector3 &float_vector3_2_param);
		friend Float_Vector3 operator-(const Float_Vector3 &float_vector3_1_param, const Float_Vector3 &float_vector3_2_param);
		friend Float_Vector3 operator*(const Float_Vector3 &float_vector3_param, float scale_param);
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
//=============== Float Vector3 Class Implementation =================//
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
	Float_Vector3::Float_Vector3() 
	{ 
		Data[0] = 0; 
		Data[1] = 0;
		Data[2] = 0;
	}
	Float_Vector3::Float_Vector3( const Float_Vector3 &float_vector3_param ) 
	{ 
		Data[0] = float_vector3_param.Data[0]; 
		Data[1] = float_vector3_param.Data[1]; 
		Data[2] = float_vector3_param.Data[2];
	}
	Float_Vector3::Float_Vector3( float x_param, float y_param, float z_param ) 
	{ 
		Data[0] = x_param; 
		Data[1] = y_param; 
		Data[2] = z_param;
	}
	Float_Vector3::Float_Vector3( const Float_Vector3 float_vector3_point1_param, const Float_Vector3 float_vector3_point2_param )
	{
		Data[0] = float_vector3_point1_param.Data[0] - float_vector3_point2_param.Data[0];
		Data[1] = float_vector3_point1_param.Data[1] - float_vector3_point2_param.Data[1];
		Data[2] = float_vector3_point1_param.Data[2] - float_vector3_point2_param.Data[2];
	}
	/*--- end Constructors ---*/
	
	
	/*----- Destructors -----*/
	Float_Vector3::~Float_Vector3() {	}
	/*--- end Destructors ---*/
	
	
	/*----- Getters -----*/
	void Float_Vector3::Get( float &x_param, float &y_param, float &z_param ) { x_param = Data[0]; y_param = Data[1]; z_param = Data[2]; }
	float* Float_Vector3::Get( ) { return Data; };
	float Float_Vector3::Get_X( ) { return Data[0]; }
	float Float_Vector3::Get_Y( ) { return Data[1]; }
	float Float_Vector3::Get_Z( ) { return Data[2]; }
	float Float_Vector3::Get_R( ) { return Data[0]; }
	float Float_Vector3::Get_G( ) { return Data[1]; }
	float Float_Vector3::Get_B( ) { return Data[2]; }
	/*--- end Getters ---*/
	
	
	/*----- Setters -----*/
	void Float_Vector3::Set( float x_param, float y_param, float z_param ) { Data[0] = x_param; Data[1] = y_param; Data[2] = z_param; }
	void Float_Vector3::Set_X( float x_param ) { Data[0] = x_param; }
	void Float_Vector3::Set_Y( float y_param ) { Data[1] = y_param; }
	void Float_Vector3::Set_Z( float z_param ) { Data[2] = z_param; }
	/*--- end Setters ---*/
		
		
	/*----- Mods -----*/
	float Float_Vector3::Length() { return sqrt( Data[0] * Data[0] + Data[1] * Data[1] + Data[2] * Data[2] ); }
	void Float_Vector3::ScaleByFloats( float scale_x_param, float scale_y_param, float scale_z_param ) 
	{ 
		Data[0] *= scale_x_param; 
		Data[1] *= scale_y_param; 
		Data[2] *= scale_z_param; 
	}
	void Float_Vector3::DivideByFloats( float divide_x_param, float divide_y_param, float divide_z_param ) 
	{
		if ( divide_x_param == 0 || divide_y_param == 0 || divide_z_param == 0 ) { cout << "RMS_Utils_Float_Vector2 :: DivideByFloats : Can't divide by zero... skipping method call." << endl; } 
		Data[0] /= divide_x_param; 
		Data[1] /= divide_y_param;
		Data[2] /= divide_z_param;
	}
	void Float_Vector3::Negate( ) 
	{ 
		Data[0] = -Data[0]; 
		Data[1] = -Data[1]; 
		Data[2] = -Data[2]; 
	}
	void Float_Vector3::Normalize( )
	{
		float length = Length();
		if ( length > 0 ) { Data[0] /= length; Data[1] /= length; Data[2] /= length; }
	}
	float Float_Vector3::Dot3( const Float_Vector3 &float_vector3_param ) const 
	{ 
		return Data[0]*float_vector3_param.Data[0] + Data[1]*float_vector3_param.Data[1] + Data[2]*float_vector3_param.Data[2]; 
	}
	void Float_Vector3::Cross3 ( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param ) 
	{ 
		float x = float_vector3_a_param[1] * float_vector3_b_param[2] - float_vector3_a_param[2] * float_vector3_b_param[1];
		float y = float_vector3_a_param[2] * float_vector3_b_param[0] - float_vector3_a_param[0] * float_vector3_b_param[2];
		float z = float_vector3_a_param[0] * float_vector3_b_param[1] - float_vector3_a_param[1] * float_vector3_b_param[0];
		float_vector3_result_param.Data[0] = x;
		float_vector3_result_param.Data[1] = y;
		float_vector3_result_param.Data[2] = z;
	}
	/*--- end Mods ---*/
	
	
	/*----- Static Operations -----*/
	void Add( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param )
	{ 
		float_vector3_result_param.Data[0] = float_vector3_a_param.Data[0] + float_vector3_b_param.Data[0];
		float_vector3_result_param.Data[1] = float_vector3_a_param.Data[1] + float_vector3_b_param.Data[1];
		float_vector3_result_param.Data[2] = float_vector3_a_param.Data[2] + float_vector3_b_param.Data[2];
	}
	void Subtract( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param )
	{
		float_vector3_result_param.Data[0] = float_vector3_a_param.Data[0] - float_vector3_b_param.Data[0];
		float_vector3_result_param.Data[1] = float_vector3_a_param.Data[1] - float_vector3_b_param.Data[1];
		float_vector3_result_param.Data[2] = float_vector3_a_param.Data[2] - float_vector3_b_param.Data[2];
	}
	void CopyScale( Float_Vector3 &float_vector3_destination_param, const Float_Vector3 &float_vector3_source_param, float scale_param )
	{
		float_vector3_destination_param.Data[0] = float_vector3_source_param.Data[0] * scale_param;
		float_vector3_destination_param.Data[1] = float_vector3_source_param.Data[1] * scale_param;
		float_vector3_destination_param.Data[2] = float_vector3_source_param.Data[2] * scale_param;
	}
	void AddScale( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param, float scale_param )
	{
		float_vector3_result_param.Data[0] = float_vector3_a_param.Data[0] + float_vector3_b_param.Data[0] * scale_param;
		float_vector3_result_param.Data[1] = float_vector3_a_param.Data[1] + float_vector3_b_param.Data[1] * scale_param;
		float_vector3_result_param.Data[2] = float_vector3_a_param.Data[2] + float_vector3_b_param.Data[2] * scale_param;
	}
	void Average( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, const Float_Vector3 &float_vector3_b_param )
	{
		float_vector3_result_param.Data[0] = ( float_vector3_a_param.Data[0] + float_vector3_b_param.Data[0] ) * 0.5f;
		float_vector3_result_param.Data[1] = ( float_vector3_a_param.Data[1] + float_vector3_b_param.Data[1] ) * 0.5f;
		float_vector3_result_param.Data[2] = ( float_vector3_a_param.Data[2] + float_vector3_b_param.Data[2] ) * 0.5f;
	}
	void WeightedAdd( Float_Vector3 &float_vector3_result_param, const Float_Vector3 &float_vector3_a_param, float scale_a_param ,const Float_Vector3 &float_vector3_b_param, float scale_b_param )
	{
		float_vector3_result_param.Data[0] = float_vector3_a_param.Data[0] * scale_a_param + float_vector3_b_param.Data[0] * scale_b_param;
		float_vector3_result_param.Data[1] = float_vector3_a_param.Data[1] * scale_a_param + float_vector3_b_param.Data[1] * scale_b_param;
		float_vector3_result_param.Data[2] = float_vector3_a_param.Data[2] * scale_a_param + float_vector3_b_param.Data[2] * scale_b_param;
	}
	/*--- end Static Operations ---*/
		
		
	/*----- Operator Overloads -----*/
	float Float_Vector3::operator[](int i) const
	{
		assert ( i >= 0 && i < 3 );
		return Data[i];
	}
	Float_Vector3& Float_Vector3::operator=(const Float_Vector3 &float_vector3_param)
	{
		Data[0] = float_vector3_param.Data[0];
		Data[1] = float_vector3_param.Data[1];
		Data[2] = float_vector3_param.Data[2];
		return *this;
	}
	int Float_Vector3::operator==(const Float_Vector3 &float_vector3_param)
	{
		return ( (Data[0] == float_vector3_param.Data[0]) && (Data[1] == float_vector3_param.Data[1]) && (Data[2] == float_vector3_param.Data[2]) );
	}
	int Float_Vector3::operator!=(const Float_Vector3 &float_vector3_param)
	{
		return ( (Data[0] != float_vector3_param.Data[0]) || (Data[1] != float_vector3_param.Data[1]) || (Data[2] != float_vector3_param.Data[2]) );
	}
	Float_Vector3& Float_Vector3::operator+=(const Float_Vector3 &float_vector3_param)
	{
		Data[0] += float_vector3_param.Data[0];
		Data[1] += float_vector3_param.Data[1];
		Data[2] += float_vector3_param.Data[2];
		return *this;
	}
	Float_Vector3& Float_Vector3::operator-=(const Float_Vector3 &float_vector3_param)
	{
		Data[0] -= float_vector3_param.Data[0];
		Data[1] -= float_vector3_param.Data[1];
		Data[2] -= float_vector3_param.Data[2];
		return *this;
	}
	Float_Vector3& Float_Vector3::operator*=(float f_param)
	{
		Data[0] *= f_param;
		Data[1] *= f_param;
		Data[2] *= f_param;
		return *this;
	}
	Float_Vector3& Float_Vector3::operator/=(float f_param)
	{
		Data[0] /= f_param;
		Data[1] /= f_param;
		Data[2] /= f_param;
		return *this;
	}
	Float_Vector3 operator+(const Float_Vector3 &float_vector3_1_param, const Float_Vector3 &float_vector3_2_param)
	{
		Float_Vector3 float_vector3_result;
		Add( float_vector3_result, float_vector3_1_param, float_vector3_2_param );
		return float_vector3_result;
	}
	Float_Vector3 operator-(const Float_Vector3 &float_vector3_1_param, const Float_Vector3 &float_vector3_2_param)
	{
		Float_Vector3 float_vector3_result;
		Subtract( float_vector3_result, float_vector3_1_param, float_vector3_2_param );
		return float_vector3_result;
	}
	Float_Vector3 operator*(const Float_Vector3 &float_vector3_param, float scale_param)
	{
		Float_Vector3 float_vector3_result;
		CopyScale( float_vector3_result, float_vector3_param, scale_param );
		return float_vector3_result;
	}
	/*--- end Operator Overloads ---*/
		
		
	/*----- Output -----*/
	//void Float_Vector3::Write( File *F = stdout )
	//{
	//	fprintf ( F, "%f %f %f\n", Data[0], Data[1], Data[2] );
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
