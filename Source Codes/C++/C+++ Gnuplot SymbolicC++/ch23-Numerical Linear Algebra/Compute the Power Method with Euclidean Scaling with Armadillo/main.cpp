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
	mat x0;
	x0.load("vectorx0.txt");
	cx_mat eigvec;
	cx_vec eigval;

	mat I(2,2,fill::eye);
	cout <<"Matrix A:" << "\n" << A <<endl;
	cout <<"Vector x_{0}:" << "\n" << x0 <<endl;
	
	eig_gen(eigval, eigvec, A); // Eigen decomposition of dense general square matrix

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
	cout << "λ_max / Maximum value of Eigenvalue:" << max(real(eigval)) << endl;
	
	cout << "\nThe Power Method with Euclidean Scaling Computation:" << endl;
	float err = 10;
	vec x;
	x = x0;
	float λ_approx;
	mat Ax(2,2,fill::zeros);
	mat Axnew(2,2,fill::zeros);
	int N = 10;
	int i = 1;
	
	// With while loop
	while (err > 10e-7)
	{
		Ax = A*x;
		cout <<"\nAx_{"<< i-1 <<"}:" << "\n" << Ax <<endl; 

		x = Ax/norm(Ax);
		cout <<"x_{"<< i <<"}:" << "\n" << x <<endl; 

		Axnew = A*x;
		λ_approx = cdot(Axnew,x);		
		cout <<"λ^("<< i <<") = " << λ_approx <<endl; 
		
		err = max(real(eigval)) - λ_approx;
		cout <<"error : λ_max - λ^(" << i <<") = " << "" << err <<endl; 
		i = i+1;
	}
	/*
	// With for loop
	for (int i = 1; i <=N; i++)
	{
		Ax = A*x;
		cout <<"\nAx_{"<< i-1 <<"}:" << "\n" << Ax <<endl; 

		x = Ax/norm(Ax);
		cout <<"x_{"<< i <<"}:" << "\n" << x <<endl; 

		Axnew = A*x;
		λ_approx = cdot(Axnew,x);		
		cout <<"λ^("<< i <<") = " << λ_approx <<endl; 
		
		err = max(real(eigval)) - λ_approx;
		
		if (err <= 10e-7)
		{
			break;		
		}
	}
	*/
	return 0;
}