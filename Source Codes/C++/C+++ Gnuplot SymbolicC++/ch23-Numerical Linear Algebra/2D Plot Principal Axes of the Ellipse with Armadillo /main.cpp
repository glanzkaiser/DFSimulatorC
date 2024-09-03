// g++ -o result main.cpp -larmadillo -lboost_iostreams 
// Merci beaucoup Freya et Sentinel..

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>
#include <boost/tuple/tuple.hpp>
#include "symbolicc++.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
	
#include "gnuplot-iostream.h"

using namespace std;
using namespace arma;

double halving(double x)
{
	double y = 2;
	return x/y;
}

// Driver code
int main(int argc, char** argv)
{
	arma::mat A(2,2, fill::zeros);
	cx_mat eigvec;
	cx_vec eigval;

	mat I(2,2,fill::eye);
	// A conic with equation 5x^2 - 4xy + 8y^2 - 36 = 0	
	// We create symmetric matrix A from quadratic form Q
	int N = 2;
	float matrixA[N][N] = {};
	
	matrixA[0][0] = 5;
	matrixA[0][1] = halving(-4);
	matrixA[1][0] = halving(-4);
	matrixA[1][1] = 8;
	
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			A[i+j*N] = matrixA[i][j];
		}			
	}

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
	
	cout << "Orthonormal Eigenvectors:" << endl;
	for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] :\n " << real(eigvec.col(i-1)) << endl;
	}

	// Save each orthonormal eigenvectors as a vector with Armadillo
	arma::vec v1 = real(eigvec.col(0));
	arma::vec v2 = real(eigvec.col(1));
	
	mat P = real(eigvec);
	mat P_transpose = P.t();
	mat D = P_transpose*A*P;
	
	float matrixD[N][N] = {};
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			matrixD[i][j] = D[i+j*N];
		}			
	}

	cout <<"Matrix P (which orthogonally diagonalizes A):" << "\n" << P <<endl;
	cout <<"det(P):" << "\n" << det(P) <<endl;
	cout <<"\nMatrix P^{T} * A * P:" << "\n" << D <<endl;

	Symbolic x2("x2"), y2("y2");

	Symbolic yt = ( (  x2 ), (y2) );
	Symbolic y =yt.transpose();

	float d11 = lround(matrixD[0][0]); 
	float d22 = lround(matrixD[1][1]); 
	float d12 = lround(matrixD[0][1]); 
	
	Symbolic MatrixD = (  (Symbolic(d11), Symbolic(d12) ),
				( Symbolic(d12), Symbolic(d22) ) );
	
	cout << "x' = " << y << endl; 
	cout << "x'^{T} = " << yt << endl; 
	cout << "D = " << MatrixD << endl; 
	cout << "x'^{T} * D * x' = " << yt*MatrixD*y << " = 36 " << endl; 

	cout <<"\nThe angle which rotate the xy-axes" <<endl;
	cout <<"θ = " << atan(P[1]/P[0])*RADTODEG <<endl;
	
	// Plotting time
	Gnuplot gp;

	// We use a separate container for each column, like so:
	std::vector<double> pts_B_x;
	std::vector<double> pts_B_y;
	std::vector<double> pts_B_dx;
	std::vector<double> pts_B_dy;
	std::vector<double> pts_C_x;
	std::vector<double> pts_C_y;
	std::vector<double> pts_C_dx;
	std::vector<double> pts_C_dy;
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;	
	
	float o = 0;
	
	// Create eigenvector v1 with origin at (0,0) 
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_dx.push_back(-v1[0]);
	pts_B_dy.push_back(-v1[1]);
	// Create eigenvector v2 with origin at (0,0) 
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_dx.push_back(-v2[0]);
	pts_C_dy.push_back(-v2[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set parametric\n";
	//gp << "unset key\n";
	gp << "set zeroaxis lw 2\n";
	gp << "set xrange [-3.3:3.3]\nset yrange [-2.3:2.3]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot 3*cos(t),2*sin(t) title '(3 cos t, 2 sin t)' lt 3 lc rgb 'dark-turquoise',\
		'-' with vectors title 'v_{1}' lw 3, '-' with vectors title 'v_{2}' lw 3\n";
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));

	return 0;
}