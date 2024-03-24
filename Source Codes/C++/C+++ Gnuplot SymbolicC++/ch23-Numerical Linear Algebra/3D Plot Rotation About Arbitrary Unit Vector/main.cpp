// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams -larmadillo
// Hasta la Meo

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>
#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

#define N 3 // Define the number of dimension
#define theta 180 // Define the degree of rotation
#define DEGTORAD 0.0174532925199432957f

using namespace std;
using namespace arma;

void PrintMatrix(float a[][N])
{
	int r = N;
	int c = N;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << setprecision(0) << a[i][j] << "\t";
		cout << endl;
	}
}

int main() {
	Gnuplot gp;
	
	// Armadillo
	arma::mat X;
	arma::mat W;
	X.load("vectorX.txt");
	W.load("vectorW.txt");
	cout <<"Vector w:" << "\n" << W <<endl;
	cout <<"Vector x:" << "\n" << X <<endl;

	float a = X[0] / (sqrt(X[0]*X[0] + X[1]*X[1] + X[2]*X[2]));
	float b = X[1] / (sqrt(X[0]*X[0] + X[1]*X[1] + X[2]*X[2]));
	float c = X[2] / (sqrt(X[0]*X[0] + X[1]*X[1] + X[2]*X[2]));

	// Create standard matrix for rotation about arbitrary unit vector x
	float matrixAx[N][N] = {};

	matrixAx[0][0] = a*a*(1 - cos(theta*DEGTORAD)) + cos(theta*DEGTORAD);
	matrixAx[0][1] = a*b*(1 - cos(theta*DEGTORAD)) - c*sin(theta*DEGTORAD);
	matrixAx[0][2] = a*c*(1 - cos(theta*DEGTORAD)) + b*sin(theta*DEGTORAD);
	matrixAx[1][0] = a*b*(1 - cos(theta*DEGTORAD)) + c*sin(theta*DEGTORAD);
	matrixAx[1][1] = b*b*(1 - cos(theta*DEGTORAD)) + cos(theta*DEGTORAD);
	matrixAx[1][2] = b*c*(1 - cos(theta*DEGTORAD)) - a*sin(theta*DEGTORAD);
	matrixAx[2][0] = a*c*(1 - cos(theta*DEGTORAD)) - b*sin(theta*DEGTORAD);
	matrixAx[2][1] = b*c*(1 - cos(theta*DEGTORAD)) + a*sin(theta*DEGTORAD);
	matrixAx[2][2] = c*c*(1 - cos(theta*DEGTORAD)) + cos(theta*DEGTORAD);

	arma::mat ArmaUnitvectorx(N,1,fill::zeros); // Declare unit vector x of size N X 1 with Armadillo
	ArmaUnitvectorx[0] = a ;
	ArmaUnitvectorx[1] = b ;
	ArmaUnitvectorx[2] = c ;

	arma::mat ArmaAx(N,N,fill::zeros); // Declare matrix ArmaAx of size N X N with Armadillo
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAx[i+j*N] = matrixAx[i][j] ;
		}			
	}
	cout <<"Unit vector x:" << "\n" << ArmaUnitvectorx <<endl;

	cout <<"Standard Matrix for rotation about arbitrary unit vector x:" << "\n" << ArmaAx <<endl;

	arma::mat Wrotatex = ArmaAx*W ;
	cout <<"The rotated vector w through an angle " << theta << " degree about the unit vector x :" << "\n" << Wrotatex <<endl;
	
	// We use a separate container for each column, like so:
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

	float o = 0;
	
	// Create a unit vector x
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(a);
	pts_D_dy.push_back(b);
	pts_D_dz.push_back(c);
	// Create a vector w
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(W[0]);
	pts_E_dy.push_back(W[1]);
	pts_E_dz.push_back(W[2]);
	// Rotated vector w about unit vector x
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(Wrotatex[0]);
	pts_F_dy.push_back(Wrotatex[1]);
	pts_F_dz.push_back(Wrotatex[2]);
	
	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-0.5:1]\nset yrange [-0.5:1]\nset zrange [-1:1]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	//gp << "set view 80,45,1\n"; // pitch,yaw,zoom for diagonal x and y axis
	gp << "set view 80,90,1\n"; // pitch,yaw,zoom for y axis on front	
	//gp << "set view 80,0,1\n"; // pitch,yaw,zoom for x axis on front
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '-' with vectors title 'unit vector x','-' with vectors title 'w' lc 'blue','-' with vectors title 'w rotated counterclockwise about unit vector x' lc 'green'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));	
}