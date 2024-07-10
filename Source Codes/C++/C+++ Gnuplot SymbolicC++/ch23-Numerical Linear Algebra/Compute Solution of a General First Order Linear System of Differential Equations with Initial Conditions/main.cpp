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
	
	// Define the initial conditions y1(0) = ic1, y2(0) = ic2, y3(0) = ic3
	ex ic1 = 1 ;
	ex ic2 = 6 ;

	// List the equations and the variables needed to be solved
	lst equations = {fx1_final.subs(x==0) == ic1, fx2_final.subs(x==0) == ic2} ;
	lst variables = {c1, c2};

	cout << endl;
	cout << "Solving the differential equations with initial conditions " << endl;
	cout << "y1(0) = 1, y2(0) = 6 " << endl;
	cout << endl;
	
	//cout << "Solutions for c1 and c2 = " << lsolve(equations, variables) <<endl;
	
	ex c1_ans = lsolve(equations, variables)[0].rhs() ; // obtain the first variable c1 as the solution
	ex c2_ans = lsolve(equations, variables)[1].rhs() ;  // obtain the second variable c2 as the solution

	cout << "c1 = " << c1_ans <<endl;
	cout << "c2 = " << c2_ans <<endl;
	
	cout << endl;
	cout << "The general solution satisfying the initial conditions are" << endl;
	cout << endl;

	ex y1_sol = fx1_final.subs(lst{c1==c1_ans, c2 ==c2_ans});
	ex y2_sol = fx2_final.subs(lst{c1==c1_ans, c2 ==c2_ans});

	cout << "y1 = " << y1_sol <<endl;
	cout << "y2 = " << y2_sol <<endl;
	
	return 0;
}