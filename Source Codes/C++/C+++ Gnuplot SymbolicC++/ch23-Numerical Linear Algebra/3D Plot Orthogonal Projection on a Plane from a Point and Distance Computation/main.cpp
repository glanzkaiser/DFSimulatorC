// g++ -o result main.cpp
// Merci beaucoup Freya.. Sentinel.. RK..

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
	// Plane W has equation of 3x - 4y + z = 0
	// We put the basis for W as column vector for matrix A
	arma::mat A(R,C,fill::zeros); //declare matrix A with size of R X C all have 0 entries with Armadillo.
	A.load("matrixA.txt"); // load matrixA.txt with Armadillo

	arma::mat p0(R,1,fill::zeros);
	p0.load("vectorp0.txt");

	cout <<"Matrix A (Coefficient Matrix):" << "\n" << A <<endl;
	
	arma::mat A_transpose(C,R,fill::zeros); 
	A_transpose = A.t();

	arma::mat AtA(C,C,fill::zeros); 
	arma::mat AtA_inv(C,C,fill::zeros); 
	AtA = A_transpose*A;
	AtA_inv = inv(AtA);

	cout <<"A^T:" << "\n" << A_transpose <<endl;
	cout <<"A^T * A:" << "\n" << AtA <<endl;
	cout <<"det(A^T * A):"  << det(AtA) <<endl;
	cout <<"(A^T * A)^{-1}:" << "\n" << AtA_inv <<endl;
	
	arma::mat P(C,C,fill::zeros);
	P = A * inv(AtA) * A_transpose;
	cout <<"[P]:" << "\n" << P <<endl;
	
	// Find the orthogonal projection of a point P0(2,1,-1) on plane W
	arma::mat Pp0(R,1,fill::zeros);
	Pp0 = P*p0;
	cout <<"The orthogonal projection of a point P0 (2,1,-1) on plane W with equation 3x-4y+z=0 is " << endl;
	cout <<"[P] * P0 :" << "\n" << Pp0 <<endl;
	
	cout <<"The  distance between the point P0 (2,1,-1) and the plane W with equation 3x-4y+z=0 is " << endl;
	// The general plane equation is ax+by+cz+d=0 
	float a = 3;
	float b = -4;
	float c = 1;
	float d = 0;
	float x0 = 2;
	float y0 = 1;
	float z0 = -1;

	float distance = sqrt( pow(x0-Pp0[0],2) + pow(y0-Pp0[1],2) +  pow(z0-Pp0[2],2));
	float D = abs(a*x0 + b*y0 + c*z0) / ( sqrt(pow(a,2) + pow(b,2) + pow(c,2)) );

	cout <<"d :" << distance <<endl;
	cout <<"D :" << D <<endl;
	
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

	// Create a vector of a point P0 (2,1,-1) 
	pts_A_x .push_back(o);
	pts_A_y .push_back(o);
	pts_A_z .push_back(o);
	pts_A_dx.push_back(p0[0]);
	pts_A_dy.push_back(p0[1]);
	pts_A_dz.push_back(p0[2]);	
	// Create a vector projection of P0 on W in R^3
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_z .push_back(o);
	pts_B_dx.push_back(Pp0[0]);
	pts_B_dy.push_back(Pp0[1]);
	pts_B_dz.push_back(Pp0[2]);
	// Create a distance vector  between  P0 and the vector projection of P0 on W in R^3
	pts_C_x .push_back(p0[0]);
	pts_C_y .push_back(p0[1]);
	pts_C_z .push_back(p0[2]);
	pts_C_dx.push_back(Pp0[0]-p0[0]);
	pts_C_dy.push_back(Pp0[1]-p0[1]);
	pts_C_dz.push_back(Pp0[2]-p0[2]);
	// Create the first basis vector for W
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(1);
	pts_D_dy.push_back(0);
	pts_D_dz.push_back(-3);
	// Create the second basis vector for W
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(0);
	pts_E_dy.push_back(1);
	pts_E_dz.push_back(4);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-1:3]\nset yrange [-1:3]\nset zrange [-5:5]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	// the splot '++' to create the plane W spanned by the vector columns of A / column space of A 
	gp << "splot '++' using 1:2:($1*-3 + $2*4) with lines lw 2 lc rgb 'gray' title 'W = c1(1,0,-3) + c2(0,1,4)', \
		'-' with vectors lw 3 lc rgb 'cyan' title 'P_{0} (2,1,-1)', '-' with vectors lw 3 lc rgb 'skyblue' title 'proj_{W} P_{0} ', \
		'-' with vectors lw 3 lc rgb 'navy' title 'd', '-' with vectors lw 3 lc rgb 'salmon' title '(1,0,-3)', '-' with vectors lw 3 lc rgb 'dark-red' title '(0,1,4)'\n";
	gp.send1d(boost::make_tuple(pts_A_x, pts_A_y,  pts_A_z, pts_A_dx, pts_A_dy, pts_A_dz));
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y,  pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	
	return 0;
}