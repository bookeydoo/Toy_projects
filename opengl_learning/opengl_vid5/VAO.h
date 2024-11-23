#ifndef VAO_class_h
#define VAO_class_h


#include<glad/glad.h>
#include "VBO.h"




class VAO {

public:
	GLuint ID;
	 
	VAO();

	void linkAttrib(VBO& vbo,GLuint layout,GLuint Numcomponents,GLenum type,GLsizeiptr stride,void* offset);
	void bind();

	void unbind();

	void Delete();
};


#endif