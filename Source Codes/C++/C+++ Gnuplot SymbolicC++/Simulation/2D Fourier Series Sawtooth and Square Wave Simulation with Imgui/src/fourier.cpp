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
#define pi  3.1415926535897

using namespace std;
//---------------------------------------------------------------
std::vector<Point> points = {
	{{200, 400}, 10}};

//----------- system dynamic parameters --------------------

// M_PI = 12
float dt = M_PI / 720.0; // the larger dt value, the slower the movement of the simulation 
float P = 0.25; // the Period
float scale = 51.0; // the bigger the value, the bigger all the circles will become

//---------------------------------------------------------------

int main(int argc, char const *argv[])
{

	int w = 1280;
	int h = 720;
	std::string title = "Fourier Series Sawtooth and Square Wave";
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

		static int num_sig = 3;

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

		float stroke = 150.0; //the center of the circle is at stroke = 0
		std::vector<int> N = {1, 3, 5};
		float r1 = 4.0 / (N[0] * M_PI) * scale;
		float r2 = 4.0 / (N[1] * M_PI) * scale;
		float r3 = 4.0 / (N[2] * M_PI) * scale;
		float size_line = 3;

		std::vector<ImVec2> circles;
		std::vector<ImVec2> dots_circles;
		std::vector<float> vec_r;

		float x = (float)points[0].position.x;
		float y = (float)points[0].position.y;

		std::vector<float> vec_w;
	
		// this for loop is to create the dots and radius lines that is circling the all circles
		// For square wave
		///*
		for (int i = 0; i < num_sig; i++)
		{

			float prev_x = x;
			float prev_y = y;
			circles.push_back({prev_x, prev_y});

			int n = 2*i + 1;

			float r = 4.0 / (n * M_PI) * scale;
			vec_r.push_back(r);

			// circle dot
			// f(x) = sum_{n}^{infty} ( 4 / ( pi * (2n-1) ) ) * sin ((2n-1)*pi*x/P)
			x += (float)std::cos(ii * dt * n / P) * r;
			y += (float)std::sin(ii * dt * n / P) * r;
			vec_w.push_back((float)std::sin(ii * dt * n / P) * r );
			dots_circles.push_back({x, y});
		}
		//*/

		// For sawtooth wave
		/*
		for (int i = 0; i < num_sig; i++)
		{

			float prev_x = x;
			float prev_y = y;
			circles.push_back({prev_x, prev_y});

			int n = i + 1;

			float r = 4.0 / (n * M_PI) * scale;
			vec_r.push_back(r);

			// circle dot
			// f(x) = sum_{n}^{infty} 2 * (-1)^{n+1} * sin (n*pi*x/P) * r
			x += (float)std::cos(ii * dt * n / P) * r;
			y += (float)std::sin(ii * dt * n / P) * r;
			vec_w.push_back((float)pi - 2 * (pow(-1,n+1)) *std::sin(ii * dt * n / P) * r );
			//vec_w.push_back((float)2*std::sin(ii * dt * n / P) * r );
			dots_circles.push_back({x, y});	
		}
		*/

		// This for loop is to create all the circles
		for (int jj = 0; jj < circles.size(); jj++)
		{

			draw_list->AddLine(circles[jj], dots_circles[jj], ImColor(ray_color), 2.0);
			draw_list->AddCircle(circles[jj], vec_r[jj], ImColor(ray_color));
		}
		// From std::vector<Point> points :
		// (float)points[0].position.x = 200
		// (float)points[0].position.y = 400
		// stroke = 150
		// the center of the first circle of the Fourier series is at (200,400) the y value here is getting larger when you 
		// go with down direction on the screen and getting smaller when you go with up direction on the screen
		// (float)points[0].position.y + std::accumulate(vec_w.begin(), vec_w.end(),0) this tells the y position of the circle moving
		// from the first circle of the Fourier series
		ImVec2 wave_N = {(float)points[0].position.x + ii + stroke, (float)points[0].position.y + std::accumulate(vec_w.begin(), vec_w.end(),0)};
		
		draw_list->AddLine(dots_circles[dots_circles.size() - 1], wave_N, ImColor(ray_color), 2.0);

		wave_tail.push_front(wave_N);

		// This for loop is the one running the movement of the dot in the circle and the sawtooth wave that is being drawn
		for (auto &it : wave_tail)
		{
			draw_list->AddCircleFilled(it, 1.0, IM_COL32(255, 0, 255, 255));
		}
		ii++;
		// the if statement to restart the drawing after variable ii reach 801
		if (ii > 800)
		{
			wave_tail.erase(wave_tail.begin(), wave_tail.end());
			ii = 0;
		}
		ImGui::PushItemWidth(200);
		ImGui::SliderInt("Number of periods", &num_sig, 1, 20);
		ImGui::Text("The Fourier series wave:");
		ImGui::Text("x: %d ", ii);
		ImGui::Text("y(x) : %d ", 400 + std::accumulate(vec_w.begin(), vec_w.end(),0) );
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
