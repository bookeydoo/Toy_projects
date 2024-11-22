#ifndef VBO_class_h
#define VBO_class_h


#include<glad/glad.h>


class VBO {

	public:
		GLuint ID;
		VBO(GLfloat* vertices,GLsizeiptr size);

		void bind();

		void unbind();

		void Delete();
};

#endif