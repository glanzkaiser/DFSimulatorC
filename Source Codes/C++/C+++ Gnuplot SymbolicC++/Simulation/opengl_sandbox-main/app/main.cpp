/*********************************************************************************************************************
 * File : main.cpp                                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "gl_error_manager.h"

#include <GLFW/glfw3.h>

#include "renderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "test/test_batch_colors.h"
#include "test/test_batch_textures.h"
#include "test/test_dynamic_buffer.h"
#include "test/test_clear_color.h"
#include "test/test_texture_2d.h"
#include "test/test_color_uniform.h"

int main(int argc, const char *argv[])
{
    GLFWwindow *window;

    // Init the Lib
    if (!glfwInit())
        return 1;

    // Create named window and its opengl context
    window = glfwCreateWindow(960, 540, "OpenGL Sandbox", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 2;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        GlCall(glEnable(GL_BLEND));
        GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
        ImGui::StyleColorsDark();

        test::Test *current_test = nullptr;
        test::TestMenu *test_menu = new test::TestMenu(current_test);
        current_test = test_menu;

        test_menu->register_test<test::TestClearColor>("Clear Color");
        test_menu->register_test<test::TestTexture2d>("2D Texture");
        test_menu->register_test<test::TestColorUniform>("Color uniform");
        test_menu->register_test<test::TestBatchColors>("Batch Rendering Colors");
        test_menu->register_test<test::TestBatchTextures>("Batch Rendering Textures");
        test_menu->register_test<test::TestDynamicBuffer>("Dynamic Vertex Buffer");

        test::TestClearColor test;
        while (!glfwWindowShouldClose(window))
        {
            GlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            renderer.clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (current_test)
            {
                current_test->on_update(0.0f);
                current_test->on_render();
                ImGui::Begin("Test");
                if (current_test != test_menu && ImGui::Button("<-"))
                {
                    delete current_test;
                    current_test = test_menu;
                }
                current_test->on_imgui_render();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        if (current_test != test_menu)
            delete test_menu;
        delete current_test;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}