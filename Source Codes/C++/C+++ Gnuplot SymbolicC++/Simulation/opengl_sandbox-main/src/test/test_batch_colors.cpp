/*********************************************************************************************************************
 * File : test_batch_colors.cpp                                                                                      *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "constants.h"

#include "gl_error_manager.h"
#include "test/test_batch_colors.h"

#include "renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"

namespace test
{

    TestBatchColors::TestBatchColors()
    {
        // clang-format off
        float positions[] = {
            -0.8f, -0.8f, 1.f, 0.f, 0.f, 1.0f, // 0
             0.2f, -0.8f, 0.f, 1.f, 0.f, 1.0f, // 1
             0.2f,  0.2f, 0.f, 0.f, 1.f, 1.0f, // 2
            -0.8f,  0.2f, 0.f, 0.f, 0.f, 1.0f, // 3

             0.3f,  0.3f, 0.f, 1.f, 1.f, 1.0f, // 4
             0.7f,  0.3f, 1.f, 1.f, 0.f, 1.0f, // 5
             0.7f,  0.7f, 1.f, 0.f, 1.f, 1.0f, // 6
             0.3f,  0.7f, 1.f, 1.f, 1.f, 1.0f  // 7
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4
        };
        // clang-format on

        GlCall(glEnable(GL_BLEND));
        GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        vao_ = std::make_unique<VertexArray>();

        vbo_ = std::make_unique<VertexBuffer>(8 * 6 * sizeof(float), positions);
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(4);
        vao_->add_buffer(*vbo_, layout);
        ibo_ = std::make_unique<IndexBuffer>(indices, 12);

        shader_ = std::make_unique<Shader>(shader_colors_path);
    }

    TestBatchColors::~TestBatchColors()
    {
    }

    void TestBatchColors::on_update(float delta_time)
    {
    }

    void TestBatchColors::on_render()
    {
        GlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GlCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        renderer.draw(*vao_, *ibo_, *shader_);
    }

    void TestBatchColors::on_imgui_render()
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

} // namespace test
