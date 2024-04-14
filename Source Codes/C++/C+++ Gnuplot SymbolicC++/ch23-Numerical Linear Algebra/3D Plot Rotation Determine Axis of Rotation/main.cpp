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
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

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
	cout <<"Vector x = " << "\n" << X <<endl;

	// Create standard matrix for rotation about arbitrary unit vector x
	float matrixAx[N][N] = {};

	matrixAx[0][0] = float(1.0/9.0);
	matrixAx[0][1] = float(-4.0/9.0);
	matrixAx[0][2] = float(8.0/9.0);
	matrixAx[1][0] = float(8.0/9.0);
	matrixAx[1][1] = float(4.0/9.0);
	matrixAx[1][2] = float(1.0/9.0);
	matrixAx[2][0] = float(-4.0/9.0);
	matrixAx[2][1] = float(7.0/9.0);
	matrixAx[2][2] = float(4.0/9.0);

	float traceA = 0;
	// Operation to compute the trace of a matrix 
	for (int i = 0; i < N; i++)
	{
		traceA += matrixAx[i][i];;
	}

	arma::mat ArmaAx(N,N,fill::zeros); // Declare matrix ArmaAx of size N X N with Armadillo
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAx[i+j*N] = matrixAx[i][j] ;
		}			
	}
	cout <<"tr(A) = " << traceA <<endl;
	// cout <<"tr(A):" << "\n" << trace(ArmaAx) <<endl;
	float theta = acos((traceA - 1)/2);
	cout <<"Angle of rotation = acos ( (tr(A) - 1) / 2 ) = " << float(theta*RADTODEG) <<endl;
	
	cout <<"Standard Matrix for rotation about an axis of rotation:\n" << "A = \n " << ArmaAx <<endl;
	cout <<"A^T = " << "\n" << ArmaAx.t() <<endl;

	arma::mat axisofrotation(N,1,fill::zeros); // Declare matrix axisofrotation of size N X 1 with Armadillo
	axisofrotation = ArmaAx*X + (ArmaAx.t())*X + (1-traceA)*X;
	float normaor = sqrt(axisofrotation[0]*axisofrotation[0] + axisofrotation[1]*axisofrotation[1] + axisofrotation[2]*axisofrotation[2]) ;
	
	cout <<"Axis of rotation = \n" << axisofrotation <<endl;
	cout << "Norm for axis of rotation = " << normaor << endl;
	cout <<"Normalized axis of rotation (vector with length / norm of 1) = \n" << axisofrotation/normaor <<endl;
	
	arma::mat Xrotatex = ArmaAx*X ;
	cout <<"The rotated vector x through an angle " << float(theta*RADTODEG)  << " degree about an axis of rotation : " << "\n" << Xrotatex <<endl;
	
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
	
	// Create an axis of rotation
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(axisofrotation[0]);
	pts_D_dy.push_back(axisofrotation[1]);
	pts_D_dz.push_back(axisofrotation[2]);
	// Create a vector x
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(X[0]);
	pts_E_dy.push_back(X[1]);
	pts_E_dz.push_back(X[2]);
	// Rotated vector x about an axis of rotation
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(Xrotatex[0]);
	pts_F_dy.push_back(Xrotatex[1]);
	pts_F_dz.push_back(Xrotatex[2]);
	// Create an axis of rotation
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_z .push_back(o);
	pts_G_dx.push_back(axisofrotation[0]/normaor);
	pts_G_dy.push_back(axisofrotation[1]/normaor);
	pts_G_dz.push_back(axisofrotation[2]/normaor);
	
	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-0.5:1]\nset yrange [-0.5:1]\nset zrange [-1:1]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	//gp << "set view 80,45,1\n"; // pitch,yaw,zoom for diagonal x and y axis
	gp << "set view 80,90,1\n"; // pitch,yaw,zoom for y axis on front	
	//gp << "set view 80,0,1\n"; // pitch,yaw,zoom for x axis on front
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '-' with vectors title 'axis of rotation' dashtype 2,'-' with vectors title 'x' lc 'blue','-' with vectors title 'x rotated counterclockwise about an axis of rotation' lc 'green','-' with vectors title 'normalized axis of rotation' lc 'black'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));	
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_z, pts_G_dx, pts_G_dy, pts_G_dz));	
}