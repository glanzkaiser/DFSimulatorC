/*********************************************************************************************************************
 * File : test_clear_color.h                                                                                         *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef TEST_CLEAR_COLOR_H
#define TEST_CLEAR_COLOR_H

#include "test/test.h"

namespace test
{
    class TestClearColor : public Test
    {
    public:
        TestClearColor();
        ~TestClearColor();

        void on_update(float delta_time) override;
        void on_render() override;
        void on_imgui_render() override;

    private:
        float clear_color_[4];
    };

} // namespace test

#endif // TEST_CLEAR_COLOR_H
