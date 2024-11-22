#include "VBO.h"


VBO::VBO(GLfloat* vertices,GLsizeiptr size) {
	glGenBuffers(1, &ID);
	//bind the VBO as a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	//introduce the vertices into the vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



}


void VBO::bind() {

	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() {
	//we unbind by binding to 0
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VBO::Delete() {

	glDeleteBuffers(1,&ID);
}