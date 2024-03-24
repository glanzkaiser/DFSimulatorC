
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
	X.load("vectorX.txt");
	cout <<"Vector x:" << "\n" << X <<endl;
	
	// Create standard matrix for orthogonal projection on y-axis
	float matrixAy[N][N] = {};
	// Create standard matrix for orthogonal projection on x-axis
	float matrixAx[N][N] = {};
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixAy[i][j] = 1;
				matrixAx[i][j] = 1;
			}
			else
			{
				matrixAy[i][j] = 0;		
				matrixAx[i][j] = 0;		
			}
		}			
	}	
	matrixAy[0][0] = 0;
	matrixAx[1][1] = 0;

	arma::mat ArmaAy(N,N,fill::zeros); // Declare matrix ArmaAy of size N X N with Armadillo
	arma::mat ArmaAx(N,N,fill::zeros); // Declare matrix ArmaAx of size N X N with Armadillo
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAy[i+j*N] = matrixAy[i][j] ;
			ArmaAx[i+j*N] = matrixAx[i][j] ;
		}			
	}
	
	//PrintMatrix(matrixAy);
	//PrintMatrix(matrixAx);
	cout <<"Standard Matrix for orthogonal projection on the x-axis:" << "\n" << ArmaAy <<endl;
	cout <<"Standard Matrix for orthogonal projection on the y-axis:" << "\n" << ArmaAx <<endl;

	arma::mat Xorthoprojecty = ArmaAy*X ;
	arma::mat Xorthoprojectx = ArmaAx*X ;
	cout <<"The orthogonal projection of vector x on the x-axis:" << "\n" << Xorthoprojectx <<endl;
	cout <<"The orthogonal projection of vector x on the y-axis:" << "\n" << Xorthoprojecty <<endl;
	
	// We use a separate container for each column, like so:
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
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(X[0]);
	pts_D_dy.push_back(X[1]);
	// The orthogonal projection of vector x on the x-axis
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(Xorthoprojectx[0]);
	pts_E_dy.push_back(Xorthoprojectx[1]);
	// The orthogonal projection of vector x on the y-axis
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_dx.push_back(Xorthoprojecty[0]);
	pts_F_dy.push_back(Xorthoprojecty[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1.5:2]\nset yrange [-1.5:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = x\n";
	gp << "plot '-' with vectors title 'x','-' with vectors title 'orthogonal projection of x on x-axis' lc 'green', '-' with vectors title 'orthogonal projection of x on y-axis'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
}