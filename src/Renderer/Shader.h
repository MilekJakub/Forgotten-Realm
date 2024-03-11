#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "GL/glew.h"

std::string get_file_contents(const char* filename);

class Shader
{
public:
    GLuint Id = 0;
    Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

    void Activate() const;
    void Delete() const;
};

#endif //SHADER_H
