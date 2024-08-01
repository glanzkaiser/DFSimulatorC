/*********************************************************************************************************************
 * File : test.h                                                                                                     *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef TEST_H
#define TEST_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace test
{
    class Test
    {
    public:
        Test() = default;
        virtual ~Test() = default;

        virtual void on_update(float delta_time) {}
        virtual void on_render() {}
        virtual void on_imgui_render() {}
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test *&crt_test_ptr);
        virtual ~TestMenu() = default;

        void on_update(float delta_time) override;
        void on_render() override;
        void on_imgui_render() override;

        template <typename T>
        void register_test(const std::string &name);

    private:
        using TestLambda = std::function<Test *()>;

        Test *&crt_test_;
        std::vector<std::pair<std::string, TestLambda>> tests_;
    };

    template <typename T>
    void TestMenu::register_test(const std::string &name)
    {
        std::cout << "Register test " << name << std::endl;
        tests_.push_back(std::make_pair(name, []() { return new T(); }));
    }

} // namespace test

#endif // TEST_H
