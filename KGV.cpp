// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Util.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Square.h"

using namespace std;

float radian(float rotationDeg)
{
    return rotationDeg * 3.14159 / 180;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "KGV Rendering Multiple Objects (Perlin-C)", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();

    // Rumput
    Square s1;
    s1.setTranslation(0.0f, -0.8f, 0.0f);
    s1.setScale(1.0f, 0.2f, 1.0f);
    s1.setColor(0.1f, 0.8f, 0.0f, 1.0f);

    // Langit
    Square s2;
    s2.setTranslation(0.0f, 0.2f, 0.0f);
    s2.setScale(1.0f, 0.8f, 1.0f);
    s2.setColor(0.1f, 0.8f, 1.0f, 1.0f);

    // Dasar Tiang
    Square s3;
    s3.setTranslation(0.0f, -0.75f, 0.0f);
    s3.setScale(0.2f, 0.05f, 1.0f);
    s3.setColor(0.5f, 0.5f, 0.5f, 1.0f);
    
    // Tiang
    Square s4;
    s4.setTranslation(0.0f, -0.2f, 0.0f);
    s4.setScale(0.1f, 0.5f, 1.0f);
    s4.setColor(0.7f, 0.7f, 0.7f, 1.0f);

    // 0
    // 120
    // 240
    
    // Blade Kincir 1
    Square s5;
    s5.setTranslation(0.06f, 0.65f, 0.0f);
    s5.setRotation(radian(-10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    s5.setScale(0.05f, 0.35f, 1.0f);
    s5.setColor(0.9f, 0.9f, 0.9f, 1.0f);
    
    // Blade Kincir 2
    Square s6;
    s6.setTranslation(0.33f, 0.03f, 0.0f);
    s6.setRotation(radian(-130.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    s6.setScale(0.05f, 0.4f, 1.0f);
    s6.setColor(0.9f, 0.9f, 0.9f, 1.0f);
    
    // Blade Kincir 3
    Square s7;
    s7.setTranslation(-0.4f, 0.15f, 0.0f);
    s7.setRotation(radian(-250.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    s7.setScale(0.05f, 0.4f, 1.0f);
    s7.setColor(0.9f, 0.9f, 0.9f, 1.0f);

    //aku
    // Rotor Kincir
    Square s8;
    s8.setTranslation(0.0f, 0.3f, 0.0f);
    s8.setRotation(radian(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    s8.setScale(0.072f, 0.072f, 1.0f);
    s8.setColor(0.75f, 0.75f, 0.75f, 1.0f);
    
    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint uColor = glGetUniformLocation(program, "uColor");
    GLint uMat4x4 = glGetUniformLocation(program, "transformationMat4x4");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        // Draw
        glUniform4fv(uColor, 1, &s1.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s1.getTransformationMat4x4()[0][0]);
        s1.draw();

        glUniform4fv(uColor, 1, &s2.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s2.getTransformationMat4x4()[0][0]);
        s2.draw();

        glUniform4fv(uColor, 1, &s3.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s3.getTransformationMat4x4()[0][0]);
        s3.draw();
        
        glUniform4fv(uColor, 1, &s4.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s4.getTransformationMat4x4()[0][0]);
        s4.draw();
        
        glUniform4fv(uColor, 1, &s5.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s5.getTransformationMat4x4()[0][0]);
        s5.draw();
        
        glUniform4fv(uColor, 1, &s6.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s6.getTransformationMat4x4()[0][0]);
        s6.draw();
        
        glUniform4fv(uColor, 1, &s7.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s7.getTransformationMat4x4()[0][0]);
        s7.draw();
        
        glUniform4fv(uColor, 1, &s8.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s8.getTransformationMat4x4()[0][0]);
        s8.draw();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
