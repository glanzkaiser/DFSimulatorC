// Change Reflection about Axis and Line
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
	
	// Create standard matrix for reflection about y-axis
	float matrixAy[N][N] = {};
	// Create standard matrix for reflection about x-axis
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
	matrixAy[0][0] = -1;
	matrixAx[1][1] = -1;

	// Create standard matrix for reflection about line y=x
	float matrixAlinex[N][N] = {};
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixAlinex[i][j] = 0;
			}
			else
			{
				matrixAlinex[i][j] = 1;			
			}
		}			
	}	
	arma::mat ArmaAy(N,N,fill::zeros); // Declare matrix ArmaAy of size N X N with Armadillo
	arma::mat ArmaAx(N,N,fill::zeros); // Declare matrix ArmaAx of size N X N with Armadillo
	arma::mat ArmaAlinex(N,N,fill::zeros); // Declare matrix ArmaAlinex of size N X N with Armadillo
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAy[i+j*N] = matrixAy[i][j] ;
			ArmaAx[i+j*N] = matrixAx[i][j] ;
			ArmaAlinex[i+j*N] = matrixAlinex[i][j];
		}			
	}
	
	//PrintMatrix(matrixAy);
	//PrintMatrix(matrixAx);
	cout <<"Standard Matrix for reflection about the y-axis:" << "\n" << ArmaAy <<endl;
	cout <<"Standard Matrix for reflection about the x-axis:" << "\n" << ArmaAx <<endl;
	cout <<"Standard Matrix for reflection about the line y=x:" << "\n" << ArmaAlinex <<endl;

	arma::mat Xreflectedy = ArmaAy*X ;
	arma::mat Xreflectedx = ArmaAx*X ;
	arma::mat Xreflectedlinex = ArmaAlinex*X ;
	cout <<"Vector x reflected about the y-axis:" << "\n" << Xreflectedy <<endl;
	cout <<"Vector x reflected about the x-axis:" << "\n" << Xreflectedx <<endl;
	cout <<"Vector x reflected about the line y=x:" << "\n" << Xreflectedlinex <<endl;
	
	// We use a separate container for each column, like so:
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
	std::vector<double> pts_G_x;
	std::vector<double> pts_G_y;
	std::vector<double> pts_G_dx;
	std::vector<double> pts_G_dy;	

	float o = 0;
	float e1x = 0;
	float e1y = 1;
	float e2x = 1;
	float e2y = 0;

	float vect_e1[] = { e1x,e1y };
	float vect_e2[] = { e2x,e2y };
	
	cout << "Vector e1:" << setw(15) << "vector e2:"  << endl;
	
	for (int i = 0; i < n; i++) 
	{
		cout << vect_e1[i]  << "\t" << "\t" << vect_e2[i] ;
		cout << endl;
	}
	cout << endl;
	
	// Create a vector with origin at (0,0) and terminal point at (1,0)
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_dx.push_back(e1x);
	pts_B_dy.push_back(e1y);
	// Create a vector with origin at (0,0) and terminal point at (0,1)
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_dx.push_back(e2x);
	pts_C_dy.push_back(e2y);
	// Create a vector x
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(X[0]);
	pts_D_dy.push_back(X[1]);
	// Reflection of vector x about the y-axis
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(Xreflectedy[0]);
	pts_E_dy.push_back(Xreflectedy[1]);
	// Reflection of vector x about the x-axis
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_dx.push_back(Xreflectedx[0]);
	pts_F_dy.push_back(Xreflectedx[1]);
	// Reflection of vector x about the x-axis
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_dx.push_back(Xreflectedlinex[0]);
	pts_G_dy.push_back(Xreflectedlinex[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1.5:2]\nset yrange [-1.5:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = x\n";
	gp << "plot '-' with vectors title 'e_{1}', '-' with vectors title 'e_{2}', '-' with vectors title 'x','-' with vectors title 'x reflected about y-axis' lc 'green', '-' with vectors title 'x reflected about x-axis', '-' with vectors title 'x reflected about line y=x' lc 'orange',f(x) title 'y=x' lc 'black;\n";
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_dx, pts_G_dy));
}