/*********************************************************************************************************************
 * File : test_dynamic_buffer.cpp                                                                                    *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "constants.h"

#include "gl_error_manager.h"
#include "test/test_dynamic_buffer.h"

#include "renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"

namespace test
{

    TestDynamicBuffer::TestDynamicBuffer() : colors_{{1.f, 0.f, 0.f, 1.0f},
                                                     {0.f, 1.f, 0.f, 1.0f},
                                                     {0.f, 0.f, 1.f, 1.0f},
                                                     {1.f, 1.f, 1.f, 1.0f}},
                                             corners_{-0.5, 0.5, -0.5, 0.5}

    {
        // clang-format off
        // float vertices[] = {
        //     -0.8f, -0.8f, 1.f, 0.f, 0.f, 1.0f, // 0
        //      0.2f, -0.8f, 0.f, 1.f, 0.f, 1.0f, // 1
        //      0.2f,  0.2f, 0.f, 0.f, 1.f, 1.0f, // 2
        //     -0.8f,  0.2f, 0.f, 0.f, 0.f, 1.0f, // 3
        // };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        // clang-format on

        GlCall(glEnable(GL_BLEND));
        GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        vao_ = std::make_unique<VertexArray>();

        vbo_ = std::make_unique<VertexBuffer>(4 * 6 * sizeof(float)); // dynamic
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(4);
        vao_->add_buffer(*vbo_, layout);
        ibo_ = std::make_unique<IndexBuffer>(indices, 6);

        shader_ = std::make_unique<Shader>(shader_dynamic_buffer_path);
    }

    TestDynamicBuffer::~TestDynamicBuffer()
    {
    }

    void TestDynamicBuffer::on_update(float delta_time)
    {
        // clang-format off
        float vertices[] = {
            corners_[0], corners_[2], colors_[0][0], colors_[0][1], colors_[0][2], colors_[0][3], // 0
            corners_[1], corners_[2], colors_[1][0], colors_[1][1], colors_[1][2], colors_[1][3], // 1
            corners_[1], corners_[3], colors_[2][0], colors_[2][1], colors_[2][2], colors_[2][3], // 2
            corners_[0], corners_[3], colors_[3][0], colors_[3][1], colors_[3][2], colors_[3][3], // 3
        };
        // clang-format on
        vbo_->update_buffer(4 * 6 * sizeof(float), vertices);
    }

    void TestDynamicBuffer::on_render()
    {
        GlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GlCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        renderer.draw(*vao_, *ibo_, *shader_);
    }

    void TestDynamicBuffer::on_imgui_render()
    {
        ImGui::ColorEdit4("Color 0", colors_[0]);
        ImGui::ColorEdit4("Color 1", colors_[1]);
        ImGui::ColorEdit4("Color 2", colors_[2]);
        ImGui::ColorEdit4("Color 3", colors_[3]);
        ImGui::DragFloat4("Quad Corners", corners_, 0.01f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

} // namespace test
