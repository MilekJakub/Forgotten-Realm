#ifndef VBO_H
#define VBO_H

#include "GL/glew.h"

class VBO
{
public:
    GLuint Id = 0;
    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};

#endif //VBO_H
