#ifndef _RMS_UTILS_OPENGL_MODEL_PARSER
#define _RMS_UTILS_OPENGL_MODEL_PARSER

/*
//====================================================================//
 
 ==========================
 Joseph DeGol
 UIUC Fall 2012
 ==========================
 RMS_Utils_OpenGL_Model_Parser: Version 1.0
 ==========================
 
 ================================================================
 RMS_Utils_OpenGL_Model_Parser.hpp
 This is a series of functions for use in other projects relating
 to parsing model files for OpenGL
 ================================================================
 
 List of Functions:
 
//====================================================================//
*/




//====================================================================//
//====================================================================//
//============================ Preamble ==============================//
//====================================================================//
//====================================================================//


//---------------------------------------------------------------//
//------------------------- Includes ----------------------------//
//---------------------------------------------------------------//

//system
#include <iostream>
#include <fstream>
#include <vector>

//Utilities
#include "RMS_Utils_Mesh.hpp"

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
//============== OpenGL_Model_Parser Class Definition ================//
//====================================================================//
//====================================================================//
class OpenGL_Model_Parser
{
	
	
	//---------------------------------------------------------------//
	//------------------------- Private -----------------------------//
	//---------------------------------------------------------------//
	private:
	
		/*----- variables -----*/
		string myFileName;
		bool verbose;
		Mesh *obj_mesh;
		/*--- end variables ---*/
		
		/*----- methods -----*/
		
		//parsing
		void skipLine(istream &inFile);
		bool skipCommentLine(istream &inFile);
		bool processLine(istream& inFile);
		
		//output
		void writeSuccess(const char *msg);
		void writeSuccess(const char *msg, string msg_obj);
		void writeError(const char *error_msg);
		void writeError(const char *error_msg, string error_obj);
		
		/*--- end methods ---*/
		
	//---------------------------------------------------------------//
	//----------------------- end Private ---------------------------//
	//---------------------------------------------------------------//


	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	public:
	
		/*----- Constructors -----*/
		OpenGL_Model_Parser();
		OpenGL_Model_Parser(bool verb);
		OpenGL_Model_Parser(char *fileName);
		OpenGL_Model_Parser(char *fileName, bool verb);
		OpenGL_Model_Parser(const char *fileName);
		OpenGL_Model_Parser(const char *fileName, bool verb);
		OpenGL_Model_Parser(string fileName);
		OpenGL_Model_Parser(string fileName, bool verb);
		/*--- end Constructors ---*/
		
		
		/*----- Destructors -----*/
		~OpenGL_Model_Parser();
		/*--- end Destructors ---*/
		
		
		/*----- Setters -----*/
		
		//myFileName
		void setFileName(char *fileName);
		void setFileName(string fileName);
		
		/*--- end Setters ---*/
		
		
		/*----- Getters -----*/
		
		//myFileName
		const char* getFileName_cstr();
		string getFileName();
		
		/*--- end Getters ---*/
		
		
		/*----- Model Loading -----*/
		
		//Load Obj Model
		bool Load_Obj_Model();
		
		/*--- end Model Loading ---*/
		
		/*----- Drawing -----*/
		
		//Draw Obj Model
		void Draw_Obj_Model();
		void Look_At_Model();
		
		/*--- end Drawing ---*/
		
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
//============ OpenGL_Model_Parser Class Implementation ==============//
//====================================================================//
//====================================================================//


	//---------------------------------------------------------------//
	//-------------------------- Private ----------------------------//
	//---------------------------------------------------------------//
	
	/*----- Parsing -----*/
	
	//skip a line
	void OpenGL_Model_Parser::skipLine(istream& inFile)
	{
		char next;
		inFile >> std::noskipws;
		while( (inFile >> next) && ('\n' != next) );
	}

	//skip a comment line
	bool OpenGL_Model_Parser::skipCommentLine(istream& inFile)
	{
		char next;
		while( inFile >> std::skipws >> next ) 
	    {
			inFile.putback(next);
			if ( next == '#') {	skipLine(inFile); }
			else { 	return true; }
	    }
	    return false;
	}
	
