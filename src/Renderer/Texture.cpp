#include "Texture.h"

Texture::Texture(const char* imageName, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = textureType;
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path projectRootPath = currentPath.parent_path();
    std::filesystem::path texturePath = projectRootPath / "res" / "textures" / imageName;

    unsigned char *imageBytes = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    glGenTextures(1, &Id);
    glActiveTexture(slot);
    glBindTexture(textureType, Id);

    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(textureType, 0, GL_RGBA, width, height, 0, format, pixelType, imageBytes);
    glGenerateMipmap(textureType);

    stbi_image_free(imageBytes);
    glBindTexture(textureType, 0);
}

void Texture::TextureUnit(Shader shader, const char *uniform, GLint unit)
{
    GLint tex0Uniform = glGetUniformLocation(shader.Id, uniform);
    shader.Activate();
    glUniform1i(tex0Uniform, unit);
}

void Texture::Bind()
{
    glBindTexture(type, Id);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &Id);
}