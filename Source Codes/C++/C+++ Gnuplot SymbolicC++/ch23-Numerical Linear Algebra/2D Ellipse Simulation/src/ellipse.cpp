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
	std::string title = "Conic Simulation";
	initImgui(w, h, title);

	// simulation state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(89.0f / 255.0, 88.0f / 255.0, 87.0f / 255.0, 1.00f);
	ImVec4 ray_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 ray_color2 = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

	// Main loop
	int ii = 0;
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

		float strokex = 600.0; // the beginning of the drawing for ellipse simulation
		float strokey = 410.0; // the beginning of the drawing for ellipse simulation

		static int alpha = 51;
		static int beta = 60;		

		ImVec2 wave_N = {std::cos((float)ii)*alpha + strokex, std::sin((float)ii)*beta + strokey};
		
		wave_tail.push_front(wave_N);

		// This for loop is the one running the movement of the dot in the circle and the sawtooth wave that is being drawn
		for (auto &it : wave_tail)
		{
			draw_list->AddCircleFilled(it, 1.0, IM_COL32(45, 0, 255, 255));
		}
		ii++;
		// the if statement to restart the drawing after variable ii reach 801
		if (ii > 800)
		{
			wave_tail.erase(wave_tail.begin(), wave_tail.end());
			ii = 0;
		}
		ImGui::PushItemWidth(200);
		ImGui::SliderInt("Alpha", &alpha, 1, 300);
		ImGui::SliderInt("Beta", &beta, 1, 300);
		ImGui::Text("Countdown: %d ", 800-ii);
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
