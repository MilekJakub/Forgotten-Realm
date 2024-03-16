#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include "Renderer/EBO.h"
#include "Renderer/VBO.h"
#include "Renderer/VAO.h"
#include "Renderer/Texture.h"

enum GameState {
    GAME_MENU,
    GAME_ACTIVE
};

class Game
{
public:
    Game();
    ~Game();

    void init();
    void run();

private:
    GLFWwindow* window = nullptr;
    int bufferWidth = 640, bufferHeight = 480; // Dimensions of the framebuffer

    GameState* gameState = nullptr;
    Shader* shader = nullptr;
    VAO* vao = nullptr;
    VBO* vbo = nullptr;
    EBO* ebo = nullptr;
    Texture* texture = nullptr;

    void processInput();
    void update();
    void render();
};

#endif // GAME_H
