/*********************************************************************************************************************
 * File : vertex_buffer_layout.cpp                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "gl_error_manager.h"
#include "vertex_buffer_layout.h"

unsigned int VertexBufferElement::get_size_of_type(unsigned int type)
{
    switch (type)
    {
    case GL_FLOAT:
        return sizeof(GLfloat);
    case GL_UNSIGNED_INT:
        return sizeof(GLuint);
    case GL_UNSIGNED_BYTE:
        return sizeof(GLubyte);
    }
    assert(false);
    return 0;
}

VertexBufferLayout::VertexBufferLayout() : stride_(0) {}

VertexBufferLayout::~VertexBufferLayout() {}

template <>
void VertexBufferLayout::push<float>(unsigned int count)
{
    elements_.push_back({GL_FLOAT, count, GL_FALSE});
    stride_ += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    elements_.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    stride_ += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
    elements_.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    stride_ += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
}