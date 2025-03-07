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
	mat A;
	A.load("matrixA.txt");
	cx_mat eigvec;
	cx_vec eigval;

	mat AtA = (A.t())*A;
	cout <<"Matrix A:" << "\n" << A <<endl;
	cout <<"A^{T} * A:" << "\n" << AtA <<endl;
	eig_gen(eigval, eigvec, AtA); // Eigen decomposition of dense general square matrix
	
	int n = AtA.n_cols; // number of dimension for A^{T}A
	for (int i = 1; i <= n; i++) 
	{
		cout << "\nλ_" << i << " = " <<real(eigval[i-1]) << endl;
		cout << "sigma_" << i << " = " <<sqrt(real(eigval[i-1])) << endl;
	}
	for (int i = 1; i <= n; i++) 
	{
		cout << "\nv_" << i << " = \n" << real(eigvec.col(i-1)) << endl;
	}
	for (int i = 1; i <= n; i++) 
	{
		cout << "\nu_" << i << " = \n" <<(1/real(eigval[i-1]))*A*real(eigvec.col(i-1)) << endl;
	}

	vec u1 = (1/sqrt(real(eigval[0])))*A*real(eigvec.col(0));
	vec u2 = (1/sqrt(real(eigval[1])))*A*real(eigvec.col(1));
	
	int N = u1.n_rows;
	
	cout <<"Singular Value Decomposition of matrix A with Armadillo\n" <<endl;	
	mat U;
	vec s;
	mat V;
	
	svd(U,s,V,A);

	cout <<"U:" << "\n" << U <<endl;	
	cout <<"s:" << "\n" << s <<endl;	
	cout <<"V:" << "\n" << V <<endl;	
	cout <<"V^{T}:" << "\n" << V.t() <<endl;	

	mat Z(N,n,fill::zeros);
	Z(0) = s(0);
	Z(0+N+1) = s(1);
	cout <<"Z:" << "\n" << Z <<endl;	
	
	mat A_SVD = U*Z*V.t();
	A_SVD(0) = lround(A_SVD(0));
	A_SVD(1) = lround(A_SVD(1));
	A_SVD(2) = lround(A_SVD(2));
	A_SVD(0+N) = lround(A_SVD(0+N));
	A_SVD(1+N) = lround(A_SVD(1+N));
	A_SVD(2+N) = lround(A_SVD(2+N));

	cout <<"U * Z * V^{T}:" << "\n" << A_SVD <<endl;	
	
	return 0;
}