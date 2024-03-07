#define GL_SILENCE_DEPRECATION
#include <exception>
#include <cstdio>
#include "Game.h"

int main(int argc, char *argv[])
{
    try
    {
        Game game;
        game.init();
        game.run();
    }
    catch (const std::exception& e)
    {
        fprintf(stderr, "[ERROR]: %s\n", e.what());
        return 1;
    }

    return 0;
}
