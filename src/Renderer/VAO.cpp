#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &Id);
}

void VAO::LinkVBO(VBO vbo, GLuint layout)
{
    vbo.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
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
