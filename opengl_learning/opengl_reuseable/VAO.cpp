#include "VAO.h"


VAO::VAO(){

	glGenVertexArrays(1, &ID);

}

void VAO::linkAttrib(VBO& vbo, GLuint layout, GLuint Numcomponents, GLenum type, GLsizeiptr stride, void* offset){
	vbo.bind();
	glVertexAttribPointer(layout, Numcomponents,type ,GL_FALSE, stride,offset);
	glEnableVertexAttribArray(layout);
	vbo.unbind();
}

void VAO::bind() {
	glBindVertexArray(ID);
}

void VAO::unbind() {
	glBindVertexArray(0);
}
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}