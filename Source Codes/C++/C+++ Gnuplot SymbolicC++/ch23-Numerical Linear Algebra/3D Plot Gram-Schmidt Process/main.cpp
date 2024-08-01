// Merci beaucoup Sentinel, Freya et Albert Silverberg
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams -larmadillo

#include <vector>
#include <cmath>
#include <utility>
#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <armadillo>

#include "gnuplot-iostream.h"

using namespace std;
using namespace arma;

double division(double x, double y)
{
	return x/y;
}

int main() {
	int N = 3;
	arma::vec u1(N,fill::zeros); 
	u1[0] = 1;
	u1[1] = 1;
	u1[2] = 1;
	arma::vec u2(N,fill::zeros); 
	u2[0] = 0;
	u2[1] = division(1,1);
	u2[2] = 1;
	arma::vec u3(N,fill::zeros); 
	u3[0] = 0;
	u3[1] = 0;
	u3[2] = division(1,1);
	
	cout <<"Vector u1 :" << "\n" << u1 <<endl;
	cout <<"|| u1 || :"  << norm(u1) <<endl;
	cout <<"\nVector u2 :" << "\n" << u2 <<endl;
	cout <<"|| u2 || :"  << norm(u2) <<endl;
	cout <<"\nVector u3 :" << "\n" << u3 <<endl;
	cout <<"|| u3 || :"  << norm(u3) <<endl;
	
	arma::vec v1(N,fill::zeros); 
	arma::vec v2(N,fill::zeros); 
	arma::vec v3(N,fill::zeros); 
	arma::vec q1(N,fill::zeros); 
	arma::vec q2(N,fill::zeros); 
	arma::vec q3(N,fill::zeros); 
	arma::vec u2projW1(N,fill::zeros); 
	arma::vec u3projW2(N,fill::zeros); 
		
	// The Gram-Schmidt Process
	v1 = u1;
	
	u2projW1 = (dot(u2,v1)/(pow(norm(v1),2)))*v1;	
	v2 = u2 - u2projW1;
	
	u3projW2 = (dot(u3,v1)/(pow(norm(v1),2)))*v1 + (dot(u3,v2)/(pow(norm(v2),2)))*v2;	
	v3 = u3 - u3projW2;
	
	cout <<"\nv1 :\n" << v1 <<endl;
	cout <<"v2 :\n" << v2 <<endl;
	cout <<"v3 :\n" << v3 <<endl;
	cout <<"\n|| v1 || :"  << norm(v1) <<endl;
	cout <<"|| v2 || :"  << norm(v2) <<endl;
	cout <<"|| v3 || :"  << norm(v3) <<endl;
	cout <<"\n<v1,v2> :" << dot(v1,v2) <<endl;
	cout <<"<v2,v3> :" << dot(v2,v3) <<endl;
	cout <<"<v1,v3> :" << dot(v1,v3) <<endl;
	
	q1 = v1/norm(v1);
	q2 = v2/norm(v2);
	q3 = v3/norm(v3);
	
	cout <<"\nq1 :\n" << q1 <<endl;
	cout <<"q2 :\n" << q2 <<endl;
	cout <<"q3 :\n" << q3 <<endl;
	cout <<"\n|| q1 || :"  << norm(q1) <<endl;
	cout <<"|| q2 || :"  << norm(q2) <<endl;
	cout <<"|| q3 || :"  << norm(q3) <<endl;

	Gnuplot gp;

	// We use a separate container for each column, like so:
	std::vector<double> pts_A_x;
	std::vector<double> pts_A_y;
	std::vector<double> pts_A_z;
	std::vector<double> pts_A_dx;
	std::vector<double> pts_A_dy;
	std::vector<double> pts_A_dz;
	std::vector<double> pts_B_x;
	std::vector<double> pts_B_y;
	std::vector<double> pts_B_z;
	std::vector<double> pts_B_dx;
	std::vector<double> pts_B_dy;
	std::vector<double> pts_B_dz;
	std::vector<double> pts_C_x;
	std::vector<double> pts_C_y;
	std::vector<double> pts_C_z;
	std::vector<double> pts_C_dx;
	std::vector<double> pts_C_dy;
	std::vector<double> pts_C_dz;
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_z;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;	
	std::vector<double> pts_D_dz;	
	std::vector<double> pts_E_x;
	std::vector<double> pts_E_y;
	std::vector<double> pts_E_z;
	std::vector<double> pts_E_dx;
	std::vector<double> pts_E_dy;	
	std::vector<double> pts_E_dz;	
	std::vector<double> pts_F_x;
	std::vector<double> pts_F_y;
	std::vector<double> pts_F_z;
	std::vector<double> pts_F_dx;
	std::vector<double> pts_F_dy;	
	std::vector<double> pts_F_dz;	
	std::vector<double> pts_G_x;
	std::vector<double> pts_G_y;
	std::vector<double> pts_G_z;
	std::vector<double> pts_G_dx;
	std::vector<double> pts_G_dy;	
	std::vector<double> pts_G_dz;	
	std::vector<double> pts_H_x;
	std::vector<double> pts_H_y;
	std::vector<double> pts_H_z;
	std::vector<double> pts_H_dx;
	std::vector<double> pts_H_dy;	
	std::vector<double> pts_H_dz;	
	std::vector<double> pts_I_x;
	std::vector<double> pts_I_y;
	std::vector<double> pts_I_z;
	std::vector<double> pts_I_dx;
	std::vector<double> pts_I_dy;	
	std::vector<double> pts_I_dz;	

	float o = 0;

	// Create a vector u1 basis in R^3
	pts_A_x .push_back(o);
	pts_A_y .push_back(o);
	pts_A_z .push_back(o);
	pts_A_dx.push_back(u1[0]);
	pts_A_dy.push_back(u1[1]);
	pts_A_dz.push_back(u1[2]);	
	// Create a vector u2 basis in R^3
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_z .push_back(o);
	pts_B_dx.push_back(u2[0]);
	pts_B_dy.push_back(u2[1]);
	pts_B_dz.push_back(u2[2]);
	// Create a vector u3 basis in R^3
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_z .push_back(o);
	pts_C_dx.push_back(u3[0]);
	pts_C_dy.push_back(u3[1]);
	pts_C_dz.push_back(u3[2]);
	// Create the first orthogonal basis for R^3: v1
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(v1[0]);
	pts_D_dy.push_back(v1[1]);
	pts_D_dz.push_back(v1[2]);
	// Create the second orthogonal basis for R^3: v2
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(v2[0]);
	pts_E_dy.push_back(v2[1]);
	pts_E_dz.push_back(v2[2]);
	// Create the third orthogonal basis for R^3: v3
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(v3[0]);
	pts_F_dy.push_back(v3[1]);
	pts_F_dz.push_back(v3[2]);
	// Create the first orthonormal basis for R^3: q1
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_z .push_back(o);
	pts_G_dx.push_back(q1[0]);
	pts_G_dy.push_back(q1[1]);
	pts_G_dz.push_back(q1[2]);
	// Create the second orthonormal basis for R^3: q2
	pts_H_x .push_back(o);
	pts_H_y .push_back(o);
	pts_H_z .push_back(o);
	pts_H_dx.push_back(q2[0]);
	pts_H_dy.push_back(q2[1]);
	pts_H_dz.push_back(q2[2]);
	// Create the third orthonormal basis for R^3: q3
	pts_I_x .push_back(o);
	pts_I_y .push_back(o);
	pts_I_z .push_back(o);
	pts_I_dx.push_back(q3[0]);
	pts_I_dy.push_back(q3[1]);
	pts_I_dz.push_back(q3[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-1:2]\nset yrange [-1:2]\nset zrange [-1:2]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "f(x,y) = (0.8*x-y)/(0.6)\n";
	
	// To plot u1,u2,u3	(comment / uncomment)	
	///*
	gp << "splot '++' using 1:2:(0) with lines lw 2 lc rgb 'gray' title 'W = (x,y,0)', \
		'-' with vectors lw 3 lc rgb 'medium-blue' title 'u_{1}', '-' with vectors lw 3 lc rgb 'skyblue' title 'u_{2}', \
		'-' with vectors lw 3 lc rgb 'navy' title 'u_{3}'\n";
	gp.send1d(boost::make_tuple(pts_A_x, pts_A_y,  pts_A_z, pts_A_dx, pts_A_dy, pts_A_dz));
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	//*/

	// To plot v1,v2,v3	(comment / uncomment)
	/*
	gp << "splot '++' using 1:2:(0) with lines lw 2 lc rgb 'gray' title 'W = (x,y,0)', \
		'-' with vectors lw 3 lc rgb 'forest-green' title 'v_{1}',\
		'-' with vectors lw 3 lc rgb 'dark-green' title 'v_{2}', '-' with vectors lw 3 lc rgb 'spring-green' title 'v_{3}'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));
	*/

	// To plot q1,q2,q3	(comment / uncomment)
	/*	
	gp << "splot '++' using 1:2:(0) with lines lw 2 lc rgb 'gray' title 'W = (x,y,0)', \
		'-' with vectors lw 3 lc rgb 'forest-green' title 'q_{1}',\
		'-' with vectors lw 3 lc rgb 'dark-green' title 'q_{2}', '-' with vectors lw 3 lc rgb 'spring-green' title 'q_{3}'\n";
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_z, pts_G_dx, pts_G_dy, pts_G_dz));
	gp.send1d(boost::make_tuple(pts_H_x, pts_H_y, pts_H_z, pts_H_dx, pts_H_dy, pts_H_dz));
	gp.send1d(boost::make_tuple(pts_I_x, pts_I_y, pts_I_z, pts_I_dx, pts_I_dy, pts_I_dz));
	*/
	return 0;
}