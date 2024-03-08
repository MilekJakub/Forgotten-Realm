#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include "Renderer/EBO.h"
#include "Renderer/VBO.h"
#include "Renderer/VAO.h"

class Game
{
public:
    Game();
    ~Game();

    // Initializes the game, including setting up the window and OpenGL context
    void init();

    // Begins the game loop, processing input, updating game state, and rendering
    void run();

private:
    GLFWwindow* window = nullptr;
    int bufferWidth = 640, bufferHeight = 480; // Dimensions of the framebuffer

    Shader* shader = nullptr;
    VAO* vao = nullptr;
    VBO* vbo = nullptr;
    EBO* ebo = nullptr;

    // Process input from the user
    void processInput();

    // Update the game state
    void update();

    // Render the game
    void render();
};

#endif // GAME_H
