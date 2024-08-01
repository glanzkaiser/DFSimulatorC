/*********************************************************************************************************************
 * File : texture.h                                                                                                  *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
    Texture(const std::string &filepath);

    ~Texture();

    void bind(unsigned int slot = 0) const;

    void unbind() const;

    inline int get_width() const { return width_; }
    inline int get_height() const { return height_; }

private:
    unsigned int rendered_id_;
    std::string filepath_;
    unsigned char *local_buffer_;

    int width_, height_, bpp_;
};

#endif // TEXTURE_H
