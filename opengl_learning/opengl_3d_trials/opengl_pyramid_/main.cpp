#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"
#include "shaderClass.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>


#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
    GLfloat vertices[] = {
        // Positions         // Colors
        -0.5f, -0.5f, 0.0f,  0.5f, 0.4f, 0.3f,
        0.5f, -0.5f, 0.0f,   0.5f, 0.4f, 0.3f,
        0.0f,  0.5f, 0.0f,   0.8f, 0.4f, 0.3f,
    };

    GLfloat PyramidVerts[] = {
        // Positions         // Colors
        0.5f, 0, 0,         0.5f, 0.4f, 0.3f, // 0
        -0.5f, 0, 0,        0.5f, 0.4f, 0.3f, // 1
        0.0f, 0.5f, 0,      0.8f, 0.4f, 0.3f, // 2
        0.0f, 0, 0.5f,      0.8f, 0.4f, 0.3f, // 3
    };

    GLuint indices[] = { 0, 1, 2 };
    GLuint pyramidIndices[] = { 0, 3, 1, 1, 3, 2, 0, 1, 2 };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* main_window = glfwCreateWindow(800, 800, "3D Example", NULL, NULL);
    if (main_window == NULL) {
        std::cout << "Error initializing GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(main_window);
    gladLoadGL();

    glViewport(0, 0, 800, 800);

    Shader shaderprogram("default.vert", "default.frag");

    VAO VAO_1, VAO_2;
    
    //this is for the triangle object
    VAO_1.bind();
    VBO VBO_1(vertices, sizeof(vertices));
    EBO EBO_1(indices, sizeof(indices));
    VAO_1.linkAttrib(VBO_1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0); // Positions
    VAO_1.linkAttrib(VBO_1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Colors

    // Set up VAO, VBO, and EBO for the pyramid
    VAO_2.bind();
    VBO VBO_2(PyramidVerts, sizeof(PyramidVerts));
    EBO EBO_2(pyramidIndices, sizeof(pyramidIndices));

    VAO_2.linkAttrib(VBO_2, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);  // Positions
    VAO_2.linkAttrib(VBO_2, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Colors

    VAO_1.unbind();
    VAO_2.unbind();
    EBO_1.unbind();
    EBO_2.unbind();
    VBO_1.unbind();
    VBO_2.unbind();

    // Init IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(main_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool drawTrig = true; // Flag to toggle between drawing triangle and pyramid

    while (!glfwWindowShouldClose(main_window)) {
        glClearColor(0.07f, 0.13f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shaderprogram.activate();

        // Draw the triangle or pyramid based on the flag
        if (drawTrig) {
            VAO_1.bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); 
            VAO_1.unbind();
        }
        else {
            VAO_2.bind();
            glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); 
            VAO_2.unbind();
        }

        // IMGUI Render
        ImGui::Begin("Hello, World!");
        ImGui::Text("It is working!!");
        ImGui::Checkbox("Draw triangle?", &drawTrig); // Toggle triangle/pyramid
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }

    // Cleanup
    VAO_1.Delete();
    VBO_1.Delete();
    EBO_1.Delete();
    VAO_2.Delete();
    VBO_2.Delete();
    EBO_2.Delete();
    shaderprogram.Delete();
    glfwTerminate();

    return 0;
}
