/*********************************************************************************************************************
 * File : texture.cpp                                                                                                *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "gl_error_manager.h"
#include "texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string &filepath) : rendered_id_(0),
                                                filepath_(filepath),
                                                local_buffer_(nullptr),
                                                width_(0),
                                                height_(0),
                                                bpp_(0)
{
    stbi_set_flip_vertically_on_load(1); // OpenGL assumes bottom-left to be the origin, and not top-left

    local_buffer_ = stbi_load(filepath.c_str(), &width_, &height_, &bpp_, 4); // RGBA

    GlCall(glGenTextures(1, &rendered_id_));
    bind();

    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0,
                        GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_));
    unbind();

    if (local_buffer_)
        stbi_image_free(local_buffer_); // Free it from the CPU now that it's on the GPU
}

Texture::~Texture()
{
    GlCall(glDeleteTextures(1, &rendered_id_));
}

void Texture::bind(unsigned int slot) const
{
    GlCall(glActiveTexture(GL_TEXTURE0 + slot));
    GlCall(glBindTexture(GL_TEXTURE_2D, rendered_id_));
}

void Texture::unbind() const
{
    GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}