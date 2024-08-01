/*********************************************************************************************************************
 * File : test_color_uniform.cpp                                                                                     *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "constants.h"

#include "gl_error_manager.h"
#include "test/test_color_uniform.h"

#include "renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"

namespace test
{

    TestColorUniform::TestColorUniform()
    {
        // clang-format off
        float positions[] = {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f,  0.5f, // 2
            -0.5f,  0.5f  // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        // clang-format on

        GlCall(glEnable(GL_BLEND));
        GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        vao_ = std::make_unique<VertexArray>();

        vbo_ = std::make_unique<VertexBuffer>(4 * 2 * sizeof(float), positions);
        VertexBufferLayout layout;
        layout.push<float>(2);
        vao_->add_buffer(*vbo_, layout);
        ibo_ = std::make_unique<IndexBuffer>(indices, 6);

        shader_ = std::make_unique<Shader>(shader_color_uniform_path);
        shader_->bind();
        shader_->set_uniform4f("u_Color", glm::vec4(0.0f, 0.3f, 0.8f, 1.0f));
    }

    TestColorUniform::~TestColorUniform()
    {
    }

    void TestColorUniform::on_update(float delta_time)
    {
        if (red_ > 1.0f)
            red_increment_ = -0.05f;
        else if (red_ < 0.0f)
            red_increment_ = +0.05f;
        red_ += red_increment_;
    }

    void TestColorUniform::on_render()
    {
        GlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GlCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        shader_->bind();
        shader_->set_uniform4f("u_Color", glm::vec4(red_, 0.3f, 0.8f, 1.0f));
        renderer.draw(*vao_, *ibo_, *shader_);
    }

    void TestColorUniform::on_imgui_render()
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

} // namespace test
