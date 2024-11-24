#ifndef  shader_class_H
#define  shader_class_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<cerrno>

std::string getfilecontent(const char* filename);

class Shader {
public:
	GLuint ID;
	Shader(const char* vertexfile, const char* fragfile);

	void activate();
	void Delete();

private:
	void compileErrors(unsigned int shader,const char* type);
};

#endif // !shaderClass.h