	//parse line
	bool OpenGL_Model_Parser::processLine(istream& inFile)
	{
		/*----- set up -----*/
		//variables
		string ele_id;
		float x, y, z;    
		
		//read in identifier, exit if failure
		if (!(inFile >> ele_id)){ return false; }
		
		/*--- end set up ---*/
		
		
		/*----- parse line -----*/
		
		//vertex
		if ("v" == ele_id) 
		{
			inFile >> x >> y >> z;
			obj_mesh->addVertex(Float_Vertex3(x, y, z));
		}
		
		//texture data
		else if ("vt" == ele_id) {	// texture data
			inFile >> x >> y >> z;
			inFile.clear();                           // is z (i.e. w) is not available, have to clear error flag.
			obj_mesh->addTextureCoord(Float_Vertex3(x, y, z));
		}
		
		//normal data
		else if ("vn" == ele_id) {	// normal data
			inFile >> x >> y >> z;
			if(!inFile.good()) 
			{
				x = y = z = 0.0;
				inFile.clear();
				skipLine(inFile);
			}
			obj_mesh->addNormal(Float_Vertex3(x, y, z));
		}
		
		//face data
		else if ("f" == ele_id) 
		{
			int vi[10];                               // vertex indices.
			int ni[10] = { -1, -1, -1, -1, };         // normal indices.
			int ti[10] = { -1, -1, -1, -1, };         // tex indices.
			
			int i = 0;
			for (char c; i<10; ++i) 
			{
				if(!obj_mesh->hasTextureCoords() && !obj_mesh->hasNormals()) { inFile >> vi[i]; }
				else if(!obj_mesh->hasTextureCoords()) { inFile >> vi[i] >> c >> c >> ni[i]; }
				else if(!obj_mesh->hasNormals()) { inFile >> vi[i] >> c >> ti[i]; }
				else { inFile >> vi[i] >> c >> ti[i] >> c >>  ni[i]; }
				
				if(!inFile.good()) { break; }
			}
			
			//	Create the polygon face
			Face face;
			for (int k=0; k < i; ++k)
				face.Add_Vert_Tex_Norm(vi[k], ti[k], ni[k]);
			obj_mesh->addFace(face);
			
			inFile.clear();
		}
		
		//else skip (not handling materials right now)
		else { skipLine(inFile); }
		
		/*----- end parse line -----*/
		
		//return
		return true;
	}
	/*--- end Parsing ---*/

	/*----- Output -----*/
	void OpenGL_Model_Parser::writeSuccess(const char *msg)
	{
		cout << "RMS_Utils_OpenGL_Model_Parser :: " << msg << endl;
	}
	void OpenGL_Model_Parser::writeSuccess(const char *msg, string msg_obj)
	{
		cout << "RMS_Utils_OpenGL_Model_Parser :: " << msg << msg_obj << endl;
	}		
	void OpenGL_Model_Parser::writeError(const char *error_msg)
	{
		cout << "RMS_Utils_OpenGL_Model_Parser :: Error: " << error_msg << endl;
	}
	void OpenGL_Model_Parser::writeError(const char *error_msg, string error_obj)
	{
		cout << "RMS_Utils_OpenGL_Model_Parser :: Error: " << error_msg << error_obj << endl;
	}
	/*--- end Output ---*/
	
