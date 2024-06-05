
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
	cout <<"Vector x:" << "\n" << X <<endl;
	
	float a = 1.2;
	float b = 1.3;
	float λ = sqrt(pow(a,2)+pow(b,2));
	// theta is in radian
	float theta = acos(a/λ); // acos(a/λ) = asin(b/λ)

	// Create matrix C
	float matrixC[N][N] = {};
	// Create standard matrix for counterclockwise rotation
	float matrixRotation[N][N] = {};
	matrixRotation[0][0] = cos(theta);
	matrixRotation[0][1] = -sin(theta);
	matrixRotation[1][0] = sin(theta);
	matrixRotation[1][1] = cos(theta);
	// Create matrix for scaling
	float matrixScaling[N][N] = {};
	
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixC[i][j] = a; 
				matrixScaling[i][j] = λ;
			}
			else
			{
				matrixC[i][j] = b; 
				matrixScaling[i][j] = 0;		
			}
		}			
	}	
	matrixC[0][1] = -b;

	arma::mat ArmaScaling(N,N,fill::zeros); 
	arma::mat ArmaRotation(N,N,fill::zeros); 
	arma::mat ArmaC(N,N,fill::zeros); 
	
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaScaling[i+j*N] = matrixScaling[i][j] ;
			ArmaRotation[i+j*N] = matrixRotation[i][j] ;
			ArmaC[i+j*N] = matrixC[i][j] ;		
		}			
	}
	
	cout <<"Matrix C:" << "\n" << ArmaC <<endl;
	cout <<"Standard Matrix for scaling:" << "\n" << ArmaScaling <<endl;
	cout <<"Standard Matrix for counterclockwise rotation:" << "\n" << ArmaRotation <<endl;

	arma::mat Xrotated = ArmaRotation*X ;
	arma::mat Xscaled = ArmaScaling*Xrotated ;
	arma::mat CX = ArmaC*X ;
	cout <<"C*x:" << "\n" << CX <<endl;
	cout <<"Vector x rotated  with angle of " << theta*RADTODEG << " :" << "\n" << Xrotated <<endl;
	cout <<"Rotated vector x is being scaled by |λ|:" << "\n" << Xscaled <<endl;
	
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
	// The rotated vector x 
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(Xrotated[0]);
	pts_D_dy.push_back(Xrotated[1]);
	// The scaled vector x after rotated
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(Xscaled[0]);
	pts_E_dy.push_back(Xscaled[1]);
	// The scaled vector x after rotated with C
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_dx.push_back(CX[0]);
	pts_F_dy.push_back(CX[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [0:2.5]\nset yrange [0:2.5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot '-' with vectors title 'x','-' with vectors title 'Rotated x' lc 'blue', '-' with vectors title 'Scaled rotated x' lc 'green'\n";
	//gp << "plot '-' with vectors title 'x','-' with vectors title 'Rotated x' lc 'blue', '-' with vectors title 'Scaled rotated x' lc 'green', '-' with vectors title 'Cx' lc 'black'\n";
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	//gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
}