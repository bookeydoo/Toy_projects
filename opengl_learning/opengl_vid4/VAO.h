#ifndef VAO_class_h
#define VAO_class_h


#include<glad/glad.h>
#include "VBO.h"




class VAO {

public:
	GLuint ID;
	 
	VAO();

	void linkVBO(VBO vbo,GLuint layout);
	void bind();

	void unbind();

	void Delete();
};


#endif