/*********************************************************************************************************************
 * File : test_clear_color.cpp                                                                                       *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "gl_error_manager.h"
#include "test/test_clear_color.h"

#include "imgui/imgui.h"

namespace test
{

    TestClearColor::TestClearColor() : clear_color_{0.2f, 0.3f, 0.8f, 1.0f}
    {
    }

    TestClearColor::~TestClearColor()
    {
    }

    void TestClearColor::on_update(float delta_time)
    {
    }

    void TestClearColor::on_render()
    {
        GlCall(glClearColor(clear_color_[0], clear_color_[1], clear_color_[2], clear_color_[3]));
        GlCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::on_imgui_render()
    {
        ImGui::ColorEdit4("Clear Color", clear_color_);
    }

} // namespace test
