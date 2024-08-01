/*********************************************************************************************************************
 * File : test_texture_2d.cpp                                                                                        *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "constants.h"

#include "gl_error_manager.h"
#include "test/test_texture_2d.h"

#include "renderer.h"
#include "imgui/imgui.h"

namespace test
{

    TestTexture2d::TestTexture2d() : translation_a_(200, 200, 0),
                                     translation_b_(400, 200, 0)
    {
        // clang-format off
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
             50.0f, -50.0f, 1.0f, 0.0f, // 1
             50.0f,  50.0f, 1.0f, 1.0f, // 2
            -50.0f,  50.0f, 0.0f, 1.0f  // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        // clang-format on

        GlCall(glEnable(GL_BLEND));
        GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        vao_ = std::make_unique<VertexArray>();

        vbo_ = std::make_unique<VertexBuffer>(4 * 4 * sizeof(float), positions);
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        vao_->add_buffer(*vbo_, layout);
        ibo_ = std::make_unique<IndexBuffer>(indices, 6);

        proj_ = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        view_ = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        shader_ = std::make_unique<Shader>(shader_texture_path);
        shader_->bind();
        texture_ = std::make_unique<Texture>(image_mines_path);
        texture_->bind();
        shader_->set_uniform1i("u_Texture", 0);
    }

    TestTexture2d::~TestTexture2d()
    {
    }

    void TestTexture2d::on_update(float delta_time)
    {
    }

    void TestTexture2d::on_render()
    {
        GlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GlCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        texture_->bind();
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation_a_);
            glm::mat4 mvp = proj_ * view_ * model;
            shader_->bind();
            shader_->set_uniformMat4f("u_MVP", mvp);
            renderer.draw(*vao_, *ibo_, *shader_);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation_b_);
            glm::mat4 mvp = proj_ * view_ * model;
            shader_->bind();
            shader_->set_uniformMat4f("u_MVP", mvp);
            renderer.draw(*vao_, *ibo_, *shader_);
        }
    }

    void TestTexture2d::on_imgui_render()
    {
        ImGui::SliderFloat3("Translation A", &translation_a_.x, 0.0f, 960.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat3("Translation B", &translation_b_.x, 0.0f, 960.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

} // namespace test
