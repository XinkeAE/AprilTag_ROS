#ifndef _RMS_UTILS_GETOPTS
#define _RMS_UTILS_GETOPTS

/*
//====================================================================//
 
 ==========================
 Joseph DeGol
 Neeraj Asthana
 UIUC Spring 2013
 ==========================
 RMS_Utils_GetOpts: Version 1.0
 ==========================
 
 ================================================================
 RMS_Util_GetOpts.hpp
 This is a series of functions for use in other projects relating
 to linux terminal command parsing
 ================================================================
 
 List of Functions:
  ----- Constructors -----
	
	GetOpts();
			
 --- end Constructors ---
			
 ----- GetOpts Methods -----
	
	void Parse(int, char**);
	void Add_Option(string, string, string, void (*)());
	void Add_Option_Group(string, string, string, vector<void (*)()>;
	void Add_Option_Set(string, string, string, bool or int or char or double or float or string);
	void Add_Option_Set_Group(string, string, vector<bool or int or char or double or float or string>)
	void Display_Help();
	
 --- end GetOpts Methods ---
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
#include <stdio.h>
#include <stdlib.h>

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







//====================================================================//
//====================================================================//
//==================== GetOpts Class Definition ======================//
//====================================================================//
//====================================================================//
class GetOpts
{
	//---------------------------------------------------------------//
	//------------------------- Private -----------------------------//
	//---------------------------------------------------------------//
	private:
		/*----- Inner Class -----*/
		class ops{
				public:
					ops(string command_long_param, string command_short_param, string command_description_param, vector<void (*)()> callback_param);
					ops(string command_long_param, string command_short_param, string command_description_param, vector<bool *> bool_param);
					ops(string command_long_param, string command_short_param, string command_description_param, vector<int *> int_param);
					ops(string command_long_param, string command_short_param, string command_description_param, vector<char *> char_param);
					ops(string command_long_param, string command_short_param, string command_description_param, vector<double *> double_param);
					ops(string command_long_param, string command_short_param, string command_description_param, vector<float *> float_param);
					ops(string command_long_param, string command_short_param, string command_description_param, vector<string *> string_param);
					
					string long_option;
					string short_option;
					string description;
				
					/**
					 * 0 - bool
					 * 1 - int
					 * 2 - char
					 * 3 - double
					 * 4 - float
					 * 5 - string
					 * */
					bool position[7] = {false, false, false, false, false, false, false};
					
					vector<void (*)()> callback_pointers;
					vector<bool *> bool_pointers;
					vector<int *> int_pointers;
					vector<char *> char_pointers;
					vector<double *> double_pointers;
					vector<float *> float_pointers;
					vector<string *> string_pointers;
					
					void execute_Action(int argc, char** argv);
					void execute_bool_Action(int argc, char** argv);
					void execute_int_Action(int argc, char** argv);
					void execute_char_Action(int argc, char** argv);
					void execute_double_Action(int argc, char** argv);
					void execute_float_Action(int argc, char** argv);
					void execute_string_Action(int argc, char** argv);
					void execute_callback_Action(int argc, char** argv);
		};
		/*----- end Inner Class -----*/
		
		/*----- Display Methods -----*/
		void Display_Help();
		/*--- end Display Methods ---*/
		
		/*--- Vectors ---*/
		vector<ops> options;
		/*--- end Vectors ---*/
	//---------------------------------------------------------------//
	//----------------------- end Private ---------------------------//
	//---------------------------------------------------------------//


	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	public:
		/*----- Constructors -----*/
		GetOpts();
		/*--- end Constructors ---*/
		
		/*----- Destructors -----*/
		/*--- end Destructors ---*/
		
		/*----- Builder Methods -----*/
		void Add_Option(string command_long_param, string command_short_param, string command_description_param, void (*callback_function_param)());
		void Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, bool * bool_param);
		void Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, int * int_param);
		void Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, char * char_param);
		void Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, double * double_param);
		void Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, float * float_param);
		void Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, string * string_param);
				
		void Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<bool *> param);
		void Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<int *> param);
		void Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<char *> param);
		void Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<double *> param);
		void Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<float *> param);
		void Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<string *> param);
		void Add_Option_Group(string command_long_param, string command_short_param, string command_description_param, vector<void (*)()> param);
		/*--- end Builder Methods ---*/
		
		/*----- Parse -----*/
		void Parse(int argc, char** array);
		/*--- end Parse ---*/

	//---------------------------------------------------------------//
	//------------------------ end Public ---------------------------//
	//---------------------------------------------------------------//
	
	
};//end class definition
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//





