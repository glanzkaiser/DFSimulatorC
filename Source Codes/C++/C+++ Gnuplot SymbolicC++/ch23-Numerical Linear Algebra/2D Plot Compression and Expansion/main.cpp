
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
	
	// Create standard matrix for compression in the x-direction
	float matrixAcompressionx[N][N] = {};
	// Create standard matrix for expansion in the x-direction
	float matrixAexpansionx[N][N] = {};
	// Create standard matrix for compression in the y-direction
	float matrixAcompressiony[N][N] = {};
	// Create standard matrix for expansion in the y-direction
	float matrixAexpansiony[N][N] = {};
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixAcompressionx[i][j] = 0.3;
				matrixAexpansionx[i][j] = 2;
				matrixAcompressiony[i][j] = 0.3;
				matrixAexpansiony[i][j] = 2;
			}
			else
			{
				matrixAcompressionx[i][j] = 0;		
				matrixAexpansionx[i][j] = 0;
				matrixAcompressionx[i][j] = 0;
				matrixAexpansionx[i][j] = 0;		
			}
		}			
	}	
	matrixAcompressionx[1][1] = 1;
	matrixAexpansionx[1][1] = 1;
	matrixAcompressiony[0][0] = 1;
	matrixAexpansiony[0][0] = 1;

	arma::mat ArmaAcompressionx(N,N,fill::zeros); 
	arma::mat ArmaAexpansionx(N,N,fill::zeros); 
	arma::mat ArmaAcompressiony(N,N,fill::zeros); 
	arma::mat ArmaAexpansiony(N,N,fill::zeros); 
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAcompressionx[i+j*N] = matrixAcompressionx[i][j] ;
			ArmaAexpansionx[i+j*N] = matrixAexpansionx[i][j] ;
			ArmaAcompressiony[i+j*N] = matrixAcompressiony[i][j] ;
			ArmaAexpansiony[i+j*N] = matrixAexpansiony[i][j] ;
		}			
	}
	
	//PrintMatrix(matrixAy);
	//PrintMatrix(matrixAx);
	cout <<"Standard Matrix for compression in the x-direction (0 <= k < 1):" << "\n" << ArmaAcompressionx <<endl;
	cout <<"Standard Matrix for expansion in the x-direction (k>1):" << "\n" << ArmaAexpansionx <<endl;
	cout <<"Standard Matrix for compression in the y-direction (0 <= k < 1):" << "\n" << ArmaAcompressiony <<endl;
	cout <<"Standard Matrix for expansion in the y-direction (k>1):" << "\n" << ArmaAexpansiony <<endl;

	arma::mat Xcompressionx = ArmaAcompressionx*X ;
	arma::mat Xexpansionx = ArmaAexpansionx*X ;
	arma::mat Xcompressiony = ArmaAcompressiony*X ;
	arma::mat Xexpansiony = ArmaAexpansiony*X ;
	cout <<"The compression of vector x in the x-direction:" << "\n" << Xcompressionx <<endl;
	cout <<"The expansion of vector x in the x-direction:" << "\n" << Xexpansionx <<endl;
	cout <<"The compression of vector x in the y-direction:" << "\n" << Xcompressiony <<endl;
	cout <<"The expansion of vector x in the y-direction:" << "\n" << Xexpansiony <<endl;
	
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

	float o = 0;
	
	// Create a vector x
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_dx.push_back(X[0]);
	pts_C_dy.push_back(X[1]);
	// The compression of vector x in the x-direction
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(Xcompressionx[0]);
	pts_D_dy.push_back(Xcompressionx[1]);
	// The expansion of vector x in the x-direction
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(Xexpansionx[0]);
	pts_E_dy.push_back(Xexpansionx[1]);
	// The compression of vector x in the y-direction
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_dx.push_back(Xcompressiony[0]);
	pts_F_dy.push_back(Xcompressiony[1]);
	// The expansion of vector x in the y-direction
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_dx.push_back(Xexpansiony[0]);
	pts_G_dy.push_back(Xexpansiony[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [0:2.5]\nset yrange [0:1.5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot '-' with vectors title 'x','-' with vectors title 'compression of x in the x-direction' lc 'green', '-' with vectors title 'expansion of x in the x-direction' lc 'blue', '-' with vectors title 'compression of x in the y-direction', '-' with vectors title 'expansion of x in the y-direction'\n";
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_dx, pts_G_dy));
}