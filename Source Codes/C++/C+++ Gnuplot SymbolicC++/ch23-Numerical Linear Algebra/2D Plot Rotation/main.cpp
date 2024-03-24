
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams -larmadillo

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>
#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

#define theta 60 // Define the degree of rotation
#define N 2 // Define the number of dimension
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
	X.load("vectorX.txt");
	cout <<"Vector x:" << "\n" << X <<endl;
	
	// Create standard matrix for counterclockwise rotation through angle theta
	float matrixA[N][N] = {};
	matrixA[0][0] = cos(theta*DEGTORAD);
	matrixA[0][1] = -sin(theta*DEGTORAD);
	matrixA[1][0] = sin(theta*DEGTORAD);
	matrixA[1][1] = cos(theta*DEGTORAD);
	
	arma::mat ArmaA(N,N,fill::zeros); // Declare matrix ArmaA of size N X N with Armadillo
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaA[i+j*N] = matrixA[i][j] ;
		}			
	}
	
	cout <<"Standard Matrix for rotation with angle of " << theta << " :" << "\n" << ArmaA <<endl;

	arma::mat Xrotate = ArmaA*X ;
	cout <<"The rotated vector x:" << "\n" << Xrotate <<endl;
	
	// We use a separate container for each column, like so:
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;	
	std::vector<double> pts_E_x;
	std::vector<double> pts_E_y;
	std::vector<double> pts_E_dx;
	std::vector<double> pts_E_dy;	
	
	float o = 0;
	
	// Create a vector x
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(X[0]);
	pts_D_dy.push_back(X[1]);
	// The counterclockwise rotation of vector x through angle theta
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(Xrotate[0]);
	pts_E_dy.push_back(Xrotate[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1.5:2]\nset yrange [-1.5:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = x\n";
	gp << "plot '-' with vectors title 'x','-' with vectors title 'x after rotation' lc 'green'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
}