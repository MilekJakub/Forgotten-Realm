#include <GLFW/glfw3.h>

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return 1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (! window)
    {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    return 0;
}