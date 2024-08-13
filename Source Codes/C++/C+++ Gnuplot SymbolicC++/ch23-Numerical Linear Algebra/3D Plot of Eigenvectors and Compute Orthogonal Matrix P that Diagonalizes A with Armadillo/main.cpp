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
	cx_mat eigvec;
	cx_vec eigval;

	mat I(3,3,fill::eye);
	cout <<"Matrix A:" << "\n" << A <<endl;
	
	eig_gen(eigval, eigvec, A); // Eigen decomposition of dense general square matrix

	cout << "Eigenvalues:" << endl;

	int n = 3;
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
	vec v3 = real(eigvec.col(2));

	//cout <<"v1 . v2:" << dot(v1,v2) <<endl;
	//cout <<"v2 . v3:" << dot(v2,v3) <<endl;
	
	mat P = real(eigvec);
	mat P_transpose = P.t();
	mat D = P_transpose*A*P;
	
	cout <<"Matrix P (which orthogonally diagonalizes A):" << "\n" << P <<endl;
	
	cout <<"Matrix P^{T} * A * P:" << "\n" << D <<endl;
	

	Gnuplot gp;

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

	float o = 0;
	
	// Create the orthonormal eigenvector v1
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(v1[0]);
	pts_D_dy.push_back(v1[1]);
	pts_D_dz.push_back(v1[2]);
	// Create the orthonormal eigenvector v2
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(v2[0]);
	pts_E_dy.push_back(v2[1]);
	pts_E_dz.push_back(v2[2]);
	// Create the orthonormal eigenvector v3
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(v3[0]);
	pts_F_dy.push_back(v3[1]);
	pts_F_dz.push_back(v3[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-1:1]\nset yrange [-1:1]\nset zrange [-1:1]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 80,90,1\n"; // pitch,yaw,zoom for y axis on front	
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '++' using 1:2:(0) with lines lw 2 lc rgb 'gray80' title 'xy-plane',\
		'-' with vectors lw 2 lc rgb 'dark-green' title '{/:Bold {v}_{1}}',\
		'-' with vectors lw 2 lc rgb 'dark-turquoise' title '{/:Bold {v}_{2}}',\
		'-' with vectors lw 2 lc rgb 'dark-red' title '{/:Bold {v}_{3}}'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));

	return 0;
}