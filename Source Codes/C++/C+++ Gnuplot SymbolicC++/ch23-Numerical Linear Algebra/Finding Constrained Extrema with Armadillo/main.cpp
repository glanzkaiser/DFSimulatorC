// g++ -o result main.cpp
// Merci beaucoup Freya.. et Sentinel

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>

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
	matrixA[0][1] = halving(4);
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
	
	if ( real(eigval[0]) < real(eigval[1]))
	{
		cout <<"Constrained maximum: z = " << real(eigval[1]) <<endl;
		cout <<"at (x,y) = " << "\n" << real(eigvec.col(1)) << endl;
		cout <<"Constrained minimum: z = " << real(eigval[0]) <<endl;
		cout <<"at (x,y) = " << "\n" << real(eigvec.col(0)) << endl;
	}
	else
	{
		cout <<"Constrained maximum: z = " << real(eigval[0]) <<endl;
		cout <<"at (x,y) = " << "\n" << real(eigvec.col(0)) << endl;
		cout <<"Constrained minimum: z = " << real(eigval[1]) <<endl;
		cout <<"at (x,y) = " << "\n" << real(eigvec.col(1)) << endl;
	}
	
	return 0;
}