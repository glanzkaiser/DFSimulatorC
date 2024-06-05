// g++ -o result main.cpp
// Merci beaucoup Freya..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>

using namespace std;
using namespace arma;

#define N 2 // Define the number of dimension

// Driver code
int main(int argc, char** argv)
{
	mat A;
	A.load("matrixA.txt");
	cx_mat eigvec;
	cx_vec eigval;

	mat I(2,2,fill::eye);
	// To be able to construct matrix C we need to know the eigenvalues of matrix A
	//  then choose one with form of λ = a - bi, so we can input the value for a and b into matrix C
	// e.g. for  λ = i, we will have a = 0 and b = -1.
	// e.g. for  λ = -i, we will have a = 0 and b = 1.
	
	float a = 0;
	float b = 1;
	float matrixC[N][N] = {};
	matrixC[0][0] = a;
	matrixC[0][1] = -b;
	matrixC[1][0] = b;
	matrixC[1][1] = a;

	cout <<"Matrix A:" << "\n" << A <<endl;
	
	eig_gen(eigval, eigvec, A); // Eigen decomposition of dense general square matrix

	cout << "Eigenvalues:" << endl;

	int n = 2;
	for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}
	
	cout << endl;
	cout <<"Matrix λ_1I - A:" << "\n" << I*eigval[0] - A <<endl;
	cout <<"Matrix λ_2I - A:" << "\n" << I*eigval[1] - A <<endl;
	mat A1 = I*real(eigval[0]) - A;
	mat A2 = I*real(eigval[1]) - A;
	cout << endl;
	
	cout << "Re(x):" << endl;
	for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] :\n " << real(eigvec.col(i-1)) << endl;
	}

	cout << "Im(x):" << endl;
	for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] :\n " << imag(eigvec.col(i-1)) << endl;
	}

	arma::mat ArmaC(N,N,fill::zeros); 
	
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaC[i+j*N] = matrixC[i][j] ;		
		}			
	}
	
	cout <<"For λ = -i" <<endl;
	cout << endl;
	cout <<"Matrix C:" << "\n" << ArmaC <<endl;

	// For λ = -i, the second eigenvalue
	arma::mat P(N,N,fill::zeros); 
	P.col(0) = real(eigvec.col(1)) ; // make Re(x) the first column for matrix P 
	P.col(1) = imag(eigvec.col(1)) ; // make Im(x) the second column for matrix P 
	cout <<"Matrix P:" << "\n" << P <<endl;
	
	arma::mat P_inv(N,N,fill::zeros); 
	P_inv = inv(P);
	cout <<"Matrix P^{-1}:" << "\n" << P_inv <<endl;
	
	cout <<"Matrix P * C * P^{-1}:" << "\n" << P*ArmaC*P_inv <<endl;
	
	return 0;
}