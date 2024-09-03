// Modification from Markus Buchholz, 2023
// https://github.com/markusbuchholz/Fourier-Series-in-Cpp-ImGui/
// Merci beaucoup Freya, Sentinel, RK.

#include <stdafx.hpp>
#include "imgui_helper.hpp"
#include "ball.h"
#include <tuple>
#include <thread>
#include <chrono>
#include <vector>
#include <math.h>
#include <list>
#include <numeric>

using namespace std;

int main(int argc, char const *argv[])
{

	int w = 1280;
	int h = 720;
	std::string title = "Hyperbola Type 2 Simulation";
	initImgui(w, h, title);

	// simulation state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(89.0f / 255.0, 88.0f / 255.0, 87.0f / 255.0, 1.00f);
	ImVec4 ray_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 ray_color2 = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

	// Main loop
	int i = 0;
	bool flag = true;
	std::list<ImVec2> wave_tail;
	std::list<int> test;


	while (!glfwWindowShouldClose(window) && flag == true)
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		ImGuiWindowFlags window_flags = 0;
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiCond_FirstUseEver);
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

		ImGui::Begin("Simulation", nullptr, window_flags);
		ImDrawList *draw_list = ImGui::GetWindowDrawList();

		float strokex = 600.0; // the hyperbola' center x-coordinate 
		float strokey = 410.0; // the hyperbola' center y-coordinate 

		static int alpha = 5;
		static int beta = 3;		

		ImVec2 wave_N1 = {sinhf((float)i)*alpha + strokex, coshf((float)i)*beta + strokey};
		ImVec2 wave_N2 = {sinhf((float)i)*alpha + strokex, -coshf((float)i)*beta + strokey};
		ImVec2 wave_N3 = {-sinhf((float)i)*alpha + strokex, coshf((float)i)*beta + strokey};
		ImVec2 wave_N4 = {-sinhf((float)i)*alpha + strokex, -coshf((float)i)*beta + strokey};
		
		wave_tail.push_front(wave_N1);
		wave_tail.push_front(wave_N2);
		wave_tail.push_front(wave_N3);
		wave_tail.push_front(wave_N4);

		// This for loop is the one drawing the hyperbola that is being drawn
		for (auto &it : wave_tail)
		{
			draw_list->AddCircleFilled(it, 6.0, IM_COL32(65, 0, 255, 255));
		}

		i++;
		// the if statement to restart the drawing after variable i reach 1001		
		if (i > 100)
		{
			wave_tail.erase(wave_tail.begin(), wave_tail.end());
			i = 0;
		}
		// To draw the hyperbola with explicit function
		struct Funcs
		{
		static float Hyperbola1(void*, int i) { return sqrt( pow(beta,2) * ((pow(-i,2) / pow(alpha,2)) + 1))  ;  }
		static float Hyperbola2(void*, int i) { return - sqrt( pow(beta,2) * ((pow(-i,2) / pow(alpha,2)) + 1))  ;  }
		};
		static int func_type = 0, display_count = 50;
		ImGui::Combo("func", &func_type, "Hyperbola1\0Hyperbola2");
		float (*func)(void*, int) = (func_type == 0) ? Funcs::Hyperbola1 : Funcs::Hyperbola2;

		// PlotLines (const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, 
		// int values_offset=0, const char* overlay_text = NULL, 
		// float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = (ImVec(0,100)); 	
		ImGui::PlotLines("", func, NULL, display_count, -25, NULL, -25.0f, 50.0f, ImVec2(0, 100));
	
		ImGui::PushItemWidth(200);
		ImGui::SliderInt("Alpha", &alpha, 1, 30);
		ImGui::SliderInt("Beta", &beta, 1, 30);
		ImGui::Text("Countdown: %d ", 100-i);
		ImGui::PopItemWidth();
		ImGui::End();
	
		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	termImgui();
	return 0;
}