	//---------------------------------------------------------------//
	//------------------------ end Private --------------------------//
	//---------------------------------------------------------------//
	
	
	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	
	/*----- Constructors -----*/
	OpenGL_Model_Parser::OpenGL_Model_Parser() : myFileName("No File Name Given"), verbose(false) { obj_mesh = new Mesh; }
	OpenGL_Model_Parser::OpenGL_Model_Parser(bool verb) : myFileName("No File Name Given"), verbose(verb) { obj_mesh = new Mesh; }
	OpenGL_Model_Parser::OpenGL_Model_Parser(char *fileName) : myFileName( string(fileName) ) , verbose(false) { obj_mesh = new Mesh; }
	OpenGL_Model_Parser::OpenGL_Model_Parser(char *fileName, bool verb) : myFileName( string(fileName) ) , verbose(verb) { obj_mesh = new Mesh; }
	OpenGL_Model_Parser::OpenGL_Model_Parser(const char *fileName) : myFileName( string(fileName) ) , verbose(false) { obj_mesh = new Mesh; }
	OpenGL_Model_Parser::OpenGL_Model_Parser(const char *fileName, bool verb) : myFileName( string(fileName) ) , verbose(verb) { obj_mesh = new Mesh; }
	OpenGL_Model_Parser::OpenGL_Model_Parser(string fileName) : myFileName( fileName ), verbose(false) { obj_mesh = new Mesh; }
	OpenGL_Model_Parser::OpenGL_Model_Parser(string fileName, bool verb) : myFileName( fileName ), verbose(verb) { obj_mesh = new Mesh; }
	/*--- end Constructors ---*/
	
	
	/*----- Destructors -----*/
	OpenGL_Model_Parser::~OpenGL_Model_Parser()
	{
		
	}
	/*--- end Destructors ---*/
	
	
	/*----- Setters -----*/
			
	//myFileName
	void OpenGL_Model_Parser::setFileName(char *fileName) { myFileName = string(fileName); }
	void OpenGL_Model_Parser::setFileName(string fileName) { myFileName = fileName; }
			
	/*--- end Setters ---*/
	
			
	/*----- Getters -----*/
			
	//myFileName
	const char* OpenGL_Model_Parser::getFileName_cstr() { return myFileName.c_str(); }
	string OpenGL_Model_Parser::getFileName() { return myFileName; }
			
	/*--- end Getters ---*/
			
			
	/*----- Model Loading -----*/
	
	//Load Obj Model
	bool OpenGL_Model_Parser::Load_Obj_Model()
	{
		
		/*----- Open and Check File -----*/
		
		//create ifstream, open to end
		ifstream inFile( myFileName.c_str(), ios::in | ios::ate);
		
		
		//if error opening file, return
		if ( !inFile.is_open() ) { writeError("Could not open file: ",myFileName); return false; }
		else if( verbose ) { writeSuccess("Obj File Opened Successfully: ", myFileName); }
		
		
		//check if file is empty
		const int fileSize = inFile.tellg();
		inFile.seekg (0, ios::beg);
		if ( fileSize == 0) { writeError("Obj file is empty: " ,myFileName); return false; }
		
		/*--- End Open and Check File ---*/
		
		/*----- Parse File -----*/
		
		obj_mesh->clear();

		while(skipCommentLine(inFile)) 
		{
			if (processLine(inFile) == false) { break; }
		}
		
		obj_mesh->shrink_to_fit();
		
		/*--- end Parse File ---*/
		
		/*----- Exit -----*/
		inFile.close();
		return true;
		/*--- end Exit ---*/
	}
	
	/*--- end Model Loading ---*/
	
	
	/*----- Drawing -----*/
	
	//Draw Obj Model
	void OpenGL_Model_Parser::Draw_Obj_Model() { obj_mesh->draw_Mesh(); obj_mesh->generateFlatNormals(); }
	void OpenGL_Model_Parser::Look_At_Model() 
	{
		double centerx = (obj_mesh->minVert.x + obj_mesh->maxVert.x) * .5;
		double centery = (obj_mesh->minVert.y + obj_mesh->maxVert.y) * .5;
		double centerz = (obj_mesh->minVert.z + obj_mesh->maxVert.z) * .5;
		cout << centerx << " " << centery << " " << centerz << endl;
		gluLookAt(0,0,0,centerx,centery,centerz,0,1,0); 
	}
	
	/*--- end Drawing ---*/

	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	
	
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
}

#endif
