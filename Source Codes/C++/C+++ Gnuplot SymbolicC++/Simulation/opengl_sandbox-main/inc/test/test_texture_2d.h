/*********************************************************************************************************************
 * File : test_texture_2d.h                                                                                          *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef TEST_TEXTURE_2D_H
#define TEST_TEXTURE_2D_H

#include "test/test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "shader.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "texture.h"

#include <memory>

namespace test
{
    class TestTexture2d : public Test
    {
    public:
        TestTexture2d();
        ~TestTexture2d();

        void on_update(float delta_time) override;
        void on_render() override;
        void on_imgui_render() override;

    private:
        glm::vec3 translation_a_;
        glm::vec3 translation_b_;

        glm::mat4 proj_;
        glm::mat4 view_;

        std::unique_ptr<VertexArray> vao_;
        std::unique_ptr<VertexBuffer> vbo_;
        std::unique_ptr<IndexBuffer> ibo_;
        std::unique_ptr<Shader> shader_;
        std::unique_ptr<Texture> texture_;
    };

} // namespace test

#endif // TEST_TEXTURE_2D_H
