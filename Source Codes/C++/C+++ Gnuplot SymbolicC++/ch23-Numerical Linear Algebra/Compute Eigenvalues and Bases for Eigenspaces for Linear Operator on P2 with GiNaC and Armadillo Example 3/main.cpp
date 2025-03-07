// g++ -o result main.cpp -larmadillo -lginac -lcln
// Merci beaucoup Freya.. et Sentinel..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <ginac/ginac.h>
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;
using namespace GiNaC;

// Linear operator T: P_2 -> P_2
// Driver code
int main(int argc, char** argv)
{
	// Armadillo and GiNac codes starts here
	cout << " ******************************************************************** " << endl;
	cout << " *********************Armadillo & GiNaC Codes*********************** " << endl;
	cout << " ******************************************************************** " << endl;
	
	Digits = 5; // define maximum decimal digits
	symbol x("x"),  a("a"), b("b"), c("c");
	
	ex Tx = -2*c + (a+2*b+c)*x + (a+3*c)*pow(x,2);
	
	cout << "\n T(x) = " << Tx << endl;
	
	for (int i = Tx.ldegree(x); i <= Tx.degree(x); ++i)
	{
		cout << " The x^" << i << "-coefficient is " << Tx.coeff(x,i) << endl;
	}

	// To obtain the coefficient of a,b,c for x^0, x^1 and x^2.
	ex Tx0 = Tx.coeff(x,0);
	ex Tx1 = Tx.coeff(x,1);
	ex Tx2 = Tx.coeff(x,2);

	/*
	cout << "\n x^0 coeff a = " << Tx0.coeff(a,1) <<endl;
	cout << "\n x^0 coeff b = " << Tx0.coeff(b,1) <<endl;
	cout << "\n x^0 coeff c = " << Tx0.coeff(c,1) <<endl;
	
	cout << "\n x^1 coeff a = " << Tx1.coeff(a,1) <<endl;
	cout << "\n x^1 coeff b = " << Tx1.coeff(b,1) <<endl;
	cout << "\n x^1 coeff c = " << Tx1.coeff(c,1) <<endl;
	
	cout << "\n x^2 coeff a = " << Tx2.coeff(a,1)<<endl;
	cout << "\n x^2 coeff b = " << Tx2.coeff(b,1)<<endl;
	cout << "\n x^2 coeff c = " << Tx2.coeff(c,1)<<endl;
	*/

	// Convert the expression to double
	double tb11 = ex_to<numeric>(Tx0.coeff(a,1)).to_double();
	double tb12 = ex_to<numeric>(Tx0.coeff(b,1)).to_double();
	double tb13 = ex_to<numeric>(Tx0.coeff(c,1)).to_double();
	double tb21 = ex_to<numeric>(Tx1.coeff(a,1)).to_double();
	double tb22 = ex_to<numeric>(Tx1.coeff(b,1)).to_double();
	double tb23 = ex_to<numeric>(Tx1.coeff(c,1)).to_double();
	double tb31 = ex_to<numeric>(Tx2.coeff(a,1)).to_double();
	double tb32 = ex_to<numeric>(Tx2.coeff(b,1)).to_double();
	double tb33 = ex_to<numeric>(Tx2.coeff(c,1)).to_double();

	// Create matrix [T]_{B} with Armadillo	
	vec tb1 = {tb11, tb21, tb31};
	vec tb2 = {tb12, tb22, tb32};
	vec tb3 = {tb13, tb23, tb33};
	arma::mat TB(3,3,fill::zeros);
	TB.col(0) = tb1;
	TB.col(1) = tb2;
	TB.col(2) = tb3;
	
	cout << "\n [T]_{B} = \n" << TB << endl;

	// Compute the eigenvalues and eigenvectors with Armadillo
	cx_mat eigvec;
	cx_vec eigval;
	eig_gen(eigval, eigvec, TB); // Eigen decomposition of dense general square matrix
	cout << "Eigenvalues:" << endl;

	int n = 3;
	for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}
	
	cout << endl;
	cout << "Eigenvectors / Basis for the eigenspace of [T]_{B} correspond to certain λ:" << endl;
	for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] :\n " << real(eigvec.col(i-1)) << endl;
	}
	cout << "(The eigenspace of [T]_{B} corresponding to λ has the basis as the eigenvector corresponding to that λ)" << endl;
	
	vec u1 = real(eigvec.col(0));
	vec u2 = real(eigvec.col(1));
	vec u3 = real(eigvec.col(2));

	cout << "\n u_{1} = \n" << u1 << endl;
	cout << "\n u_{2} = \n" << u2 << endl;
	cout << "\n u_{3} = \n" << u3 << endl;

	// Construct the basis B' = { p_{1}, p_{2}, p_{3} } with GiNaC
	ex p1 = 1*u1(0) + x*u1(1) + pow(x,2)*u1(2);
	ex p2 = 1*u2(0) + x*u2(1) + pow(x,2)*u2(2);
	ex p3 = 1*u3(0) + x*u3(1) + pow(x,2)*u3(2);

	cout << "\n p_{1} = " << p1 << endl;
	cout << "\n p_{2} = " << p2 << endl;
	cout << "\n p_{3} = " << p3 << endl;

	cout << "\n The eigenspace of T corresponding to λ = " << real(eigval[0]) << " has the basis " << endl;
	cout << "\n p_{1} = " << p1 << endl;
	cout << "\n p_{3} = " << p3 << endl;
	
	cout << "\n The eigenspace of T corresponding to λ = " << real(eigval[1]) << " has the basis " << endl;
	cout << "\n p_{2} = " << p2 << endl;
	
	return 0;
}