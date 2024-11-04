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
		cout << "p[λ_" << i << "] :\n " << eigvec.col(i-1) << endl;
	}

	//cout << "det(A) = " << det(A) << endl;
	//cout << "rank(A) = " << arma::rank(A) << endl;

	cout << "\np1 . p2 = " << dot(eigvec.col(0),eigvec.col(1).t()) << endl;  

	cx_mat P(3,3,fill::eye);
	cx_mat Pt(3,3,fill::eye);
	P = eigvec;
	Pt = P.t();

	cx_mat D(3,3,fill::eye);
	D = Pt*A*P;
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

	cout <<"\nMatrix P:" << "\n" << P <<endl;
	cout <<"Matrix P*:" << "\n" << Pt <<endl;
	cout <<"Matrix P*AP:" << "\n" << D <<endl;

	mat RealP;
	mat ComplexP;
	RealP.load("matrixRealP.txt");
	ComplexP.load("matrixComplexP.txt");
	cx_mat P2(RealP,ComplexP);
	cout <<"\nMatrix P2:" << "\n" << P2 <<endl;
	cout <<"Matrix P2*:" << "\n" << P2.t() <<endl;
	cout <<"Matrix P2*AP2:" << "\n" << (P2.t())*A*P2 <<endl;

	return 0;
}