#ifndef VAO_H
#define VAO_H

#include "GL/glew.h"
#include "VBO.h"

class VAO
{
public:
    GLuint Id = 0;
    VAO();

    void LinkVBO(VBO vbo, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();
};

#endif //VAO_H
