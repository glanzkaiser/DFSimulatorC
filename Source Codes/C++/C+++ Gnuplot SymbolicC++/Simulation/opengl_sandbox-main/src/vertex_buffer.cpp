/*********************************************************************************************************************
 * File : vertex_buffer.cpp                                                                                          *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "gl_error_manager.h"
#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(unsigned int bytes_size, const void *data)
{
    GlCall(glGenBuffers(1, &rendered_id_));
    bind();
    GlCall(glBufferData(GL_ARRAY_BUFFER, bytes_size, data, (data ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW)));
}

VertexBuffer::~VertexBuffer()
{
    GlCall(glDeleteBuffers(1, &rendered_id_));
}

void VertexBuffer::bind() const
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, rendered_id_));
}

void VertexBuffer::unbind() const
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::update_buffer(unsigned int bytes_size, const void *data)
{
    bind();
    GlCall(glBufferSubData(GL_ARRAY_BUFFER, 0, bytes_size, data));
}
