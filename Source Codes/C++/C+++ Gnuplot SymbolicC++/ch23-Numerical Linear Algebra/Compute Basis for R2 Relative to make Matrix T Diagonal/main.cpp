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
	// Define the standard basis vector B = {u1, u2}
	vec u1 = {1, 0};
	vec u2 = {0, 1};
	mat TB(2,2,fill::zeros);
	TB.col(0) = {3*u1(0) - 2*u1(1), -u1(0) + 4*u1(1)};
	TB.col(1) = {3*u2(0) - 2*u2(1), -u2(0) + 4*u2(1)};
	cx_mat eigvec;
	cx_vec eigval;

	
	mat I(2,2,fill::eye);
	cout <<"Matrix [T]_{B}:" << "\n" << TB <<endl;
	
	eig_gen(eigval, eigvec, TB); // Eigen decomposition of dense general square matrix

	cout << "Eigenvalues:" << endl;

	int n = 2;
	for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}
	
	cout << endl;
	
	cout << "Eigenvectors:" << endl;
	for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] :\n " << real(eigvec.col(i-1)) << endl;
	}

	cout << "det([T]_{B}) = " << det(TB) << endl;
	cout << "rank([T]_{B}) = " << arma::rank(TB) << endl;

	mat P(2,2,fill::zeros);
	P.col(0) = real(eigvec.col(0));
	P.col(1) = real(eigvec.col(1));
	mat T_Bnew;
	T_Bnew = arma::inv(P)*TB*P;
		
	T_Bnew(0) = lround(T_Bnew(0));
	T_Bnew(1) = lround(T_Bnew(1));
	T_Bnew(2) = lround(T_Bnew(2));
	T_Bnew(3) = lround(T_Bnew(3));
	
	cout << "\nP = \n" << P << endl;
	cout << "P^{-1} = \n" << inv(P) << endl;
	cout << "P^{-1} * [T]_{B} * P = \n" << T_Bnew << endl;
	
	return 0;
}