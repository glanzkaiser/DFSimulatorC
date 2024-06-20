// g++ -o result main.cpp
// Merci beaucoup Freya..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>
#include <ginac/ginac.h>

using namespace std;
using namespace arma;
using namespace GiNaC;

// The second order differential equaiton is: y'' - 7y' + 6y = 0
// Substitutions: y1 = y, y2 = y'
// The system becomes
// y1' = y2
// y2' = -6y1 + 7 y2 
//
// Driver code
int main(int argc, char** argv)
{
	mat A;
	A.load("matrixA.txt");
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
	
	mat A1 = I*real(eigval[0]) - A;
	mat A2 = I*real(eigval[1]) - A;
	
	cout << endl;
	cout << "Eigenspaces for λ_1: " <<  n - arma::rank(A1) << endl;
	cout << "Eigenspaces for λ_2: " <<  n - arma::rank(A2) << endl;
	cout << endl;
	
	cout << "Eigenvectors:" << endl;
	for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] :\n " << real(eigvec.col(i-1)) << endl;
	}

	mat P(2,2,fill::eye);
	mat PI(2,2,fill::eye);
	P = real(eigvec);
	PI = inv(P);

	mat D(2,2,fill::eye);
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
	cout <<"Matrix P^{-1}AP:" << "\n" << D <<endl;

	// GiNaC computation starts here for symbolic computation
	Digits = 5; // define maximum decimal digits
	symbol x("x") ;
	symbol u1("u1"), y2("u2");
	symbol c1("c1"), c2("c2") ;
	
	ex fx1 = c1*exp(D(0,0)*x) ;
	ex fx2 = c2*exp(D(1,1)*x) ;
	cout << endl;

	cout << "u1 = " << fx1 <<endl;
	cout << "u2 = " << fx2 <<endl;
	cout << endl;

	matrix P_ginac = { { P(0,0), P(0,1) }, { P(1,0), P(1,1)} };
	matrix u = { { fx1}, { fx2} };
	
	cout << "\n P = " << P_ginac << endl;
	
	matrix Pu = P_ginac.mul(u);
	
	cout << "\n y1 = " << Pu(0,0) << endl;
	cout << "\n y2 = " << Pu(1,0) << endl;
	
	ex fx1_final = Pu(0,0) ;
	ex fx2_final = Pu(1,0) ;
	
	cout << endl;
	cout << "The second order differential equation is :" << endl;	
	cout << "y'' - 7' + 6y = 0 " <<endl;
	cout << "y2' - 7y2 + 6y1 = 0 " <<endl;
	
	cout << "The general solution for the second order differential equation is :" << endl;	
	cout << (-6*fx1_final + 7*fx2_final ) << -7*fx2_final << + 6*fx1_final<< "=" ;	
	cout <<  (-6*fx1_final + 7*fx2_final ) -7*fx2_final + 6*fx1_final <<endl;
	
	return 0;
}