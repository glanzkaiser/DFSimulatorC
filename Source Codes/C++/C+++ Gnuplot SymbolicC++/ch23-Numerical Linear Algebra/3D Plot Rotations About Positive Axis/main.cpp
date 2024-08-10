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
#define theta 60 // Define the degree of rotation
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
	
	// Create standard matrix for rotation about positive x-axis
	float matrixAx[N][N] = {};
	// Create standard matrix for rotation about positive y-axis
	float matrixAy[N][N] = {};
	// Create standard matrix for rotation about positive z-axis
	float matrixAz[N][N] = {};
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixAx[i][j] = 1;
				matrixAy[i][j] = 1;
				matrixAz[i][j] = 1;
			}
			else
			{
				matrixAx[i][j] = 0;		
				matrixAy[i][j] = 0;	
				matrixAz[i][j] = 0;			
			}
		}			
	}	
	matrixAx[1][1] = cos(theta*DEGTORAD);
	matrixAx[1][2] = -sin(theta*DEGTORAD);
	matrixAx[2][1] = sin(theta*DEGTORAD);
	matrixAx[2][2] = cos(theta*DEGTORAD);

	matrixAy[0][0] = cos(theta*DEGTORAD);
	matrixAy[0][2] = sin(theta*DEGTORAD);
	matrixAy[2][0] = -sin(theta*DEGTORAD);
	matrixAy[2][2] = cos(theta*DEGTORAD);

	matrixAz[0][0] = cos(theta*DEGTORAD);
	matrixAz[0][1] = -sin(theta*DEGTORAD);
	matrixAz[1][0] = sin(theta*DEGTORAD);
	matrixAz[1][1] = cos(theta*DEGTORAD);

	arma::mat ArmaAx(N,N,fill::zeros); // Declare matrix ArmaAx of size N X N with Armadillo
	arma::mat ArmaAy(N,N,fill::zeros); // Declare matrix ArmaAy of size N X N with Armadillo
	arma::mat ArmaAz(N,N,fill::zeros); // Declare matrix ArmaAz of size N X N with Armadillo
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAx[i+j*N] = matrixAx[i][j] ;
			ArmaAy[i+j*N] = matrixAy[i][j] ;
			ArmaAz[i+j*N] = matrixAz[i][j] ;
		}			
	}
	
	cout <<"Standard Matrix for rotation about positive x-axis:" << "\n" << ArmaAx <<endl;
	cout <<"Standard Matrix for rotation about positive y-axis:" << "\n" << ArmaAy <<endl;
	cout <<"Standard Matrix for rotation about positive z-axis:" << "\n" << ArmaAz <<endl;

	arma::mat Xrotatex = ArmaAx*X ;
	arma::mat Xrotatey = ArmaAy*X ;
	arma::mat Xrotatez = ArmaAz*X ;
	cout <<"The rotated vector x about positive x-axis:" << "\n" << Xrotatex <<endl;
	cout <<"The rotated vector x about positive y-axis:" << "\n" << Xrotatey <<endl;
	cout <<"The rotated vector x about positive z-axis:" << "\n" << Xrotatez <<endl;
	
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
	std::vector<double> pts_G_x;
	std::vector<double> pts_G_y;
	std::vector<double> pts_G_z;
	std::vector<double> pts_G_dx;
	std::vector<double> pts_G_dy;	
	std::vector<double> pts_G_dz;

	float o = 0;
	
	// Create a vector x
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(X[0]);
	pts_D_dy.push_back(X[1]);
	pts_D_dz.push_back(X[2]);
	// Rotated vector x about positive x-axis
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(Xrotatex[0]);
	pts_E_dy.push_back(Xrotatex[1]);
	pts_E_dz.push_back(Xrotatex[2]);
	// Rotated vector x about positive y-axis
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(Xrotatey[0]);
	pts_F_dy.push_back(Xrotatey[1]);
	pts_F_dz.push_back(Xrotatey[2]);
	//  Rotated vector x about positive z-axis
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_z .push_back(o);
	pts_G_dx.push_back(Xrotatez[0]);
	pts_G_dy.push_back(Xrotatez[1]);
	pts_G_dz.push_back(Xrotatez[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-0.5:1]\nset yrange [-0.5:1]\nset zrange [-1:1]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	//gp << "set view 80,45,1\n"; // pitch,yaw,zoom for diagonal x and y axis
	gp << "set view 80,90,1\n"; // pitch,yaw,zoom for y axis on front	
	//gp << "set view 80,0,1\n"; // pitch,yaw,zoom for x axis on front
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '-' with vectors title 'x','-' with vectors title 'rotated x about positive x-axis' lc 'green', '-' with vectors title 'rotated x about positive y-axis', '-' with vectors title 'rotated x about positive z-axis' lc 'orange'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_z, pts_G_dx, pts_G_dy, pts_G_dz));	
}