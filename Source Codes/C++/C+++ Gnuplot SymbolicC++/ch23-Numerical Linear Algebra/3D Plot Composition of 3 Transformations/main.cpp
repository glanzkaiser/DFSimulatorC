
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
	
	// Create standard matrix for reflection about xy-plane
	float matrixAxy[N][N] = {};
	// Create standard matrix for reflection about xz-plane
	float matrixAxz[N][N] = {};
	// Create standard matrix for reflection about yz-plane
	float matrixAyz[N][N] = {};
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixAxy[i][j] = 1;
				matrixAxz[i][j] = 1;
				matrixAyz[i][j] = 1;
			}
			else
			{
				matrixAxy[i][j] = 0;		
				matrixAxz[i][j] = 0;	
				matrixAyz[i][j] = 0;			
			}
		}			
	}	
	matrixAxy[2][2] = -1;
	matrixAxz[1][1] = -1;
	matrixAyz[0][0] = -1;

	// Create standard matrix for orthogonal projection on xy-plane
	float matrixAorthogonalprojxy[N][N] = {};
	// Create standard matrix for orthogonal projection on xz-plane
	float matrixAorthogonalprojxz[N][N] = {};
	// Create standard matrix for orthogonal projection on yz-plane
	float matrixAorthogonalprojyz[N][N] = {};
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixAorthogonalprojxy[i][j] = 1;
				matrixAorthogonalprojxz[i][j] = 1;
				matrixAorthogonalprojyz[i][j] = 1;
			}
			else
			{
				matrixAorthogonalprojxy[i][j] = 0;		
				matrixAorthogonalprojxz[i][j] = 0;	
				matrixAorthogonalprojyz[i][j] = 0;			
			}
		}			
	}	
	matrixAorthogonalprojxy[2][2] = 0;
	matrixAorthogonalprojxz[1][1] = 0;
	matrixAorthogonalprojyz[0][0] = 0;

	// Create standard matrix for rotation about positive x-axis
	float matrixArotatex[N][N] = {};
	// Create standard matrix for rotation about positive y-axis
	float matrixArotatey[N][N] = {};
	// Create standard matrix for rotation about positive z-axis
	float matrixArotatez[N][N] = {};
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			if (i == j) 
			{
				matrixArotatex[i][j] = 1;
				matrixArotatey[i][j] = 1;
				matrixArotatez[i][j] = 1;
			}
			else
			{
				matrixArotatex[i][j] = 0;		
				matrixArotatey[i][j] = 0;	
				matrixArotatez[i][j] = 0;			
			}
		}			
	}	
	matrixArotatex[1][1] = cos(theta*DEGTORAD);
	matrixArotatex[1][2] = -sin(theta*DEGTORAD);
	matrixArotatex[2][1] = sin(theta*DEGTORAD);
	matrixArotatex[2][2] = cos(theta*DEGTORAD);

	matrixArotatey[0][0] = cos(theta*DEGTORAD);
	matrixArotatey[0][2] = -sin(theta*DEGTORAD);
	matrixArotatey[0][2] = sin(theta*DEGTORAD);
	matrixArotatey[2][2] = cos(theta*DEGTORAD);

	matrixArotatez[0][0] = cos(theta*DEGTORAD);
	matrixArotatez[0][1] = -sin(theta*DEGTORAD);
	matrixArotatez[1][0] = sin(theta*DEGTORAD);
	matrixArotatez[1][1] = cos(theta*DEGTORAD);

	arma::mat ArmaAxy(N,N,fill::zeros); // Declare matrix ArmaAxy of size N X N with Armadillo
	arma::mat ArmaAxz(N,N,fill::zeros); // Declare matrix ArmaAxz of size N X N with Armadillo
	arma::mat ArmaAyz(N,N,fill::zeros); // Declare matrix ArmaAyz of size N X N with Armadillo
	arma::mat ArmaAorthogonalprojxy(N,N,fill::zeros); 
	arma::mat ArmaAorthogonalprojxz(N,N,fill::zeros); 
	arma::mat ArmaAorthogonalprojyz(N,N,fill::zeros); 
	arma::mat ArmaArotatex(N,N,fill::zeros); 
	arma::mat ArmaArotatey(N,N,fill::zeros); 
	arma::mat ArmaArotatez(N,N,fill::zeros); 

	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAxy[i+j*N] = matrixAxy[i][j] ;
			ArmaAxz[i+j*N] = matrixAxz[i][j] ;
			ArmaAyz[i+j*N] = matrixAyz[i][j] ;
			ArmaAorthogonalprojxy[i+j*N] = matrixAorthogonalprojxy[i][j] ;
			ArmaAorthogonalprojxz[i+j*N] = matrixAorthogonalprojxz[i][j] ;
			ArmaAorthogonalprojyz[i+j*N] = matrixAorthogonalprojyz[i][j] ;
			ArmaArotatex[i+j*N] = matrixArotatex[i][j];
			ArmaArotatey[i+j*N] = matrixArotatey[i][j];
			ArmaArotatez[i+j*N] = matrixArotatez[i][j];

		}			
	}
	
	arma::mat Xreflectedxy = ArmaAxy*X ;
	arma::mat Xreflectedxz = ArmaAxz*X ;
	arma::mat Xreflectedyz = ArmaAyz*X ;

	arma::mat Xorthoprojectxy = ArmaAorthogonalprojxy*X ;
	arma::mat Xorthoprojectxz = ArmaAorthogonalprojxz*X ;
	arma::mat Xorthoprojectyz = ArmaAorthogonalprojyz*X ;

	arma::mat Xrotatex = ArmaArotatex*X ;
	arma::mat Xrotatey = ArmaArotatey*X ;
	arma::mat Xrotatez = ArmaArotatez*X ;

	arma::mat T1 = Xrotatez;
	arma::mat T2 = ArmaAyz*T1;
	arma::mat T3 = ArmaAorthogonalprojxy*T2;
	
	cout <<"T1(x) = Vector x is rotated counterclockwise about the positive z-axis with angle of " << theta << " :" << "\n" << T1 <<endl;
	cout <<"T2(T1(x)) = T1(x) is reflected about the yz-plane:" << "\n" << T2 <<endl;
	cout <<"T3(T2(T1(x))) = The orthogonal projection of T2(T1(x)) on the xy-plane:" << "\n" << T3 <<endl;
		
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
	// First transformation
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(T1[0]);
	pts_E_dy.push_back(T1[1]);
	pts_E_dz.push_back(T1[2]);
	// Second transformation
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(T2[0]);
	pts_F_dy.push_back(T2[1]);
	pts_F_dz.push_back(T2[2]);
	// Third transformation
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_z .push_back(o);
	pts_G_dx.push_back(T3[0]);
	pts_G_dy.push_back(T3[1]);
	pts_G_dz.push_back(T3[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1:1]\nset yrange [-1:1]\nset zrange [-1:1]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 60,5,1\n"; // pitch,yaw,zoom
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '-' with vectors title 'x','-' with vectors title 'T1(x)' lc 'green', '-' with vectors title 'T2(T1(x))', '-' with vectors title 'T3(T2(T1(x)))' lc 'orange'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_z, pts_G_dx, pts_G_dy, pts_G_dz));	
}