// g++ -o result main.cpp -larmadillo -lginac -lcln
// Merci beaucoup Freya..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>
#include <ginac/ginac.h>

using namespace std;
using namespace arma;
using namespace GiNaC;

// The third order differential equation is: y''' - 6y'' + 11y' - 6y = 0
// Substitutions: y1 = y, y2 = y', y3 = y''
// The system becomes
// y1' = y2
// y2' = y3
// y3' = 6y1 - 11y2 + 6y3
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
	
	cout << "Eigenvectors:" << endl;
	for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] :\n " << real(eigvec.col(i-1)) << endl;
	}

	mat P(3,3,fill::eye);
	mat PI(3,3,fill::eye);
	P = real(eigvec);
	PI = inv(P);

	mat D(3,3,fill::eye);
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
	symbol u1("u1"), u2("u2"), u3("u3");
	symbol c1("c1"), c2("c2"), c3("c3") ;
	
	ex fx1 = c1*exp(D(0,0)*x) ;
	ex fx2 = c2*exp(D(1,1)*x) ;
	ex fx3 = c3*exp(D(2,2)*x) ;
	cout << endl;

	cout << "u1 = " << fx1 <<endl;
	cout << "u2 = " << fx2 <<endl;
	cout << "u3 = " << fx3 <<endl;
	cout << endl;

	matrix P_ginac = { { P(0,0), P(0,1), P(0,2) }, { P(1,0), P(1,1), P(1,2)}, { P(2,0), P(2,1), P(2,2)} };
	matrix u = { { fx1}, { fx2}, {fx3} };
	
	cout << "\n P = " << P_ginac << endl;
	
	matrix Pu = P_ginac.mul(u);
	
	cout << "\n y1 = " << Pu(0,0) << endl;
	cout << "\n y2 = " << Pu(1,0) << endl;
	cout << "\n y2 = " << Pu(2,0) << endl;
	
	ex fx1_final = Pu(0,0) ;
	ex fx2_final = Pu(1,0) ;
	ex fx3_final = Pu(2,0) ;
	
	cout << endl;
	cout << "The third order differential equation is :" << endl;	
	cout << "y''' - 6y'' + 11y' - 6y = 0" <<endl;
	cout << "y3' - 6y3 + 11y2 - 6y1 = 0 " <<endl;
	
	cout << "The general solution for the second order differential equation is :" << endl;	
	cout << (6*fx1_final - 11*fx2_final + 6*fx3_final ) << -6*fx3_final << + 11*fx2_final << -6*fx1_final << "=" ;	
	cout <<  (6*fx1_final - 11*fx2_final + 6*fx3_final ) -6*fx3_final + 11*fx2_final -6*fx1_final <<endl;
	
	return 0;
}