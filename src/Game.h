#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    GLFWwindow* window;
    int bufferWidth, bufferHeight; // Dimensions of the framebuffer
    GLuint VAO, VBO;
    GLuint shaderProgram;

    // Process input from the user
    void processInput();

    // Update the game state
    void update();

    // Render the game
    void render();
};

#endif // GAME_H
