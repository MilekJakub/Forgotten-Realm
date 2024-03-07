#ifndef EBO_H
#define EBO_H

#include "GL/glew.h"

class EBO
{
public:
    GLuint Id = 0;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};

#endif //EBO_H
