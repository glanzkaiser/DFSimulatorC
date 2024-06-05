
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams -larmadillo

#include <vector>
#include <cmath>
#include <utility>
#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <armadillo>

#include "gnuplot-iostream.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

using namespace std;
using namespace arma;

double division(double x, double y)
{
	return x/y;
}

int main() {
	Gnuplot gp;
	int N = 2;
	vec x, y, ystdbasis;
	x.load("vectorx.txt");
	
	float theta = atan(division(3,4))*RADTODEG ;
	//cout <<"Tan(theta) :" << "\n" << tan(theta*DEGTORAD) <<endl;
	
	arma::mat xstdbasis(N,1,fill::zeros); 
	xstdbasis[0] = 1;
	xstdbasis[1] = division(1,2);
	arma::mat A(N,N,fill::zeros); 
	A[0] = division(1,2);
	A[1] = division(-3,5);
	A[2] = division(3,4);
	A[3] = division(11,10);
	
	cout <<"Matrix A :" << "\n" << A <<endl;
	cout <<"Vector x :" << "\n" << x <<endl;
	cout <<"Vector xstdbasis :" << "\n" << xstdbasis <<endl;
	cout <<"Ax:" << "\n" << A*x <<endl;	

	// Compute eigenvalues
	cx_vec eigval;
	cx_mat eigvec;
	
	eig_gen(eigval, eigvec, A); // Eigen decomposition of dense general square matrix

	cout << "Eigenvalues:" << endl;

	for (int i = 1; i <= N; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}
	cout << endl;
	cout <<"Eigenvectors:" << "\n" << eigvec <<endl; 
		
	arma::mat B(N,N,fill::zeros); 	
	B[0] = A[0];
	B[1] = A[1];
	B[2] = A[2];
	B[3] = A[3];
	
	int n = 15;
	// n = 1 makes B = A^2
	// n = 2 makes B = A^3
	// n = 3 makes B = A^4
	y = A*x;
	arma::mat PSA;
	// we can also declare a matrix PSA as a matrix with no column  / 0 column and n rows, since we will insert the column later on
	//arma::mat PSA(n,0,fill::zeros); 
	arma::vec Ax1(n,1);
	arma::vec Ax2(n,1);
	Ax1[0] = y[0];
	Ax2[0] = y[1];
	for (int i = 1; i <= n; i++) 
	{
		B*=A;
		// cout <<"A^{"<< i+1 << "}:" << "\n" << B <<endl;
		// cout <<"A^{"<< i+1 << "}*x:" << "\n" << B*x <<endl;
		y = B*x;
		Ax1[i] = y[0];
		Ax2[i] = y[1];
	}	

	PSA.insert_cols(0, Ax1);
	PSA.insert_cols(1, Ax2);

	cout << endl;	
	cout << "Power Sequences of A" << "\n" << PSA<< endl;
	// save matrix as a text file
	PSA.save("PSAMatrix.txt", raw_ascii);
  
	// Compute P S R_theta and P^{-1}
	// We choose λ = 0.8 - 0.6i, thus a = 0.8, b = 0.6
	float a = 0.8;
	float b = 0.6;
	float matrixC[N][N] = {};
	matrixC[0][0] = a;
	matrixC[0][1] = -b;
	matrixC[1][0] = b;
	matrixC[1][1] = a;
	
	arma::mat ArmaC(N,N,fill::zeros); 
	
	
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaC[i+j*N] = matrixC[i][j] ;		
		}			
	}

	// To compute and plot the points that move along a circular path
	arma::mat BN(N,N,fill::zeros); 	
	BN[0] = ArmaC[0];
	BN[1] = ArmaC[1];
	BN[2] = ArmaC[2];
	BN[3] = ArmaC[3];

	ystdbasis = ArmaC*xstdbasis;
	arma::mat PSStandardBasis;

	arma::vec Axnewbasis1(n,1);
	arma::vec Axnewbasis2(n,1);
	Axnewbasis1[0] = ystdbasis[0];
	Axnewbasis2[0] = ystdbasis[1];
	for (int i = 1; i <= n; i++) 
	{
		BN*=ArmaC;
		ystdbasis = BN*xstdbasis;
		Axnewbasis1[i] = ystdbasis[0];
		Axnewbasis2[i] = ystdbasis[1];
	}	

	PSStandardBasis.insert_cols(0, Axnewbasis1);
	PSStandardBasis.insert_cols(1, Axnewbasis2);

	cout << endl;	
	cout << "Power Sequences for standard basis (as new basis)" << "\n" << PSStandardBasis<< endl;
	// save matrix as a text file
	PSStandardBasis.save("PSStandardBasis.txt", raw_ascii);

	cout <<"For λ = 0.8 - 0.6 i, Matrix C:" << "\n" << ArmaC <<endl;

	arma::mat P(N,N,fill::zeros); 
	P.col(0) = real(eigvec.col(1)) ; // make Re(x) the first column for matrix P 
	P.col(1) = imag(eigvec.col(1)) ; // make Im(x) the second column for matrix P 
	cout <<"Matrix P:" << "\n" << P <<endl;
	
	arma::mat P_inv(N,N,fill::zeros); 
	P_inv = inv(P);
	cout <<"Matrix P^{-1}:" << "\n" << P_inv <<endl;
	
	cout <<"Matrix P * C * P^{-1}:" << "\n" << P*ArmaC*P_inv <<endl;
	
	// Don't forget to put "\n" at the end of each line!
	gp << "set key inside bottom right\n";
	gp << "set xlabel 'x'\n";
	gp << "set ylabel 'y'\n";
	gp << "set title 'Power Sequences of Matrix with Complex Eigenvalues'\n";
	gp << "set style line 1 lc rgb 'blue' pt 7\n";
	gp << "set style line 2 lc rgb 'green' pt 7\n";
	
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot  'PSAMatrix.txt' using 1:2 title 'A^{k} x' with points ls 1,  'PSStandardBasis.txt' using 1:2 title 'R_{θ} x_{std}' with points ls 2, \n";
		
	return 0;
}