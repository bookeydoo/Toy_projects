#include<glad/glad.h>
#include<iostream>
#include<GLFW/glfw3.h>




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
	GLFWwindow* main_window = glfwCreateWindow(400, 400, "my window", NULL, NULL);

		if (main_window == NULL) {
			std::cout << "sth went wrong ";
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(main_window);
		gladLoadGL();


	glViewport(0, 0, 800, 800);


	//create reference containers for vertex array object and vertex buffer object
	GLuint VBO,VAO ,EBO; //vertex buffer object 
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO); 
	glGenBuffers(1, &EBO);
	//make the VAO the current vertex array object by binding it
	glBindVertexArray(VAO);

	//bind the VBO as a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	//introduce the vertices into the vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//configure the vertex attribute so that opengl knows how to read the vbo
	glVertexAttribPointer(0,3,GL_FLOAT,false,3*sizeof(GL_FLOAT),(void*)0);

	//enable the vertex attribute so it can be used
	glEnableVertexAttribArray(0);
	//binding their values to 0 for some reason??
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0) ;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(main_window)) {

	//specify color of background
	glClearColor(0.07f, 0.13f, 0.2f, 1.0f);
	//clear back buffer and  assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);


	//specify which shader program to use
	

	//BIND VAO
 	glBindVertexArray(VAO);
	
	//draw triangle
	glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0 );

	//swap back buffer with front buffer
	glfwSwapBuffers(main_window);

	//take care of all glfw events
	glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	glfwWindowShouldClose(main_window);
	glfwTerminate();
		return 0;
	}