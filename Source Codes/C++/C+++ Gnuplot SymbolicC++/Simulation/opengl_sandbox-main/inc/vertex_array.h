/*********************************************************************************************************************
 * File : vertex_array.h                                                                                             *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray
{
public:
    VertexArray();

    ~VertexArray();

    void bind() const;

    void unbind() const;

    void add_buffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

private:
    unsigned int rendered_id_;
};

#endif // VERTEX_ARRAY_H
