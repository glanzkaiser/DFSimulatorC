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

int main() {
	Gnuplot gp;

	// Armadillo
	arma::mat X;
	arma::mat Y;
	arma::mat Z;
	arma::mat Q;
	X.load("vectorX.txt");
	Y.load("vectorY.txt");
	Z.load("vectorZ.txt");
	Q.load("vectorQ.txt");
	cout <<"Vector u1:" << "\n" << X <<endl;
	cout <<"Vector u2:" << "\n" << Y <<endl;
	cout <<"Vector u3:" << "\n" << Z <<endl;
	
	// Create standard matrix for rotation about x-axis
	float matrixAx[N][N] = {};
	// Create standard matrix for rotation about y-axis
	float matrixAy[N][N] = {};
	// Create standard matrix for rotation about z-axis
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
			ArmaAx[i+j*N] = matrixAx[i][j] ; // Standard Matrix for rotation about x-axis 
			ArmaAy[i+j*N] = matrixAy[i][j] ; // Standard Matrix for rotation about y-axis 
			ArmaAz[i+j*N] = matrixAz[i][j] ; // Standard Matrix for rotation about z-axis 
		}			
	}
	// Standard Matrix for rotation about z-axis = Transition matrix from B' to B
	arma::mat ArmaAz_Transpose  = ArmaAz.t();
	cout <<"P (Transition matrix from B' to B):" << "\n" << ArmaAz <<endl;
	cout <<"P^{T} (Transition matrix from B to B'):" << "\n" << ArmaAz_Transpose <<endl;

	arma::mat Xrotatez = ArmaAz*X ;
	arma::mat Yrotatez = ArmaAz*Y ;
	cout <<"The rotated vector u1 about positive z-axis:" << "\n" << Xrotatez <<endl;
	cout <<"The rotated vector u2 about positive z-axis:" << "\n" << Yrotatez <<endl;
	
	arma::mat PTQ;
	PTQ = ArmaAz_Transpose*Q;

	cout <<"Q relative to the xyz-system:" << endl;	
	cout <<"(x, y,z) = " << "( " << Q[0] << ", " << Q[1] << ", " << Q[2] << " )"<<endl;
	cout <<"Q relative to the x'y'z'-system:" << endl;
	cout <<"(x', y', z') = " << "( " << PTQ[0] << ", " << PTQ[1] << ", " << PTQ[2] << " )"<<endl;

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
	std::vector<double> pts_H_x;
	std::vector<double> pts_H_y;
	std::vector<double> pts_H_z;
	std::vector<double> pts_H_dx;
	std::vector<double> pts_H_dy;	
	std::vector<double> pts_H_dz;
	float o = 0;
	
	// Create a vector u1
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(X[0]);
	pts_D_dy.push_back(X[1]);
	pts_D_dz.push_back(X[2]);
	// Create a vector u2
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(Y[0]);
	pts_E_dy.push_back(Y[1]);
	pts_E_dz.push_back(Y[2]);
	// Create a vector u3
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(Z[0]);
	pts_F_dy.push_back(Z[1]);
	pts_F_dz.push_back(Z[2]);
	//  Rotated vector u1 about positive z-axis
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_z .push_back(o);
	pts_G_dx.push_back(Xrotatez[0]);
	pts_G_dy.push_back(Xrotatez[1]);
	pts_G_dz.push_back(Xrotatez[2]);
	//  Rotated vector u2 about positive z-axis
	pts_H_x .push_back(o);
	pts_H_y .push_back(o);
	pts_H_z .push_back(o);
	pts_H_dx.push_back(Yrotatez[0]);
	pts_H_dy.push_back(Yrotatez[1]);
	pts_H_dz.push_back(Yrotatez[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-0.5:1]\nset yrange [-0.5:1]\nset zrange [-1:1]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	//gp << "set view 80,45,1\n"; // pitch,yaw,zoom for diagonal x and y axis
	gp << "set view 80,90,1\n"; // pitch,yaw,zoom for y axis on front	
	//gp << "set view 80,0,1\n"; // pitch,yaw,zoom for x axis on front
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '-' with vectors lw 1 lc rgb 'dark-green' title '{/:Bold {u}_{1}}',\
		'-' with vectors lw 1 lc rgb 'dark-turquoise' title '{/:Bold {u}_{2}}',\
		'-' with vectors lw 1 lc rgb 'dark-red' title '{/:Bold {u}_{3}}',\
		'-' with vectors lw 3 lc rgb 'dark-green' title 'rotated {/:Bold {u}_{1}}',\
		'-' with vectors lw 3 lc rgb 'dark-turquoise' title 'rotated {/:Bold {u}_{2}}',\
		'vectorQ.dat' with points pt 7 ps 2 title 'Q'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_z, pts_G_dx, pts_G_dy, pts_G_dz));
	gp.send1d(boost::make_tuple(pts_H_x, pts_H_y, pts_H_z, pts_H_dx, pts_H_dy, pts_H_dz));	
}