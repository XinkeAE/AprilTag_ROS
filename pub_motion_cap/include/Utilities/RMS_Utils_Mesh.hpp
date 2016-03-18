#ifndef _RMS_UTILS_MESH
#define _RMS_UTILS_MESH

/*
//====================================================================//
 
 ==========================
 Joseph DeGol
 UIUC Fall 2012
 ==========================
 RMS_Utils_Mesh: Version 1.0
 ==========================
 
 ================================================================
 RMS_Utils_Mesh.hpp
 This is a 3-dimensional mesh class
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
#include <limits>
#include <cmath>

//Utilities
#include "RMS_Utils_Float_Vertex3.hpp"
#include "RMS_Utils_Face.hpp"

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
//====================== Mesh Class Definition =======================//
//====================================================================//
//====================================================================//
class Mesh
{
	
	
	//---------------------------------------------------------------//
	//------------------------- Private -----------------------------//
	//---------------------------------------------------------------//
	private:
	
		/*----- variables -----*/
		
		//primitives
		static const int FIRST_INDEX = 1;	//	0 or 1
		
		//vectors
		vector<Float_Vertex3> vertex_vector;
		vector<Float_Vertex3> texture_vector;
		vector<Float_Vertex3> normal_vector;
		vector<Face> face_vector;
		
		/*--- end variables ---*/
		
		/*----- methods -----*/
		
		/*--- end methods ---*/
		
	//---------------------------------------------------------------//
	//----------------------- end Private ---------------------------//
	//---------------------------------------------------------------//


	//---------------------------------------------------------------//
	//-------------------------- Public -----------------------------//
	//---------------------------------------------------------------//
	public:
		/*----- Variables -----*/
		Float_Vertex3 minVert;
		Float_Vertex3 maxVert;
		/*--- end Variables ---*/
		
		/*----- Constructors -----*/
		Mesh();
		/*--- end Constructors ---*/
		
		
		/*----- Destructors -----*/
		~Mesh();
		/*--- end Destructors ---*/
		
		/*----- Modifiers -----*/
		void clear();
		void addVertex(const Float_Vertex3& v);
		void addTextureCoord(const Float_Vertex3& vt);
		void addNormal(const Float_Vertex3& vn);
		void addFace(const Face& face);
		void shrink_to_fit();
		/*--- end Modifiers ---*/
		
		/*----- Setters -----*/
		/*--- end Setters ---*/
		
		
		/*----- Getters -----*/
		const bool hasNormals() const;
		const bool hasTextureCoords() const;
		/*--- end Getters ---*/
	
		/*----- Draw Mesh -----*/
		void draw_Mesh();
		void generateFlatNormals();
		/*--- end Draw Mesh ---*/
		
		/*----- Overloaded Operators -----*/
		/*--- end Overloaded Operators ---*/
		
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
//==================== Mesh Class Implementation =====================//
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
	Mesh::Mesh() : minVert(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max())
				 , maxVert(-numeric_limits<float>::max(), -numeric_limits<float>::max(), -numeric_limits<float>::max())
	{
		//push default
		vertex_vector.push_back(Float_Vertex3(0, 0, 0));
		texture_vector.push_back(Float_Vertex3(0, 0, 0));
		normal_vector.push_back(Float_Vertex3(0, 0, 0));
	}
	/*--- end Constructors ---*/
	
	
	/*----- Destructors -----*/
	Mesh::~Mesh() {}
	/*--- end Destructors ---*/
	
	/*----- Modify -----*/
	void Mesh::clear()
	{
		//reset min and max vert
		minVert.set_vertex(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
		maxVert.set_vertex(-numeric_limits<float>::max(), -numeric_limits<float>::max(), -numeric_limits<float>::max());
	
		//clear vectors
		vertex_vector.clear();
		texture_vector.clear();
		normal_vector.clear();
		face_vector.clear();

		//push default
		vertex_vector.push_back(Float_Vertex3(0, 0, 0));
		texture_vector.push_back(Float_Vertex3(0, 0, 0));
		normal_vector.push_back(Float_Vertex3(0, 0, 0));
	}
	
	//shrink to fit
	void Mesh::shrink_to_fit()
	{
		vector<Float_Vertex3>(vertex_vector).swap(vertex_vector);
		vector<Float_Vertex3>(texture_vector).swap(texture_vector);
		vector<Float_Vertex3>(normal_vector).swap(normal_vector);
		vector<Face>(face_vector).swap(face_vector);
		
		for (vector<Face>::iterator it = face_vector.begin(); it != face_vector.end(); ++it) {
			vector<int>((*it).vertex_ind).swap((*it).vertex_ind);
			vector<int>((*it).texture_ind).swap((*it).texture_ind);
			vector<int>((*it).normal_ind).swap((*it).normal_ind);
		}
	}

	//add vertex
	void Mesh::addVertex(const Float_Vertex3& vertex_in)
	{
		//push back
		vertex_vector.push_back(vertex_in);
		
		/*----- bound checking -----*/
		//x
		if (vertex_in.x < minVert.x)
			minVert.x = vertex_in.x;
		if (maxVert.x < vertex_in.x)
			maxVert.x = vertex_in.x;
			
		//y
		if (vertex_in.y < minVert.y)
			minVert.y = vertex_in.y;
		if (maxVert.y < vertex_in.y)
			maxVert.y = vertex_in.y;
			
		//z
		if (vertex_in.z < minVert.z)
			minVert.z = vertex_in.z;
		if (maxVert.z < vertex_in.z)
			maxVert.z = vertex_in.z;
			
		/*--- end bound checking ---*/
	}
	
	//add texture
	void Mesh::addTextureCoord(const Float_Vertex3& texture_in) { texture_vector.push_back(texture_in); }
	
	//add normal
	void Mesh::addNormal(const Float_Vertex3& normal_in) { normal_vector.push_back(normal_in); }
	
	//add face
	void Mesh::addFace(const Face& face) { face_vector.push_back(face); }
	
	/*--- end Modify ---*/
	
	/*----- Setters -----*/
	/*--- end Setters ---*/
	
			
	/*----- Getters -----*/
	const bool Mesh::hasNormals() const { return static_cast<int>(normal_vector.size()) > FIRST_INDEX; }
	const bool Mesh::hasTextureCoords() const { return static_cast<int>(texture_vector.size()) > FIRST_INDEX; }
	/*--- end Getters ---*/
	
	
	/*----- Draw Mesh -----*/
	void Mesh::draw_Mesh()
	{
		//bool isTransparent;
		// bind the texture
		//if (hasTexture()) {
		//	glBindTexture (GL_TEXTURE_2D, m_pTexture->getID());
		//	isTransparent = m_pTexture->isTransparent();
		//}
		//else isTransparent = false;
	
		//bool isDepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
		//if (isTransparent)
		//	glDisable(GL_DEPTH_TEST);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_material.Ka);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_material.Kd);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_material.Ks);
		//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_material.Ns);
		// draw each face...
		for (vector<Face>::const_iterator itFace = face_vector.begin(); itFace != face_vector.end(); ++itFace)
		{
			glColor3f(1, 1, 0);
			glBegin(GL_POLYGON);
			
			for (unsigned i = 0; i < (*itFace).vertex_ind.size(); ++i) {
				glNormal3fv(normal_vector[(*itFace).normal_ind[i]].get_vertex());
				//if (hasTexture() && hasTextureCoords())
				//	glTexCoord3fv(m_texVector[(*itFace).vt[i]].getVertex3fv());
				glVertex3fv(vertex_vector[(*itFace).vertex_ind[i]].get_vertex());
			}
			glEnd();
		}
		
		//	restore depth test
		//if (isDepthTestEnabled)
		//	glEnable(GL_DEPTH_TEST);
		//else
		//	glDisable(GL_DEPTH_TEST);
	}
	
	void Mesh::generateFlatNormals()
	{
		if (hasNormals()) { return; }
		
		// for each face...
		for (vector<Face>::iterator itFace = face_vector.begin(); itFace != face_vector.end(); ++itFace)
		{
			const Float_Vertex3& v1 = vertex_vector[(*itFace).vertex_ind[0]];
			const Float_Vertex3& v2 = vertex_vector[(*itFace).vertex_ind[1]];
			const Float_Vertex3& v3 = vertex_vector[(*itFace).vertex_ind[2]];
			Float_Vertex3 v(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
			Float_Vertex3 w(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
			Float_Vertex3 vn(v.y*w.z - v.z*w.y, v.z*w.x - v.x*w.z, v.x*w.y - v.y*w.x);
			float length = sqrtf(vn.x*vn.x+vn.y*vn.y+vn.z*vn.z);
			if (0 < length) {
				const float a = 1/length;
				vn.x *= a;
				vn.y *= a;
				vn.z *= a;
			}
			normal_vector.push_back(vn);
			
			//	register the generated normal through the face
			fill((*itFace).normal_ind.begin(), (*itFace).normal_ind.end(), normal_vector.size()-1);
		}
	}
	/*--- end Draw Mesh ---*/
	
	//---------------------------------------------------------------//
	//------------------------ end Public ---------------------------//
	//---------------------------------------------------------------//
	
	
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
}

#endif
