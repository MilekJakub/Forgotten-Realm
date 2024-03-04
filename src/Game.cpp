#include "Game.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

Game::Game() : window(nullptr), bufferWidth(640), bufferHeight(480)
{
}

Game::~Game()
{
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}