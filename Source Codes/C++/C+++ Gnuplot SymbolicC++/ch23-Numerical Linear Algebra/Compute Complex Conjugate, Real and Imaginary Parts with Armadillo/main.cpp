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
	mat Areal;
	mat Acomplex;
	vec vreal;
	vec vcomplex;
	Areal.load("matrixAreal.txt");
	Acomplex.load("matrixAcomplex.txt");
	vreal.load("vectorvreal.txt");
	vcomplex.load("vectorvcomplex.txt");
	cx_mat A(Areal, Acomplex); // To directly construct a complex matrix out of two real matrices
	cx_mat complexconjugateA(Areal, -Acomplex);
	cx_mat eigvec;
	cx_vec eigval;
	cx_vec v(vreal,vcomplex);

	mat I(2,2,fill::eye);
	cout <<"Matrix A:" << "\n" << A <<endl;
	cout <<"Re(A):" << "\n" << real(A) <<endl;
	cout <<"Im(A):" << "\n" << imag(A) <<endl;
	cout <<"Complex conjugate of A:" << "\n" << complexconjugateA <<endl;
	//cout <<"Complex conjugate of A:" << "\n" << (A.t()).st() <<endl;
	cout <<"det(A):" << "\n" << det(A) <<endl;
	cout << endl;

	eig_gen(eigval, eigvec, A); // Eigen decomposition of dense general square matrix

	cout << "Eigenvalues:" << endl;

	int n = 2;
	for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}

	cout << endl;
	cout <<"Vector v:" << "\n" << v <<endl;
	cout <<"Re(v):" << "\n" << real(v) <<endl;
	cout <<"Im(v):" << "\n" << imag(v) <<endl;
	cout <<"Complex conjugate of v:" << "\n" << (v.t()).st() <<endl;
	
	return 0;
}