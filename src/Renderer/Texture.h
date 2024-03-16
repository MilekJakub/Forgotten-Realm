#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <STB/stb_image.h>

#include "Shader.h"

class Texture
{
public:
    GLuint Id = 0;
    GLenum type;
    Texture(const char* path, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);

    void TextureUnit(Shader shader, const char* uniform, GLint unit);
    void Bind();
    void Unbind();
    void Delete();
};

#endif //TEXTURE_H
