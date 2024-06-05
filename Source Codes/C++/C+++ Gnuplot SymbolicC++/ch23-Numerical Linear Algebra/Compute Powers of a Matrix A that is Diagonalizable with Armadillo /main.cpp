// g++ -o result main.cpp
// Merci beaucoup Freya..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>

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
	
	mat A1 = I*real(eigval[0]) - A;
	mat A2 = I*real(eigval[1]) - A;
	mat A3 = I*real(eigval[2]) - A;

	cout << endl;
	cout << "Eigenspaces for λ_1: " <<  n - arma::rank(A1) << endl;
	cout << "Eigenspaces for λ_2: " <<  n - arma::rank(A2) << endl;
	cout << "Eigenspaces for λ_3: " <<  n - arma::rank(A3) << endl;
	cout << endl;
	
	mat P(3,3,fill::eye);
	mat PI(3,3,fill::eye);
	mat D(3,3,fill::eye);
	P = real(eigvec);
	PI = inv(P);

	D = PI*A*P;
	
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++)
		{
			if (i !=j)
			{
			D(i,j) = 0;
			}
		}
	}

	cout <<"Matrix P:" << "\n" << P <<endl;
	cout <<"Matrix P^{-1}:" << "\n" << PI <<endl;
	cout <<"Matrix P^{-1}AP:" << "\n" << D <<endl;

	cout <<"Matrix A^{10} = P D^{10} P^{-1} :" << "\n" << P*(pow(D,10))*PI <<endl;
	cout <<"Matrix A^{10} manual way: " << "\n" << A*A*A*A*A*A*A*A*A*A<<endl; // using pow(A,10) gives wrong result
	
	return 0;
}