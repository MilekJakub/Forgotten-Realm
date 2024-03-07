#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include "GL/glew.h"

std::string get_file_contents(const char* filename);

class Shader
{
public:
    GLuint Id;
    Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

    void Activate();
    void Delete();
};

#endif //SHADER_H
