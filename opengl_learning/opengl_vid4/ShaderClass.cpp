#include "shaderClass.h"



std::string getfilecontent(const char* filename) {

	std::ifstream in(filename, std::ios::binary);
	if (in)			//means if it opened
	{
		std::string content;
		in.seekg(0, std::ios::end);
		content.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&content[0], content.size());
		in.close();
		return content;
	}
	throw errno;
}

Shader::Shader(const char* vertexfile,const char* fragfile){


	std::string vertexcode = getfilecontent(vertexfile);
	std::string fragcode = getfilecontent(fragfile); 


	const char* vertexsource = vertexcode.c_str();
	const char* fragsource = fragcode.c_str();



	//create vertex shader object and get its reference
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//attaching vertex shader source to the vertex shader object
	glShaderSource(vertexshader, 1, &vertexsource, NULL);

	//compile the vertex shader into machine code
	glCompileShader(vertexshader);


	//create fragment shader object  and gets its reference
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragsource, NULL);
	glCompileShader(fragment_shader);


	//create shader object and get its reference
	ID = glCreateProgram();

	//attach the vertex shader and the fragment shader
	glAttachShader(ID, vertexshader);
	glAttachShader(ID, fragment_shader);

	//link all the shaders together

	glLinkProgram(ID);
	//freeing up the space taken by the shaders
	glDeleteShader(vertexshader);
	glDeleteShader(fragment_shader);



}


void Shader::activate() {

	glUseProgram(ID);
}

void Shader ::Delete(){
	
	glDeleteProgram(ID);
}