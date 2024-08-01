/*********************************************************************************************************************
 * File : test.cpp                                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "test/test.h"
#include "imgui/imgui.h"

namespace test
{
    TestMenu::TestMenu(Test *&crt_test_ptr) : crt_test_(crt_test_ptr)
    {
    }

    void TestMenu::on_update(float delta_time) {}
    void TestMenu::on_render() {}
    void TestMenu::on_imgui_render()
    {
        for (auto &test : tests_)
        {
            // if button pressed
            if (ImGui::Button(test.first.c_str()))
            {
                crt_test_ = test.second();
            }
        }
    }

} // namespace test
