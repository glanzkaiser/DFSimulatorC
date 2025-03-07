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
	
	return 0;
}