#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include <STB/stb_image.h>

#include "Game.h"
#include "Renderer/Shader.h"
#include "Renderer/VAO.h"
#include "Renderer/VBO.h"
#include "Renderer/EBO.h"

GLfloat vertices[] =
{
    //    positions              colors         texture coords
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	  0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	  0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	  1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	  1.0f, 0.0f  // Lower right corner
};

GLuint indices[] =
{
    0, 2, 1, // Upper triangle
    0, 3, 2  // Lower triangle
};

GLuint textureId;

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

    glDeleteTextures(1, &textureId);

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

    vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao->LinkAttrib(*vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path projectRootPath = currentPath.parent_path();
    std::filesystem::path texturePath = projectRootPath / "res" / "Textures" / "box.jpeg";

    unsigned char *imageData = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLint tex0Uniform = glGetUniformLocation(shader->Id, "tex0");
    shader->Activate();
    glUniform1i(tex0Uniform, 0);
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
    glBindTexture(GL_TEXTURE_2D, textureId);
    vao->Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
    glfwSwapBuffers(window);
    glfwPollEvents();
}