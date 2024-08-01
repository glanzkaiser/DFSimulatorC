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
	arma::vec u(N,fill::zeros); 
	u[0] = 1;
	u[1] = 1;
	u[2] = 1;
	arma::vec v1(N,fill::zeros); 
	v1[0] = 0;
	v1[1] = division(1,1);
	v1[2] = 0;
	arma::vec v2(N,fill::zeros); 
	v2[0] = division(-4,5);
	v2[1] = 0;
	v2[2] = division(3,5);
	
	cout <<"Vector v1 :" << "\n" << v1 <<endl;
	cout <<"|| v1 || :"  << norm(v1) <<endl;
	cout <<"\nVector v2 :" << "\n" << v2 <<endl;
	cout <<"|| v2 || :"  << norm(v2) <<endl;
	cout <<"\nVector u :" << "\n" << u <<endl;
	cout <<"|| u || :"  << norm(u) <<endl;
	
	double uv1 = dot(u,v1);
	double uv2 = dot(u,v2);
	
	cout <<"\n<u,v1> :" << uv1 <<endl;
	cout <<"<u,v2> :" << uv2 <<endl;
	
	arma::vec uprojW(N,fill::zeros); 
	arma::vec uprojWperp(N,fill::zeros); 
	uprojW = uv1*v1 + uv2*v2;
	uprojWperp = u - uprojW;

	cout <<"\nThe orthogonal projection of u on W:" <<endl;
	cout <<"proj_{W} u =\n" << uprojW <<endl;
	cout <<"\nThe orthogonal projection of u on W:" <<endl;
	cout <<"proj_{W⊥} u =\n" << uprojWperp <<endl;

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

	float o = 0;

	// Create a vector with origin at (0,0,0) and terminal point at (u1,u2,u3)
	pts_A_x .push_back(o);
	pts_A_y .push_back(o);
	pts_A_z .push_back(o);
	pts_A_dx.push_back(u[0]);
	pts_A_dy.push_back(u[1]);
	pts_A_dz.push_back(u[2]);	
	// Create a vector v1 that span W
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_z .push_back(o);
	pts_B_dx.push_back(v1[0]);
	pts_B_dy.push_back(v1[1]);
	pts_B_dz.push_back(v1[2]);
	// Create a vector v2 that span W
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_z .push_back(o);
	pts_C_dx.push_back(v2[0]);
	pts_C_dy.push_back(v2[1]);
	pts_C_dz.push_back(v2[2]);
	// Create an orthogonal projection of u on W
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(uprojW[0]);
	pts_D_dy.push_back(uprojW[1]);
	pts_D_dz.push_back(uprojW[2]);
	// Create the component of u orthogonal to W
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(uprojWperp[0]);
	pts_E_dy.push_back(uprojWperp[1]);
	pts_E_dz.push_back(uprojWperp[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-1:2]\nset yrange [-1:2]\nset zrange [-1:2]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "f(x,y) = (0.8*x-y)/(0.6)\n";
	// If you want to plot xy-plane (u,v,0) use this: splot '++' using 1:2:(0) with lines
	// A plane spanned by (0,1,0) and (-4/5,0,3/5) can be written as (-4/5 c2, c1, 3/5 c2)
	// To plot use this: splot '++' using ($1*-0.8):2:($1*0.6)
	gp << "splot '++' using ($1*-0.8):2:($1*0.6) with lines lw 2 lc rgb 'gray' title 'W = c_{1} v_{1} + c_{2} v_{2}', \
		'-' with vectors lw 3 lc rgb 'light-green' title 'u', '-' with vectors lw 3 lc rgb 'skyblue' title 'v_{1}', \
		'-' with vectors lw 3 lc rgb 'navy' title 'v_{2}', '-' with vectors lw 3 lc rgb 'forest-green' title 'proj_{W} u',\
		'-' with vectors lw 3 lc rgb 'plum' title 'proj_{W^{⊥}} u'\n";
	gp.send1d(boost::make_tuple(pts_A_x, pts_A_y,  pts_A_z, pts_A_dx, pts_A_dy, pts_A_dz));
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	
	return 0;
}