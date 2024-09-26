// g++ -o result main.cpp
// Merci beaucoup Freya.. et Sentinel

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>

#include "symbolicc++.h"

using namespace std;
using namespace arma;

double halving(double x)
{
	double y = 2;
	return x/y;
}

double division(double x, double y)
{
	return x/y;
}


// Driver code
int main(int argc, char** argv)
{
	mat A(2,2, fill::zeros);
	cx_mat eigvec;
	cx_vec eigval;

	mat I(2,2,fill::eye);
	// We create symmetric matrix A from quadratic form Q
	int N = 2;
	float matrixA[N][N] = {};
	
	matrixA[0][0] = 5;
	matrixA[0][1] = halving(division(4,1));
	matrixA[1][0] = matrixA[0][1];
	matrixA[1][1] = 5;
	
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
	
	if (det(P) < 0)
	{
		P.col(0) = v2;
		P.col(1) = v1;
	}
	else 
	{
		P.col(0) = v1;
		P.col(1) = v2;
	}
	cout <<"Matrix P (which orthogonally diagonalizes A):" << "\n" << P <<endl;
	cout <<"det(P):" << "\n" << det(P) <<endl;
	cout <<"Matrix P^{T} * A * P:" << "\n" << D <<endl;

	Symbolic y1("y1"), y2("y2");

	Symbolic yt = ( ( y1), (y2)  );
	Symbolic y =yt.transpose();

	float d11 = matrixD[0][0]; 
	float d22 = matrixD[1][1]; 
	float d12 = lround(matrixD[0][1]); 
	
	Symbolic MatrixD = (  (Symbolic(d11), Symbolic(d12) ),
				( Symbolic(d12), Symbolic(d22) ) );
	
	cout << "y = " << y << endl; 
	cout << "y^{T} = " << yt << endl; 
	cout << "D = " << MatrixD << endl; 
	cout << "y^{T} * D * y = " << yt*MatrixD*y << endl; 

	return 0;
}