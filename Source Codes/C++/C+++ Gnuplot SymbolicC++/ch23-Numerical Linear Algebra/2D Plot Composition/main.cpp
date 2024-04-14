
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
	
	// Create standard matrix for orthogonal projection on y-axis
	float matrixAorthoprojy[N][N] = {};
	// Create standard matrix for orthogonal projection on x-axis
	float matrixAorthoprojx[N][N] = {};
	
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixAorthoprojy[i][j] = 1;
				matrixAorthoprojx[i][j] = 1;
			}
			else
			{
				matrixAorthoprojy[i][j] = 0;		
				matrixAorthoprojx[i][j] = 0;		
			}
		}			
	}	
	matrixAorthoprojy[0][0] = 0;
	matrixAorthoprojx[1][1] = 0;

	arma::mat ArmaA(N,N,fill::zeros); 
	arma::mat ArmaAorthoprojy(N,N,fill::zeros); 
	arma::mat ArmaAorthoprojx(N,N,fill::zeros); 

	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaA[i+j*N] = matrixA[i][j] ;
			ArmaAorthoprojy[i+j*N] = matrixAorthoprojy[i][j] ;
			ArmaAorthoprojx[i+j*N] = matrixAorthoprojx[i][j] ;
		}			
	}
	
	// Do the composition transformation
	arma::mat XT1 = ArmaA*X ; // rotate first
	arma::mat XT2 = ArmaAorthoprojy*XT1 ; // orthogonal projection on y-axis
	
	cout <<"The first transformation on vector x / T1(x) :" << "\n" << XT1 <<endl;
	cout <<"The second transformation on vector x / T2(x) :" << "\n" << XT2 <<endl;
	
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
	// The first transformation
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(XT1[0]);
	pts_E_dy.push_back(XT1[1]);
	// The second transformation
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_dx.push_back(XT2[0]);
	pts_F_dy.push_back(XT2[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1.5:2]\nset yrange [-1.5:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = x\n";
	gp << "plot '-' with vectors title 'x','-' with vectors title 'T1(x)' lc 'green', '-' with vectors title 'T2(T1(x))' lc 'blue'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
}