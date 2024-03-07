#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

#include "Game.h"
#include "Renderer/Shader.h"
#include "Renderer/VAO.h"
#include "Renderer/VBO.h"
#include "Renderer/EBO.h"

// Vertices coordinates
GLfloat vertices[] =
{
    -0.5f,      -0.5f * float(sqrt(3)) / 3,     0.0f, // Lower left corner
     0.5f,      -0.5f * float(sqrt(3)) / 3,     0.0f, // Lower right corner
     0.0f,       0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2,   0.5f * float(sqrt(3)) / 6,     0.0f, // Inner left
     0.5f / 2,   0.5f * float(sqrt(3)) / 6,     0.0f, // Inner right
     0.0f,      -0.5f * float(sqrt(3)) / 3,     0.0f  // Inner down
};

GLuint indices[] =
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

Game::Game()
        : shader("default.vert", "default.frag"), // Initialize shader with vertex and fragment shader file paths
          vbo(vertices, sizeof(vertices)),        // Initialize vbo with vertices array and its size
          ebo(indices, sizeof(indices))           // Initialize ebo with indices array and its size
{

}

Game::~Game()
{
    // Delete all the objects we've created
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::init()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(bufferWidth, bufferHeight, "Forgotten Realm", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }

    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW.");
    }

    glViewport(0, 0, bufferWidth, bufferHeight);

    vao.Bind();


    vao.LinkVBO(vbo, 0);
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    shader.Activate();
    // Bind the VAO so OpenGL knows to use it
    vao.Bind();
    // Draw the triangle using the GL_TRIANGLES primitive
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
    // Take care of all GLFW events
    glfwPollEvents();
}

void Game::run()
{
    double lastFrame = glfwGetTime();
    double thisFrame = lastFrame;
    double deltaTimeAccumulator = 0.0;

    while(!glfwWindowShouldClose(window))
    {
        lastFrame = thisFrame;
        thisFrame = glfwGetTime();
        double deltaTime = thisFrame - lastFrame;
        deltaTimeAccumulator += deltaTime;

        processInput();
        update();
        render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Game::processInput()
{

}

void Game::update()
{

}

void Game::render()
{
    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Tell OpenGL which Shader Program we want to use
    shader.Activate();
    // Bind the VAO so OpenGL knows to use it
    vao.Bind();
    // Draw the triangle using the GL_TRIANGLES primitive
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
    // Take care of all GLFW events
    glfwPollEvents();
}