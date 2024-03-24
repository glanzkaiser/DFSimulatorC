
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

#define N 2 // Define the number of dimension

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
	arma::mat Y;
	X.load("vectorX.txt");
	Y.load("vectorY.txt");
	cout <<"Vector x:" << "\n" << X <<endl;
	cout <<"Vector y:" << "\n" << Y <<endl;
	
	// Create standard matrix for contraction
	float matrixAcontraction[N][N] = {};
	// Create standard matrix for dilation
	float matrixAdilation[N][N] = {};
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixAcontraction[i][j] = 0.3;
				matrixAdilation[i][j] = 2;
			}
			else
			{
				matrixAcontraction[i][j] = 0;		
				matrixAdilation[i][j] = 0;		
			}
		}			
	}	

	arma::mat ArmaAcontraction(N,N,fill::zeros); 
	arma::mat ArmaAdilation(N,N,fill::zeros); 
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAcontraction[i+j*N] = matrixAcontraction[i][j] ;
			ArmaAdilation[i+j*N] = matrixAdilation[i][j] ;
		}			
	}
	
	//PrintMatrix(matrixAy);
	//PrintMatrix(matrixAx);
	cout <<"Standard Matrix for contraction (0 <= k < 1):" << "\n" << ArmaAcontraction <<endl;
	cout <<"Standard Matrix for dilation (k>1):" << "\n" << ArmaAdilation <<endl;

	arma::mat Xcontraction = ArmaAcontraction*X ;
	arma::mat Ydilation = ArmaAdilation*Y ;
	cout <<"The contraction of vector x:" << "\n" << Xcontraction <<endl;
	cout <<"The dilation of vector y:" << "\n" << Ydilation <<endl;
	
	// We use a separate container for each column, like so:
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
	
	// Create a vector x
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_dx.push_back(X[0]);
	pts_C_dy.push_back(X[1]);
	// Create a vector y
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(Y[0]);
	pts_D_dy.push_back(Y[1]);
	// The contraction of vector x 
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(Xcontraction[0]);
	pts_E_dy.push_back(Xcontraction[1]);
	// The dilation of vector y
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_dx.push_back(Ydilation[0]);
	pts_F_dy.push_back(Ydilation[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [0:2.5]\nset yrange [0:1.5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot '-' with vectors title 'x','-' with vectors title 'y' lc 'blue','-' with vectors title 'contraction of x' lc 'green', '-' with vectors title 'dilation of y'\n";
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
}