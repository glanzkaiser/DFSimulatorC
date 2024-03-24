
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
	arma::mat B1x;
	arma::mat B2x;
	B1x.load("basis1x.txt");
	B2x.load("basis2x.txt");
	cout <<"Basis 1 for shear :" << "\n" << B1x <<endl;
	cout <<"Basis 2 for shear :" << "\n" << B2x <<endl;
	
	// Create standard matrix for Shear in the x-direction with k>0
	float matrixAshearxpositive[N][N] = {};
	// Create standard matrix for Shear in the x-direction with k<0
	float matrixAshearxnegative[N][N] = {};
	// Create standard matrix for Shear in the y-direction with k>0
	float matrixAshearypositive[N][N] = {};
	// Create standard matrix for Shear in the y-direction with k<0
	float matrixAshearynegative[N][N] = {};
		
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixAshearxpositive[i][j] = 1;
				matrixAshearxnegative[i][j] = 1;
				matrixAshearypositive[i][j] = 1;
				matrixAshearynegative[i][j] = 1;
			}
			else
			{
				matrixAshearxpositive[i][j] = 0;		
				matrixAshearxnegative[i][j]  = 0;
				matrixAshearypositive[i][j]  = 0;
				matrixAshearxnegative[i][j]  = 0;		
			}
		}			
	}	
	matrixAshearxpositive[0][1] = 0.3;
	matrixAshearxnegative[0][1] = -0.5;
	matrixAshearypositive[1][0] = 0.3;
	matrixAshearynegative[1][0] = -0.5;
	
	arma::mat ArmaAshearxpositive(N,N,fill::zeros); 
	arma::mat ArmaAshearxnegative(N,N,fill::zeros); 
	arma::mat ArmaAshearypositive(N,N,fill::zeros); 
	arma::mat ArmaAshearynegative(N,N,fill::zeros); 
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAshearxpositive[i+j*N] = matrixAshearxpositive[i][j] ;
			ArmaAshearxnegative[i+j*N] = matrixAshearxnegative[i][j] ;
			ArmaAshearypositive[i+j*N] = matrixAshearypositive[i][j] ;
			ArmaAshearynegative[i+j*N] = matrixAshearynegative[i][j] ;
		}			
	}
	
	//PrintMatrix(matrixAy);
	//PrintMatrix(matrixAx);
	cout <<"Standard Matrix for shear in the x-direction (k > 0):" << "\n" << ArmaAshearxpositive <<endl;
	cout <<"Standard Matrix for shear in the x-direction (k < 0):" << "\n" << ArmaAshearxnegative <<endl;
	cout <<"Standard Matrix for shear in the y-direction (k > 0):" << "\n" << ArmaAshearypositive <<endl;
	cout <<"Standard Matrix for shear in the y-direction (k < 0):" << "\n" << ArmaAshearynegative <<endl;
	
	arma::mat B1xshearxpositive = ArmaAshearxpositive*B1x ;
	arma::mat B2xshearxpositive = ArmaAshearxpositive*B2x ;
	arma::mat B1xshearxnegative = ArmaAshearxnegative*B1x ;
	arma::mat B2xshearxnegative = ArmaAshearxnegative*B2x ;
	arma::mat B1yshearypositive = ArmaAshearypositive*B1x ;
	arma::mat B2yshearypositive = ArmaAshearypositive*B2x ;
	arma::mat B1yshearynegative = ArmaAshearynegative*B1x ;
	arma::mat B2yshearynegative = ArmaAshearynegative*B2x ;
	
	cout <<"The shear of Basis 1 in the x-direction (k > 0):" << "\n" << B1xshearxpositive <<endl;
	cout <<"The shear of Basis 2 in the x-direction (k > 0):" << "\n" << B2xshearxpositive <<endl;
	cout <<"The shear of Basis 1 in the x-direction (k < 0):" << "\n" << B1xshearxnegative <<endl;
	cout <<"The shear of Basis 2 in the x-direction (k < 0):" << "\n" << B2xshearxnegative <<endl;
	cout <<"The shear of Basis 1 in the y-direction (k > 0):" << "\n" << B1yshearypositive <<endl;
	cout <<"The shear of Basis 2 in the y-direction (k > 0):" << "\n" << B2yshearypositive <<endl;
	cout <<"The shear of Basis 1 in the y-direction (k < 0):" << "\n" << B1yshearynegative <<endl;
	cout <<"The shear of Basis 2 in the y-direction (k < 0):" << "\n" << B2yshearynegative <<endl;
	
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
	std::vector<double> pts_G_x;
	std::vector<double> pts_G_y;
	std::vector<double> pts_G_dx;
	std::vector<double> pts_G_dy;
	std::vector<double> pts_H_x;
	std::vector<double> pts_H_y;
	std::vector<double> pts_H_dx;
	std::vector<double> pts_H_dy;
	std::vector<double> pts_I_x;
	std::vector<double> pts_I_y;
	std::vector<double> pts_I_dx;
	std::vector<double> pts_I_dy;
	std::vector<double> pts_J_x;
	std::vector<double> pts_J_y;
	std::vector<double> pts_J_dx;
	std::vector<double> pts_J_dy;

	float o = 0;
	
	// Create a basis 1 for shear in the x-direction
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_dx.push_back(B1x[0]);
	pts_C_dy.push_back(B1x[1]);
	// Create a basis 2 for shear in the x-direction
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(B2x[0]);
	pts_D_dy.push_back(B2x[1]);
	// Create a basis 1 for shear in the y-direction
	pts_E_x .push_back(o);
	pts_E_y .push_back(1.3);
	pts_E_dx.push_back(B1x[0]);
	pts_E_dy.push_back(B1x[1]);
	// Create a basis 2 for shear in the y-direction
	pts_F_x .push_back(o);
	pts_F_y .push_back(1.3);
	pts_F_dx.push_back(B2x[0]);
	pts_F_dy.push_back(B2x[1]);
	// The shear of vector basis 2 in the x-direction with k>0
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_dx.push_back(B2xshearxpositive[0]);
	pts_G_dy.push_back(B2xshearxpositive[1]);
	// The shear of vector basis 2 in the x-direction with k<0
	pts_H_x .push_back(o);
	pts_H_y .push_back(o);
	pts_H_dx.push_back(B2xshearxnegative[0]);
	pts_H_dy.push_back(B2xshearxnegative[1]);
	// The shear of vector basis 1 in the y-direction with k>0
	pts_I_x .push_back(o);
	pts_I_y .push_back(1.3);
	pts_I_dx.push_back(B1yshearypositive[0]);
	pts_I_dy.push_back(B1yshearypositive[1]);
	// The shear of vector basis 1 in the y-direction with k<0
	pts_J_x .push_back(o);
	pts_J_y .push_back(1.3);
	pts_J_dx.push_back(B1yshearynegative[0]);
	pts_J_dy.push_back(B1yshearynegative[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-0.55:2.5]\nset yrange [-0.3:2.5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot '-' with vectors title 'e_{1} for x-direction','-' with vectors title 'e_{2} for x-direction' lc 'green', '-' with vectors title 'e_{1} for y-direction' lc 'blue', '-' with vectors title 'e_{2} for y-direction', '-' with vectors title 'shear in the x-direction (k>0)' lc 'black' dashtype 2, '-' with vectors title 'shear in the x-direction (k<0)' lc 'black' dashtype 3,'-' with vectors title 'shear in the y-direction (k>0)' lc 'red' dashtype 2,'-' with vectors title 'shear in the y-direction (k<0)' lc 'red' dashtype 3\n";
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_dx, pts_G_dy));
	gp.send1d(boost::make_tuple(pts_H_x, pts_H_y, pts_H_dx, pts_H_dy));
	gp.send1d(boost::make_tuple(pts_I_x, pts_I_y, pts_I_dx, pts_I_dy));
	gp.send1d(boost::make_tuple(pts_J_x, pts_J_y, pts_J_dx, pts_J_dy));
}