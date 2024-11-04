// g++ -o result main.cpp -larmadillo
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
	mat Real;
	mat Complex;
	Real.load("matrixReal.txt");
	Complex.load("matrixComplex.txt");
	cx_mat A(Real,Complex);
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
	cx_mat A1 = I*real(eigval[0]) - A;
	cx_mat A2 = I*real(eigval[1]) - A;

	cout << endl;
	cout << "Eigenspaces for λ_1: " <<  n - arma::rank(A1) << endl;
	cout << "Eigenspaces for λ_2: " <<  n - arma::rank(A2) << endl;
	cout << endl;
	
	cout << "Orthonormal Eigenvectors:" << endl;
	for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] :\n " <<eigvec.col(i-1) << endl;
	}

	cout << "det(A) = " << det(A) << endl;
	cout << "rank(A) = " << arma::rank(A) << endl;

	// show eigenvectors in matrix form 
	// cout <<"Eigenvectors:" << "\n" << eigvec <<endl; 
	// cout <<"Eigenvectors:" << "\n" << real(eigvec) <<endl; 
	return 0;
}