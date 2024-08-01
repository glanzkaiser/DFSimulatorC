/*********************************************************************************************************************
 * File : vertex_array.cpp                                                                                           *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "gl_error_manager.h"
#include "vertex_array.h"

VertexArray::VertexArray()
{
    GlCall(glGenVertexArrays(1, &rendered_id_));
}

VertexArray::~VertexArray()
{
    GlCall(glDeleteVertexArrays(1, &rendered_id_));
}

void VertexArray::bind() const
{
    GlCall(glBindVertexArray(rendered_id_));
}

void VertexArray::unbind() const
{
    GlCall(glBindVertexArray(rendered_id_));
}

void VertexArray::add_buffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    bind();
    vb.bind();

    const auto &elements = layout.get_elements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        GlCall(glEnableVertexAttribArray(i));
        GlCall(glVertexAttribPointer(i, element.count, element.type,
                                     element.normalized, layout.get_stride(),
                                     reinterpret_cast<const void *>((const intptr_t)offset)));
        // Warning: OpenGL is expected to pass integer offset into argument defined as pointer
        // It's very C-style and not very safe
        offset += element.count * VertexBufferElement::get_size_of_type(element.type);
    }
}