#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &Id);
}

void VAO::LinkVBO(VBO vbo, GLuint layout)
{
    vbo.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    vbo.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(Id);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &Id);
}
