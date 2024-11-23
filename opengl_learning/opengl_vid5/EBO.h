#ifndef EBO_class_h
#define EBO_class_h



#include<glad/glad.h>


class EBO {

public:
	GLuint ID;
	EBO(GLuint* vertices, GLsizeiptr size);

	void bind();

	void unbind();

	void Delete();
};

#endif // !1