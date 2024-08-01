// g++ -o result main.cpp
// Merci beaucoup Freya..
// C++ program to find the least square solution for inconsistent system

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>
#include <boost/tuple/tuple.hpp>
#include <cmath>
#include <utility>

#include "gnuplot-iostream.h"

using namespace std;
using namespace arma;

const int N = 5;
const int R = 3;
const int C = 2;

// Driver code
int main(int argc, char** argv)
{
	arma::mat A(R,C,fill::zeros); //declare matrix A with size of R X C all have 0 entries with Armadillo.
	A.load("matrixA.txt"); // load matrixA.txt with Armadillo

	arma::mat b(R,1,fill::zeros);
	b.load("vectorb.txt");

	cout <<"Matrix A (Coefficient Matrix):" << "\n" << A <<endl;
	cout <<"Vector b:" << "\n" << b <<endl;

	arma::mat A_transpose(C,R,fill::zeros); 
	A_transpose = A.t();

	arma::mat AtA(C,C,fill::zeros); 
	arma::mat Atb(C,1,fill::zeros); 
	AtA = A_transpose*A;
	Atb = A_transpose*b;

	cout <<"A^T:" << "\n" << A_transpose <<endl;
	cout <<"A^T * A:" << "\n" << AtA <<endl;
	cout <<"(A^T) * b:" << "\n" << Atb <<endl;

	// Find the solution for x from A^T * A * x = A^T * b
	mat X;
	mat bprojW;
	X = solve(AtA,Atb,solve_opts::force_approx); 
	bprojW = A*X;
	cout <<"The least squares solution " << endl;
	cout <<"x :" << "\n" << X <<endl;
	cout <<"Ax :" << "\n" << bprojW <<endl;

	mat error_vector;
	error_vector = b-bprojW;
	cout <<"The error vector " << endl;
	cout <<"b - Ax :" << "\n" << error_vector <<endl;
	
	cout <<"The error" << endl;
	cout <<"|| b - Ax || :" << norm(error_vector) <<endl;
	
	cout <<"\n< Ax, b - Ax > :" << dot(bprojW,error_vector) <<endl;
	
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
	
	float o = 0;

	// Create a vector b in R^3
	pts_A_x .push_back(o);
	pts_A_y .push_back(o);
	pts_A_z .push_back(o);
	pts_A_dx.push_back(b[0]);
	pts_A_dy.push_back(b[1]);
	pts_A_dz.push_back(b[2]);	
	// Create a vector projection of b on W in R^3
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_z .push_back(o);
	pts_B_dx.push_back(bprojW[0]);
	pts_B_dy.push_back(bprojW[1]);
	pts_B_dz.push_back(bprojW[2]);
	// Create a vector component of b orthogonal to W in R^3
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_z .push_back(o);
	pts_C_dx.push_back(error_vector[0]);
	pts_C_dy.push_back(error_vector[1]);
	pts_C_dz.push_back(error_vector[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-5:5]\nset yrange [-5:5]\nset zrange [-5:5]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	// the splot '++' to create the plane W spanned by the vector columns of A / column space of A 
	gp << "splot '++' using ($1-$2):($1*3 + $2*2):($2*4 + $1*-2) with lines lw 2 lc rgb 'gray' title 'W = c1(1,3,-2) + c2(-1,2,4)', \
		'-' with vectors lw 3 lc rgb 'cyan' title 'b', '-' with vectors lw 3 lc rgb 'skyblue' title 'proj_{W} b ', \
		'-' with vectors lw 3 lc rgb 'navy' title 'b - proj_{W} b '\n";
	gp.send1d(boost::make_tuple(pts_A_x, pts_A_y,  pts_A_z, pts_A_dx, pts_A_dy, pts_A_dz));
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	
	return 0;
}