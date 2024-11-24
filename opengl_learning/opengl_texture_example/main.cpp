#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"
#include "shaderClass.h"
#include <stb_image.h>

int main() {
    // Vertex data (with texture coordinates)
    GLfloat vertices[] = {
        // Positions         // Colors           // Texture Coords
        -0.5f, -0.5f, 0.0f,  0.5f, 0.4f, 0.3f,   0.0f, 0.0f,  // 0
        0.5f, -0.5f, 0.0f,   0.5f, 0.4f, 0.3f,   1.0f, 0.0f,  // 1
        0.0f,  0.5f, 0.0f,   0.8f, 0.4f, 0.3f,   0.5f, 1.0f   // 2
    };

    GLuint indices[] = { 0, 1, 2 };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* main_window = glfwCreateWindow(800, 800, "Texture Example", NULL, NULL);
    if (main_window == NULL) {
        std::cout << "Error initializing GLFW" << std::endl;
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

    VAO_1.linkAttrib(VBO_1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); // Positions
    VAO_1.linkAttrib(VBO_1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Colors
    VAO_1.linkAttrib(VBO_1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture Coords

    VAO_1.unbind();
    EBO_1.unbind();
    VBO_1.unbind();

    // Load image
    int widthImg, HeightImg, NumColCh;
    unsigned char* imagebytes = stbi_load("Cool.jpg", &widthImg, &HeightImg, &NumColCh, 0);

    if (!imagebytes) {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum format;
    if (NumColCh == 1) format = GL_RED;
    else if (NumColCh == 3) format = GL_RGB;
    else if (NumColCh == 4) format = GL_RGBA;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, widthImg, HeightImg, 0, format, GL_UNSIGNED_BYTE, imagebytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imagebytes);

    while (!glfwWindowShouldClose(main_window)) {
        glClearColor(0.07f, 0.13f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderprogram.activate();
        // Set texture unit 0 (you can use other units if needed)
        glUniform1i(glGetUniformLocation(shaderprogram.ID, "texture1"), 0);

        // Bind the texture to texture unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        VAO_1.bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }

    // Cleanup
    VAO_1.Delete();
    VBO_1.Delete();
    EBO_1.Delete();
    glDeleteTextures(1, &texture);
    shaderprogram.Delete();
    glfwTerminate();

    return 0;
}
