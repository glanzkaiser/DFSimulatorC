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
	
	// Create standard matrix for orthogonal projection on xy-plane
	float matrixAxy[N][N] = {};
	// Create standard matrix for orthogonal projection on xz-plane
	float matrixAxz[N][N] = {};
	// Create standard matrix for orthogonal projection on yz-plane
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
	matrixAxy[2][2] = 0;
	matrixAxz[1][1] = 0;
	matrixAyz[0][0] = 0;

	arma::mat ArmaAxy(N,N,fill::zeros); // Declare matrix ArmaAxy of size N X N with Armadillo
	arma::mat ArmaAxz(N,N,fill::zeros); // Declare matrix ArmaAxz of size N X N with Armadillo
	arma::mat ArmaAyz(N,N,fill::zeros); // Declare matrix ArmaAyz of size N X N with Armadillo
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaAxy[i+j*N] = matrixAxy[i][j] ;
			ArmaAxz[i+j*N] = matrixAxz[i][j] ;
			ArmaAyz[i+j*N] = matrixAyz[i][j] ;
		}			
	}
	
	//PrintMatrix(matrixAy);
	//PrintMatrix(matrixAx);
	cout <<"Standard Matrix for orthogonal projection on the xy-plane:" << "\n" << ArmaAxy <<endl;
	cout <<"Standard Matrix for orthogonal projection on the xz-plane:" << "\n" << ArmaAxz <<endl;
	cout <<"Standard Matrix for orthogonal projection on the yz-plane:" << "\n" << ArmaAyz <<endl;

	arma::mat Xorthoprojectxy = ArmaAxy*X ;
	arma::mat Xorthoprojectxz = ArmaAxz*X ;
	arma::mat Xorthoprojectyz = ArmaAyz*X ;
	cout <<"The orthogonal projection of vector x on the xy-plane:" << "\n" << Xorthoprojectxy <<endl;
	cout <<"The orthogonal projection of vector x on the xz-plane:" << "\n" << Xorthoprojectxz <<endl;
	cout <<"The orthogonal projection of vector x on the yz-plane:" << "\n" << Xorthoprojectyz <<endl;
	
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
	// The orthogonal projection of vector x on the xy-plane
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(Xorthoprojectxy[0]);
	pts_E_dy.push_back(Xorthoprojectxy[1]);
	pts_E_dz.push_back(Xorthoprojectxy[2]);
	// The orthogonal projection of vector x on the xz-plane
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(Xorthoprojectxz[0]);
	pts_F_dy.push_back(Xorthoprojectxz[1]);
	pts_F_dz.push_back(Xorthoprojectxz[2]);
	// The orthogonal projection of vector x on the yz-plane
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_z .push_back(o);
	pts_G_dx.push_back(Xorthoprojectyz[0]);
	pts_G_dy.push_back(Xorthoprojectyz[1]);
	pts_G_dz.push_back(Xorthoprojectyz[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [0:1]\nset yrange [0:1]\nset zrange [0:1]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	//gp << "set view 80,45,1\n"; // pitch,yaw,zoom for xy plane
	//gp << "set view 80,90,1\n"; // pitch,yaw,zoom for xz plane		
	gp << "set view 80,0,1\n"; // pitch,yaw,zoom for yz plane
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '-' with vectors title 'x','-' with vectors title 'orthogonal projection of x on xy-plane' lc 'green', '-' with vectors title 'orthogonal projection of x on xz-plane', '-' with vectors title 'orthogonal projection of x on yz-plane' lc 'orange'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_z, pts_G_dx, pts_G_dy, pts_G_dz));	
}