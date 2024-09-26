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
#include <iostream>
#include "symbolicc++.h"

using namespace std;

#define pi  3.1415926535897
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f	

int main(int argc, char const *argv[])
{

	int w = 1280;
	int h = 720;
	std::string title = "Level Curves Simulation";
	initImgui(w, h, title);

	// simulation state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(89.0f / 255.0, 88.0f / 255.0, 87.0f / 255.0, 1.00f);
	ImVec4 ray_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 ray_color2 = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

	// Main loop
	int ii = 300;
	bool flag = true;
	std::list<ImVec2> wave_tail;
	std::list<ImVec2> wave_tail2;
	std::list<ImVec2> wave_tail3;
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

		float strokex = 600.0; // the ellipse' and circle center x-coordinate 
		float strokey = 410.0; // the ellipse' and circle center y-coordinate 

		static int k1 = 7;
		float k2 = 3;
		static int eigen1 = 7;
		static int eigen2 = 3;
		static int r = 100;
		//static int alpha1 = r*(sqrt(k1/eigen1));
		//static int beta1 = r*(sqrt(k1/eigen2));		
		//static int alpha2 = r*(sqrt(k2/eigen1));
		//static int beta2 = r*(sqrt(k2/eigen2));		
		static int deg = 45;
		float theta = DEGTORAD*-deg;
		// The rotated ellipse in parametric equation will be:
		// P * [x y]
		// P is the transition matrix, the standard rotation matrix
		// x = alpha * cos t
		// y = beta * sin t
		ImVec2 wave_N = {std::cos((float)ii)*r*(sqrt(k1/eigen1)) * std::cos((float)theta) - std::sin((float)ii)*r*(sqrt(k1/eigen2)) * std::sin((float)theta) + strokex, std::sin((float)theta)  * std::cos((float)ii)*r*(sqrt(k1/eigen1)) + std::cos((float)theta) * std::sin((float)ii)*r*(sqrt(k1/eigen2)) + strokey}; // the first ellipse
		ImVec2 wave_N2 = {std::cos((float)ii)*r*(sqrt(k2/eigen1)) * std::cos((float)theta) - std::sin((float)ii)*r*(sqrt(k2/eigen2)) * std::sin((float)theta) + strokex, std::sin((float)theta)  * std::cos((float)ii)*r*(sqrt(k2/eigen1)) + std::cos((float)theta) * std::sin((float)ii)*r*(sqrt(k2/eigen2)) + strokey}; // the second ellipse
		ImVec2 wave_N3 = {std::cos((float)ii)*r + strokex, std::sin((float)ii)*r + strokey}; // The unit circle
		
		wave_tail.push_front(wave_N);
		wave_tail2.push_front(wave_N2);
		wave_tail3.push_front(wave_N3);

		// This for loop is the one running the dots that will make the shape of an ellipse
		for (auto &it : wave_tail)
		{
			draw_list->AddCircleFilled(it, 1.0, IM_COL32(45, 140, 25, 255)); // color green
		}
		for (auto &it2 : wave_tail2)
		{
			draw_list->AddCircleFilled(it2, 1.0, IM_COL32(45, 90, 255, 255)); // color blue
		}
		for (auto &it3 : wave_tail3)
		{
			draw_list->AddCircleFilled(it3, 1.0, IM_COL32(55, 10, 25, 155)); // color black
		}
		ii++;
		// the if statement to restart the drawing after variable ii reach 801
		if (ii > 800)
		{
			wave_tail.erase(wave_tail.begin(), wave_tail.end());
			wave_tail2.erase(wave_tail2.begin(), wave_tail2.end());
			wave_tail3.erase(wave_tail3.begin(), wave_tail3.end());
			ii = 300;
		}
		// SymbolicC++ codes start here
		Symbolic x("x"), y("y");
		auto ellipse1 = 5*(x^2) + 5*(y^2) + 4*x*y == 7;
		auto ellipse2 = 5*(x^2) + 5*(y^2) + 4*x*y == 3;
		auto circle = (x^2) + (y^2) == 1;

		Equation e1 = 5*(x^2) + 5*(y^2) + 4*x*y == 7;
		Equation e2 = (x^2) + (y^2) == 1;

		Equations eqs = {e1, e2};
		list<Symbolic> symbs = {x, y};
		list<Equations> sols = solve(eqs, symbs);

		Symbolic x_sol, y_sol;
		int i = 1;
		for( auto iter1 = sols.begin(); iter1 != sols.end(); iter1++)
		{
			x_sol = x.subst((*(*iter1).begin()));
			y_sol = y.subst((*(--(*iter1).end())));
			cout << "p" << i << " = {" << x_sol << ", " << y_sol << "};" << endl;
			i++;
		}
		// SymbolicC++ codes end here

		ImGui::PushItemWidth(200);
		ImGui::SliderInt("r", &r, 51, 146);
		ImGui::SliderInt("k1", &k1, -51, 108);
		ImGui::SliderFloat("k2", &k2, -51, 108,"%.1f", 0); //still not working for SliderFloat
		ImGui::SliderInt("Eigen 1", &eigen1, -51, 108);
		ImGui::SliderInt("Eigen 2", &eigen2, -51, 108);
		
		ImGui::SliderInt("Rotation degree", &deg, 1, 180);
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