//====================================================================//
//====================================================================//
//================== GetOpts Class Implementation ====================//
//====================================================================//
//====================================================================//

	//---------------------------------------------------------------//
	//-------------------------- Private ----------------------------//
	//---------------------------------------------------------------//
	
	/*----- Inner Class Constructors -----*/
	GetOpts::ops::ops(string command_long_param, string command_short_param, string command_description_param, vector<bool *> bool_param):
		long_option(command_long_param), short_option(command_short_param), description(command_description_param), bool_pointers(bool_param){
			position[0] = true;
	}

	GetOpts::ops::ops(string command_long_param, string command_short_param, string command_description_param, vector<int *> int_param):	
		long_option(command_long_param), short_option(command_short_param), description(command_description_param), int_pointers(int_param){
			position[1] = true;
	}

	GetOpts::ops::ops(string command_long_param, string command_short_param, string command_description_param, vector<char *> char_param):
		long_option(command_long_param), short_option(command_short_param), description(command_description_param), char_pointers(char_param){
			position[2] = true;
	}

	GetOpts::ops::ops(string command_long_param, string command_short_param, string command_description_param, vector<double *> double_param):
		long_option(command_long_param), short_option(command_short_param), description(command_description_param), double_pointers(double_param){
			position[3] = true;
	}
	
	GetOpts::ops::ops(string command_long_param, string command_short_param, string command_description_param, vector<float *> float_param):
		long_option(command_long_param), short_option(command_short_param), description(command_description_param), float_pointers(float_param){
			position[4] = true;
	}

	GetOpts::ops::ops(string command_long_param, string command_short_param, string command_description_param, vector<string *> string_param):
		long_option(command_long_param), short_option(command_short_param), description(command_description_param), string_pointers(string_param){
			position[5] = true;
	}
	
	GetOpts::ops::ops(string command_long_param, string command_short_param, string command_description_param, vector<void (*)()> callback_param):
		long_option(command_long_param), short_option(command_short_param), description(command_description_param), callback_pointers(callback_param){
			position[6] = true;
	}
	/*----- end Inner Class Constructors -----*/
	
	/*----- Inner Class Methods -----*/
	void GetOpts::ops::execute_Action(int argc, char** argv){
		int pos;
		for(int i = 0; i < 7; i++)
			if(position[i])
				pos = i;
		if(pos == 0)execute_bool_Action(argc, argv);
		else if(pos == 1)execute_int_Action(argc, argv);
		else if(pos == 2)execute_char_Action(argc, argv);
		else if(pos == 3)execute_double_Action(argc, argv);
		else if(pos == 4)execute_float_Action(argc, argv);
		else if(pos == 5)execute_string_Action(argc, argv);
		else if(pos == 6)execute_callback_Action(argc, argv);
	}

	void GetOpts::ops::execute_bool_Action(int argc, char** argv){
		for(unsigned int i = 2; i < argc && i < (bool_pointers.size()+2); i++){
			string s = argv[i];
			if(s == "true" || s == "TRUE" || s == "True" || s == "T" || s == "t")
				(*bool_pointers[i-2]) = true;
			else
				(*bool_pointers[i-2]) = false;
		}
	}

	void GetOpts::ops::execute_int_Action(int argc, char** argv){
		for(unsigned int i = 2; i < argc && i < (int_pointers.size()+2); i++){
			string s = argv[i];
			(*int_pointers[i-2]) = atoi(s.c_str());
		}
	}

	void GetOpts::ops::execute_char_Action(int argc, char** argv){
		for(unsigned int i = 2; i < argc && i < (char_pointers.size()+2); i++){
			string s = argv[i];
			(*char_pointers[i-2]) = s[0];
		}
	}

	void GetOpts::ops::execute_double_Action(int argc, char** argv){
		for(unsigned int i = 2; i < argc && i < (double_pointers.size()+2); i++){
			string s = argv[i];
			(*double_pointers[i-2]) = atof(s.c_str());
		}
	}

	void GetOpts::ops::execute_float_Action(int argc, char** argv){
		for(unsigned int i = 2; i < argc && i < (float_pointers.size() + 2); i++){
			string s = argv[i];
			(*float_pointers[i-2]) = atof(s.c_str());
		}
	}

	void GetOpts::ops::execute_string_Action(int argc, char** argv){
		for(unsigned int i = 2; i < argc && i < (string_pointers.size() + 2); i++){
			string s = argv[i];
			(*string_pointers[i-2]) = argv[i];
		}
	}

	void GetOpts::ops::execute_callback_Action(int argc, char** argv){
		for(unsigned int i = 0; i < callback_pointers.size(); i++)
			callback_pointers[i]();
	}
	/*----- end Inner Class Methods -----*/	
	
	void GetOpts::Display_Help(){
		cout << "GetOpts Help Options: " << endl;
		for(unsigned int i = 0; i < options.size(); i++){
			string result = options[i].long_option + " [" + options[i].short_option + "]   (" + options[i].description + ")";
			cout << result << endl;
		}
	}
	
	//---------------------------------------------------------------//
	//------------------------ end Private --------------------------//
	//---------------------------------------------------------------//
	
	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//

	/*----- Constructors -----*/
	GetOpts::GetOpts(){}
	/*----- end Constructors -----*/

	/*----- Destructors -----*/
	/*--- end Destructors ---*/
		
	/*----- Builder Methods -----*/
	void GetOpts::Add_Option(string command_long_param, string command_short_param, string command_description_param, void (*callback_param)()){
		vector<void (*)()> temp;
		temp.push_back(callback_param);
		ops o(command_long_param, command_short_param, command_description_param, temp);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Group(string command_long_param, string command_short_param, string command_description_param, vector<void (*)()> param){
		ops o(command_long_param, command_short_param, command_description_param, param);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, bool * bool_param){	
		vector<bool *> temp;
		temp.push_back(bool_param);
		ops o(command_long_param, command_short_param, command_description_param, temp);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, int * int_param){
		vector<int *> temp;
		temp.push_back(int_param);
		ops o(command_long_param, command_short_param, command_description_param, temp);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, char * char_param){	
		vector<char *> temp;
		temp.push_back(char_param);
		ops o(command_long_param, command_short_param, command_description_param, temp);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, double * double_param){
		vector<double *> temp;
		temp.push_back(double_param);
		ops o(command_long_param, command_short_param, command_description_param, temp);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, float * float_param){
		vector<float *> temp;
		temp.push_back(float_param);
		ops o(command_long_param, command_short_param, command_description_param, temp);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set(string command_long_param, string command_short_param, string command_description_param, string * string_param){
		vector<string *> temp;
		temp.push_back(string_param);
		ops o(command_long_param, command_short_param, command_description_param, temp);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<bool *> param){
		ops o(command_long_param, command_short_param, command_description_param, param);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<int *> param){
		ops o(command_long_param, command_short_param, command_description_param, param);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<char *> param){
		ops o(command_long_param, command_short_param, command_description_param, param);
		options.push_back(o);
	}
	
	void GetOpts::Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<double *> param){
		ops o(command_long_param, command_short_param, command_description_param, param);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<float *> param){
		ops o(command_long_param, command_short_param, command_description_param, param);
		options.push_back(o);
	}

	void GetOpts::Add_Option_Set_Group(string command_long_param, string command_short_param, string command_description_param, vector<string *> param){
		ops o(command_long_param, command_short_param, command_description_param, param);
		options.push_back(o);	
	}
	/*----- end Builder Methods -----*/

	/*----- Parse -----*/
	void GetOpts::Parse(int argc, char** argv){
	bool flag = false;
	for(int i = 0; i < argc; i++){
		string s = argv[i];
		if(s == "--help" || s == "-h"){
				Display_Help();
				flag = true;
		}
		for(unsigned int j = 0; j < options.size(); j++){
			if(s == options[j].long_option || s == options[j].short_option){
				options[j].execute_Action(argc, argv);
				flag = true;
			}
		}
	}
	if(!flag)
		cout << "invalid command" << endl;
}
	/*----- end Parse -----*/
	
	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//

#endif
