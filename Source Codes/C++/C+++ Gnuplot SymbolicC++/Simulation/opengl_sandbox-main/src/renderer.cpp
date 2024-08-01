/*********************************************************************************************************************
 * File : renderer.cpp                                                                                               *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "gl_error_manager.h"
#include "renderer.h"

Renderer::Renderer()
{
    //
}

Renderer::~Renderer()
{
    //
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
    shader.bind();
    va.bind();
    ib.bind();
    GlCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
    GlCall(glClear(GL_COLOR_BUFFER_BIT));
}