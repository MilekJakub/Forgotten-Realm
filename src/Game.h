#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include "Renderer/EBO.h"
#include "Renderer/VBO.h"
#include "Renderer/VAO.h"
#include "Renderer/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    int bufferWidth = 800, bufferHeight = 600; // Dimensions of the framebuffer

    GameState* gameState = nullptr;
    Shader* shader = nullptr;
    VAO* vao = nullptr;
    VBO* vbo = nullptr;
    EBO* ebo = nullptr;
    Texture* texture = nullptr;

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    void processInput(double deltaTime);
    void update();
    void render();
};

#endif // GAME_H
