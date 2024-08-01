/*********************************************************************************************************************
 * File : renderer.h                                                                                                 *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef RENDERER_H
#define RENDERER_H

#include "gl_error_manager.h"

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Renderer
{
public:
    Renderer(/* args */);
    ~Renderer();

    void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;

    void clear() const;

private:
    /* data */
};

#endif // RENDERER_H
