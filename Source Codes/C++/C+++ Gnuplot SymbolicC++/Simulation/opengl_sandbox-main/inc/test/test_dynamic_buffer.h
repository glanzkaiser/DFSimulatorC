/*********************************************************************************************************************
 * File : test_dynamic_buffer.h                                                                                      *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef TEST_BATCH_DYNAMIC_BUFFER_H
#define TEST_BATCH_DYNAMIC_BUFFER_H

#include "test/test.h"

#include "shader.h"
#include "index_buffer.h"
#include "vertex_array.h"

#include <memory>

namespace test
{
    class TestDynamicBuffer : public Test
    {
    public:
        TestDynamicBuffer();
        ~TestDynamicBuffer();

        void on_update(float delta_time) override;
        void on_render() override;
        void on_imgui_render() override;

    private:
        std::unique_ptr<VertexArray> vao_;
        std::unique_ptr<VertexBuffer> vbo_;
        std::unique_ptr<IndexBuffer> ibo_;
        std::unique_ptr<Shader> shader_;

        float colors_[4][4];
        float corners_[4];
    };

} // namespace test

#endif // TEST_BATCH_DYNAMIC_BUFFER_H
