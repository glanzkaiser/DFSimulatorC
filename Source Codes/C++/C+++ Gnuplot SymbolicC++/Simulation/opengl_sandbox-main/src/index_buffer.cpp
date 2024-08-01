/*********************************************************************************************************************
 * File : index_buffer.cpp                                                                                           *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "gl_error_manager.h"
#include "index_buffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : count_(count)
{
    assert(sizeof(unsigned int) == sizeof(GLuint));

    GlCall(glGenBuffers(1, &rendered_id_));
    bind();
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GlCall(glDeleteBuffers(1, &rendered_id_));
}

void IndexBuffer::bind() const
{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendered_id_));
}

void IndexBuffer::unbind() const
{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}