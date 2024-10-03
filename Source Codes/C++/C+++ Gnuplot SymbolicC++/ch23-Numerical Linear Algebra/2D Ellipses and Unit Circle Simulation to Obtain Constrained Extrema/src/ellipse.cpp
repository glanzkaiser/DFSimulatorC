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
// #include "symbolicc++.h"
#include <armadillo>

using namespace std;
using namespace arma;

double halving(double x)
{
	double y = 2;
	return x/y;
}

double division(double x, double y)
{
	return x/y;
}
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
	std::list<ImVec2> ellipse_tail;
	std::list<ImVec2> ellipse_tail2;
	std::list<ImVec2> ellipse_tail3;
	std::list<ImVec2> point1;
	std::list<ImVec2> point2;
	std::list<ImVec2> point3;
	std::list<ImVec2> point4;
	std::list<int> test;

	mat A(2,2, fill::zeros);
	cx_mat eigvec;
	cx_vec eigval;

	mat I(2,2,fill::eye);
	// We create symmetric matrix A from quadratic form Q
	int N = 2;
	float matrixA[N][N] = {};
	
	matrixA[0][0] = 5;
	matrixA[0][1] = halving(4);
	matrixA[1][0] = matrixA[0][1];
	matrixA[1][1] = 5;
	
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			A[i+j*N] = matrixA[i][j];
		}			
	}

	cout <<"Matrix A:" << "\n" << A <<endl;
	
	eig_gen(eigval, eigvec, A); // Eigen decomposition of dense general square matrix
	arma::vec v1 = real(eigvec.col(0));
	arma::vec v2 = real(eigvec.col(1));

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
		
		static int deg = acos(v1[0]) * RADTODEG;
		// for creating the ellipses, 
		// we multiply by -deg because rotation will be clockwise since in the quadratic form ax^2 + bxy + cy2^2, we have b>0
		float theta = DEGTORAD*-deg; 

		float p1x = cos(theta); // first column first row of transition matrix P
		float p1y = sin(theta); // first column second row of transition matrix P
		float p2x = -p1x;
		float p2y = -p1y;
		float p3x = -sin(theta); // second column first row of transition matrix P
		float p3y = cos(theta); // second column second row of transition matrix P
		float p4x = -p3x;
		float p4y = -p3y;

		// The rotated ellipse in parametric equation will be:
		// P * [x y]
		// P is the transition matrix, the standard rotation matrix
		// x = alpha * cos t
		// y = beta * sin t
		ImVec2 wave_N = {std::cos((float)ii)*r*(sqrt(k1/eigen1)) * std::cos((float)theta) - std::sin((float)ii)*r*(sqrt(k1/eigen2)) * std::sin((float)theta) + strokex, std::sin((float)theta)  * std::cos((float)ii)*r*(sqrt(k1/eigen1)) + std::cos((float)theta) * std::sin((float)ii)*r*(sqrt(k1/eigen2)) + strokey}; // the first ellipse
		ImVec2 wave_N2 = {std::cos((float)ii)*r*(sqrt(k2/eigen1)) * std::cos((float)theta) - std::sin((float)ii)*r*(sqrt(k2/eigen2)) * std::sin((float)theta) + strokex, std::sin((float)theta)  * std::cos((float)ii)*r*(sqrt(k2/eigen1)) + std::cos((float)theta) * std::sin((float)ii)*r*(sqrt(k2/eigen2)) + strokey}; // the second ellipse
		ImVec2 wave_N3 = {std::cos((float)ii)*r + strokex, std::sin((float)ii)*r + strokey}; // The unit circle
		ImVec2 point_1 = {std::cos((float)ii)*3+strokex + r*p1x, std::sin((float)ii)*3 + strokey + r*p1y}; // The intersection point 1
		ImVec2 point_2 = {std::cos((float)ii)*3+strokex + r*p2x, std::sin((float)ii)*3 + strokey + r*p2y}; // The intersection point 2
		ImVec2 point_3 = {std::cos((float)ii)*3+strokex + r*p3x, std::sin((float)ii)*3 + strokey + r*p3y}; // The intersection point 3
		ImVec2 point_4 = {std::cos((float)ii)*3+strokex + r*p4x, std::sin((float)ii)*3 + strokey + r*p4y}; // The intersection point 4
		
		ellipse_tail.push_front(wave_N);
		ellipse_tail2.push_front(wave_N2);
		ellipse_tail3.push_front(wave_N3);
		point1.push_front(point_1);
		point2.push_front(point_2);
		point3.push_front(point_3);
		point4.push_front(point_4);

		// This for loop is the one running the dots that will make the shape of an ellipse
		for (auto &it : ellipse_tail)
		{
			draw_list->AddCircleFilled(it, 1.0, IM_COL32(45, 140, 25, 255)); // color green
		}
		for (auto &it2 : ellipse_tail2)
		{
			draw_list->AddCircleFilled(it2, 1.0, IM_COL32(45, 90, 255, 255)); // color blue
		}
		for (auto &it3 : ellipse_tail3)
		{
			draw_list->AddCircleFilled(it3, 1.0, IM_COL32(55, 10, 25, 155)); // color black
		}
		for (auto &it4 : point1)
		{
			draw_list->AddCircleFilled(it4, 1.0, IM_COL32(55, 230, 25, 255)); // color metallic green
		}
		for (auto &it5 : point2)
		{
			draw_list->AddCircleFilled(it5, 1.0, IM_COL32(55, 230, 25, 255)); // color metallic green
		}
		for (auto &it6 : point3)
		{
			draw_list->AddCircleFilled(it6, 1.0, IM_COL32(55, 230, 25, 255)); // color metallic green
		}
		for (auto &it7 : point4)
		{
			draw_list->AddCircleFilled(it7, 1.0, IM_COL32(55, 230, 25, 255)); // color metallic green
		}
		ii++;
		// the if statement to restart the drawing after variable ii reach 801
		if (ii > 800)
		{
			ellipse_tail.erase(ellipse_tail.begin(), ellipse_tail.end());
			ellipse_tail2.erase(ellipse_tail2.begin(), ellipse_tail2.end());
			ellipse_tail3.erase(ellipse_tail3.begin(), ellipse_tail3.end());
			point1.erase(point1.begin(), point1.end());
			point2.erase(point2.begin(), point2.end());
			point3.erase(point3.begin(), point3.end());
			point4.erase(point4.begin(), point4.end());
			ii = 300;
		}
		// SymbolicC++ codes start here
		/* 
		Symbolic x("x"), y("y");
		auto ellipse1 = 5*(x^2) + 5*(y^2) + 4*x*y == 7;
		auto ellipse2 = 5*(x^2) + 5*(y^2) + 4*x*y == 3;
		auto circle = (x^2) + (y^2) == 1;

		Equation e1 = 5*(x^2) + 5*(y^2) + 4*x*y == 7;
		Equation e2 = (x^2) + (y^2) == 1;

		Equations eqs = {e1, e2};
		list<Symbolic> symbs = {x, y};
		list<Equations> sols = solve(eqs, symbs);

		*/
		// SymbolicC++ codes end here
		cout << "point 1 : (x,y) = (" << point_1[0] ;
		cout << ",  " << point_1[1] << ")" << endl;
		cout << "point 2 : (x,y) = (" << point_2[0] ;
		cout << ",  " << point_2[1] << ")" << endl;
		cout << "point 3 : (x,y) = (" << point_3[0] ;
		cout << ",  " << point_3[1] << ")" << endl;
		cout << "point 4 : (x,y) = (" << point_4[0] ;
		cout << ",  " << point_4[1] << ")" << endl;

		ImGui::PushItemWidth(200);
		ImGui::SliderInt("r", &r, 51, 146);
		ImGui::SliderInt("k1", &k1, -51, 108);
		ImGui::SliderFloat("k2", &k2, 0.0f, 5.0f);            // Edit 1 float using a slider from 0.0f to 5.0f
		//sImGui::SliderFloat("k2", &k2, -51, 108,"%.1f", 0); //still not working for SliderFloat
		ImGui::SliderInt("Eigen 1", &eigen1, -51, 108);
		ImGui::SliderInt("Eigen 2", &eigen2, -51, 108);
		
		ImGui::SliderInt("Rotation degree", &deg, 1, 180);
		ImGui::Text("Countdown: %d ", 800-ii);
		ImGui::Text("For circle with radius of 1 : ");
		ImGui::Text("Point of intersection 1: ( %.5f , % .5f )", cos(theta), sin(theta));
		ImGui::Text("Point of intersection 2: ( %.5f , % .5f )", -cos(theta), -sin(theta));
		ImGui::Text("Point of intersection 3: ( %.5f , % .5f )", -sin(theta), cos(theta));
		ImGui::Text("Point of intersection 4: ( %.5f , % .5f )", sin(theta), -cos(theta));
		ImGui::Text("cos(theta): % .5f ", cos(theta));
		ImGui::Text("sin(theta): % .5f ", sin(theta));
		
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
