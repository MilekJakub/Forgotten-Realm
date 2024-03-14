#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

#include "Game.h"
#include "Renderer/Shader.h"
#include "Renderer/VAO.h"
#include "Renderer/VBO.h"
#include "Renderer/EBO.h"

GLfloat vertices[] =
{
    //                  positions                              colors
    -0.5f,      -0.5f * float(sqrt(3)) / 3,     0.0f,     1.0f, 0.0f, 0.0f, // Lower left corner
     0.5f,      -0.5f * float(sqrt(3)) / 3,     0.0f,     0.0f, 1.0f, 0.0f, // Lower right corner
     0.0f,       0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.0f, 0.0f, 1.0f, // Upper corner
    -0.5f / 2,   0.5f * float(sqrt(3)) / 6,     0.0f,     1.0f, 0.0f, 0.0f, // Inner left
     0.5f / 2,   0.5f * float(sqrt(3)) / 6,     0.0f,     0.0f, 1.0f, 0.0f, // Inner right
     0.0f,      -0.5f * float(sqrt(3)) / 3,     0.0f,     1.0f, 0.0f, 0.0f  // Inner down
};

GLuint indices[] =
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

Game::Game()
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
}

Game::~Game()
{
    ebo->Delete();
    vbo->Delete();
    vao->Delete();
    shader->Delete();

    delete ebo;
    delete vbo;
    delete vao;
    delete shader;

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::init()
{
    shader = new Shader("default.vert", "default.frag");

    vao = new VAO();
    vao->Bind();

    vbo = new VBO(vertices, sizeof(vertices));
    ebo = new EBO(indices, sizeof(indices));

    vao->LinkVBO(*vbo, 0);
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
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
    }
}

void Game::processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Game::update()
{

}

void Game::render()
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader->Activate();
    vao->Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
    glfwSwapBuffers(window);
    glfwPollEvents();
}