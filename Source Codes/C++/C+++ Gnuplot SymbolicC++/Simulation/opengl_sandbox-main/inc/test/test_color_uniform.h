/*********************************************************************************************************************
 * File : test_color_uniform.h                                                                                       *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef TEST_COLOR_UNIFORM_H
#define TEST_COLOR_UNIFORM_H

#include "test/test.h"

#include "shader.h"
#include "index_buffer.h"
#include "vertex_array.h"

#include <memory>

namespace test
{
    class TestColorUniform : public Test
    {
    public:
        TestColorUniform();
        ~TestColorUniform();

        void on_update(float delta_time) override;
        void on_render() override;
        void on_imgui_render() override;

    private:
        std::unique_ptr<VertexArray> vao_;
        std::unique_ptr<VertexBuffer> vbo_;
        std::unique_ptr<IndexBuffer> ibo_;
        std::unique_ptr<Shader> shader_;

        float red_ = 0.0f;
        float red_increment_ = 0.05f;
    };

} // namespace test

#endif // TEST_COLOR_UNIFORM_H
