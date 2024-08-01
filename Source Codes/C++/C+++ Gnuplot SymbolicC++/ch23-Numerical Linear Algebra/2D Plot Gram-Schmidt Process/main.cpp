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
	int N = 2;
	arma::vec u1(N,fill::zeros); 
	u1[0] = 1;
	u1[1] = -3;
	arma::vec u2(N,fill::zeros); 
	u2[0] = 2;
	u2[1] = division(2,1);
	
	cout <<"Vector u1 :" << "\n" << u1 <<endl;
	cout <<"|| u1 || :"  << norm(u1) <<endl;
	cout <<"\nVector u2 :" << "\n" << u2 <<endl;
	cout <<"|| u2 || :"  << norm(u2) <<endl;
	
	arma::vec v1(N,fill::zeros); 
	arma::vec v2(N,fill::zeros); 
	arma::vec q1(N,fill::zeros); 
	arma::vec q2(N,fill::zeros); 
	arma::vec u2projW1(N,fill::zeros); 
		
	// The Gram-Schmidt Process
	v1 = u1;
	
	u2projW1 = (dot(u2,v1)/(pow(norm(v1),2)))*v1;	
	v2 = u2 - u2projW1;
	
	cout <<"\nv1 :\n" << v1 <<endl;
	cout <<"v2 :\n" << v2 <<endl;
	cout <<"\n|| v1 || :"  << norm(v1) <<endl;
	cout <<"|| v2 || :"  << norm(v2) <<endl;
	cout <<"\n<v1,v2> :" << dot(v1,v2) <<endl;
	
	q1 = v1/norm(v1);
	q2 = v2/norm(v2);
	
	cout <<"\nq1 :\n" << q1 <<endl;
	cout <<"q2 :\n" << q2 <<endl;
	cout <<"\n|| q1 || :"  << norm(q1) <<endl;
	cout <<"|| q2 || :"  << norm(q2) <<endl;
	
	Gnuplot gp;

	// We use a separate container for each column, like so:
	std::vector<double> pts_A_x;
	std::vector<double> pts_A_y;
	std::vector<double> pts_A_dx;
	std::vector<double> pts_A_dy;
	std::vector<double> pts_B_x;
	std::vector<double> pts_B_y;
	std::vector<double> pts_B_dx;
	std::vector<double> pts_B_dy;
	std::vector<double> pts_C_x;
	std::vector<double> pts_C_y;
	std::vector<double> pts_C_dx;
	std::vector<double> pts_C_dy;
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;	
	std::vector<double> pts_E_x;
	std::vector<double> pts_E_y;
	std::vector<double> pts_E_dx;
	std::vector<double> pts_E_dy;	
	std::vector<double> pts_F_x;
	std::vector<double> pts_F_y;
	std::vector<double> pts_F_dx;
	std::vector<double> pts_F_dy;	

	float o = 0;

	// Create a vector u1 basis in R^2
	pts_A_x .push_back(o);
	pts_A_y .push_back(o);
	pts_A_dx.push_back(u1[0]);
	pts_A_dy.push_back(u1[1]);
	// Create a vector u2 basis in R^2
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_dx.push_back(u2[0]);
	pts_B_dy.push_back(u2[1]);
	// Create a vector v1 new orthogonal basis in R^2
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_dx.push_back(v1[0]);
	pts_C_dy.push_back(v1[1]);
	// Create a vector v2 new orthogonal basis in R^2
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(v2[0]);
	pts_D_dy.push_back(v2[1]);
	// Create a vector q1 orthonormal basis in R^2
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(q1[0]);
	pts_E_dy.push_back(q1[1]);
	// Create a vector q2 orthonormal basis in R^2
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_dx.push_back(q2[0]);
	pts_F_dy.push_back(q2[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-5:5]\nset yrange [-5:5]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	gp << "set multiplot layout 2,2 title 'Gram-Schmidt Process in R^{2}'\n"; // multiplot
	
	// To plot u1,u2	
	gp << " plot '-' with vectors lw 3 lc rgb 'medium-blue' title 'u_{1}',\
		 '-' with vectors lw 3 lc rgb 'skyblue' title 'u_{2}'\n";
	gp.send1d(boost::make_tuple(pts_A_x, pts_A_y, pts_A_dx, pts_A_dy));
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));

	// To plot v1,v2
	gp << "plot '-' with vectors lw 3 lc rgb 'forest-green' title 'v_{1}',\
		'-' with vectors lw 3 lc rgb 'spring-green' title 'v_{2}'\n";
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));

	// To plot q1,q2
	gp << "plot '-' with vectors lw 3 lc rgb 'salmon' title 'q_{1}', \
		'-' with vectors lw 3 lc rgb 'magenta' title 'q_{2}'\n";
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
	
	return 0;
}