// g++ -o result main.cpp
// Merci beaucoup Freya.. et Sentinel

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

using namespace std;
using namespace arma;

// Driver code
int main(int argc, char** argv)
{
	mat A;
	A.load("matrixA.txt");
	vec X;
	X.load("vectorX.txt");
	cx_mat eigvec;
	cx_vec eigval;

	mat I(2,2,fill::eye);
	cout <<"Matrix A:" << "\n" << A <<endl;
	
	eig_gen(eigval, eigvec, A); // Eigen decomposition of dense general square matrix

	cout << "Eigenvalues:" << endl;

	int n = 2;
	for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}
	
	cout << endl;
	mat A1 = I*real(eigval[0]) - A;
	mat A2 = I*real(eigval[1]) - A;
	mat A3 = I*real(eigval[2]) - A;
	cout <<"Matrix λ_1I - A:" << "\n" << A1 <<endl;
	cout <<"Matrix λ_2I - A:" << "\n" << A2 <<endl;
	
	cout << endl;
	cout << "Eigenspaces for λ_1: " <<  n - arma::rank(A1) << endl;
	cout << "Eigenspaces for λ_2: " <<  n - arma::rank(A2) << endl;
	cout << endl;
	
	cout << "Orthonormal Eigenvectors:" << endl;
	for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] :\n " << real(eigvec.col(i-1)) << endl;
	}

	// Save each orthonormal eigenvectors as a vector with Armadillo
	vec v1 = real(eigvec.col(0));
	vec v2 = real(eigvec.col(1));
	
	//cout <<"v1 . v2:" << dot(v1,v2) <<endl;
	
	// Spectral Decomposition of A for vector x=(1,1)
	vec spectral_decomp = A*X;
	vec spectral_decomp1 = v1*v1.t()*X;
	vec spectral_decomp2 = v2*v2.t()*X;
	vec scaled_spectral_decomp1 = v1*v1.t()*X*real(eigval[0]);
	vec scaled_spectral_decomp2 = v2*v2.t()*X*real(eigval[1]);
	
	mat P = real(eigvec);
	mat P_transpose = P.t();
	mat D = P_transpose*A*P;
	
	cout <<"Matrix P (which orthogonally diagonalizes A):" << "\n" << P <<endl;
	
	cout <<"Matrix P^{T} * A * P:" << "\n" << D <<endl;
	
	cout <<"Projection of vector x=(1,1) onto eigenspaces corresponding to λ_1 = "<< real(eigval[0])<< ":" << "\n" << spectral_decomp1 <<endl;
	cout <<"Projection of vector x=(1,1) onto eigenspaces corresponding to λ_2 = "<< real(eigval[1])<< ":" <<  "\n" << spectral_decomp2 <<endl;
	
	cout <<"Scaled spectral decomposition of x=(1,1) onto eigenspaces corresponding to λ_1 = "<< real(eigval[0])<< ":" << "\n" << scaled_spectral_decomp1 <<endl;
	cout <<"Scaled spectral decomposition of x=(1,1) onto eigenspaces corresponding to λ_2 = "<< real(eigval[1])<< ":" << "\n" << scaled_spectral_decomp2 <<endl;
	
	Gnuplot gp;

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
	std::vector<double> pts_K_x;
	std::vector<double> pts_K_y;
	std::vector<double> pts_K_dx;
	std::vector<double> pts_K_dy;	

	float o = 0;
	
	// Create the orthonormal eigenvector v1
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(v1[0]);
	pts_D_dy.push_back(v1[1]);
	// Create the orthonormal eigenvector v2
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(v2[0]);
	pts_E_dy.push_back(v2[1]);
	// Create the vector x = (1,1)
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_dx.push_back(X[0]);
	pts_F_dy.push_back(X[1]);
	// Projection of vector x=(1,1) onto eigenspaces corresponding to λ_1
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_dx.push_back(spectral_decomp1[0]);
	pts_G_dy.push_back(spectral_decomp1[1]);
	// Projection of vector x=(1,1) onto eigenspaces corresponding to λ_2
	pts_H_x .push_back(o);
	pts_H_y .push_back(o);
	pts_H_dx.push_back(spectral_decomp2[0]);
	pts_H_dy.push_back(spectral_decomp2[1]);
	// Projection of vector x=(1,1) onto eigenspaces corresponding to λ_1 then scaled with  λ_1 
	pts_I_x .push_back(o);
	pts_I_y .push_back(o);
	pts_I_dx.push_back(scaled_spectral_decomp1[0]);
	pts_I_dy.push_back(scaled_spectral_decomp1[1]);
	// Projection of vector x=(1,1) onto eigenspaces corresponding to λ_2 then scaled with  λ_2
	pts_J_x .push_back(o);
	pts_J_y .push_back(o);
	pts_J_dx.push_back(scaled_spectral_decomp2[0]);
	pts_J_dy.push_back(scaled_spectral_decomp2[1]);
	// Image of vector x=(1,1) under multiplication by matrix A
	pts_K_x .push_back(o);
	pts_K_y .push_back(o);
	pts_K_dx.push_back(spectral_decomp[0]);
	pts_K_dy.push_back(spectral_decomp[1]);
	
	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-1:4]\nset yrange [-1.5:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	///*	
	gp << "plot '-' with vectors lw 1 lc rgb 'dark-red' title '{/:Bold {x}}',\
		'-' with vectors lw 1 lc rgb 'dark-green' title '{/:Bold {spectral decomposition x on λ}_{1}}',\
		'-' with vectors lw 1 lc rgb 'dark-turquoise' title '{/:Bold {spectral decomposition x on λ}_{2}}',\
		'-' with vectors lw 2 lc rgb 'dark-green' dashtype 3 title '{/:Bold {scaled spectral decomposition x on λ}_{1}}',\
		'-' with vectors lw 2 lc rgb 'dark-turquoise' dashtype 3 title '{/:Bold {scaled spectral decomposition x on λ}_{2}}',\
		'-' with vectors lw 2 lc rgb 'dark-red' title 'A{/:Bold {x}}'\n";
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_dx, pts_G_dy));
	gp.send1d(boost::make_tuple(pts_H_x, pts_H_y, pts_H_dx, pts_H_dy));
	gp.send1d(boost::make_tuple(pts_I_x, pts_I_y, pts_I_dx, pts_I_dy));
	gp.send1d(boost::make_tuple(pts_J_x, pts_J_y, pts_J_dx, pts_J_dy));
	gp.send1d(boost::make_tuple(pts_K_x, pts_K_y, pts_K_dx, pts_K_dy));
	//*/

	// to plot the orthonormal eigenvectors and vector x only
	/* 
	gp << "plot '-' with vectors lw 1 lc rgb 'black' title '{/:Bold {u}_{1}}',\
		'-' with vectors lw 1 lc rgb 'gray50' title '{/:Bold {u}_{2}}',\
		'-' with vectors lw 1 lc rgb 'dark-red' title '{/:Bold {x}}'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
	*/

	return 0;
}