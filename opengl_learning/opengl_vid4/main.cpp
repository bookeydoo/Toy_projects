#include<glad/glad.h>
#include<iostream>
#include<GLFW/glfw3.h>
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"
#include "shaderClass.h"





int main() {

	//vertices  coordinates
	GLfloat vertices[] = {
			-0.5f,-0.5f* float((sqrt(3))) / 3, 0.0f,//0 //max left
			0.5f, -0.5f* float((sqrt(3))) / 3, 0.0f,//1 max right 
			0.0f, 0.5f * float((sqrt(3))) / 3, 0.0f,//2 upper mid
			-0.25f,0.0f* float(sqrt(3))/3,0.0f, //3 left upper
			0.0f, -0.5f* float((sqrt(3))) /3, 0.0f,//middle 4
			0.25f,0.0f*float(sqrt(3))/3 , 0.0f,


	};

	GLuint indices[] = {
		0,4,3,
		4,1,5,
		3,5,2
	};



	glfwInit();
	//tell glfw we are using core profile  so we only have the modern functions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//self explanatory 
	GLFWwindow* main_window = glfwCreateWindow(800, 800, "my window", NULL, NULL);

		if (main_window == NULL) {
			std::cout << "sth went wrong ";
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(main_window);
		gladLoadGL();


	glViewport(0, 0, 800, 800);


	
	Shader shaderprogram("default.vert", "default.frag");

	VAO VAO_1;
	
	VAO_1.bind();

	VBO VBO_1(vertices, sizeof(vertices));
	EBO EBO_1(indices, sizeof(indices));

	VAO_1.linkVBO(VBO_1,0);
	VAO_1.unbind();
	EBO_1.unbind();
	VBO_1.unbind();

	while (!glfwWindowShouldClose(main_window)) 
	{

			//specify color of background
			glClearColor(0.07f, 0.13f, 0.2f, 1.0f);
			//clear back buffer and  assign new color to it
			glClear(GL_COLOR_BUFFER_BIT);

			shaderprogram.activate();
	
			VAO_1.bind();
	
			//draw triangle
			glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0 );

			//swap back buffer with front buffer
			glfwSwapBuffers(main_window);

			//take care of all glfw events
			glfwPollEvents();
	}

		//deleting all the objects
			VAO_1.Delete();
			VBO_1.Delete();
			EBO_1.Delete();
			shaderprogram.Delete();
	
			glfwWindowShouldClose(main_window);
			glfwTerminate();
				return 0;
	}