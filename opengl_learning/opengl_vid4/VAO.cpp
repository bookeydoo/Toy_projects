#include "VAO.h"


VAO::VAO(){

	glGenVertexArrays(1, &ID);

}

void VAO::linkVBO(VBO vbo, GLuint layout) {
	vbo.bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0,(void*)0);
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