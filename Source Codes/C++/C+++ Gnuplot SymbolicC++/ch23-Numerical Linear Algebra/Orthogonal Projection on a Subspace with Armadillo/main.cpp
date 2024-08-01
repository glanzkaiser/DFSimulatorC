// g++ -o result main.cpp -larmadillo
// Merci beaucoup Freya, Sentinel..

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

#define R 4
#define C 3

// Driver code
int main(int argc, char** argv)
{
	arma::mat U(R,1,fill::zeros);
	arma::mat U1(R,1,fill::zeros);
	arma::mat U2(R,1,fill::zeros);
	arma::mat U3(R,1,fill::zeros);
	arma::mat A(R,C,fill::zeros);
	U.load("vectorU.txt");
	U1.load("vectorU1.txt");
	U2.load("vectorU2.txt");
	U3.load("vectorU3.txt");	

	A.col(0) = U1;
	A.col(1) = U2;
	A.col(2) = U3;

	arma::mat A_transpose(C,R,fill::zeros);
	A_transpose = A.t();

	arma::mat X(C,1,fill::zeros);
	X = solve(A_transpose*A,A_transpose*U,solve_opts::force_approx); 
	
	cout <<"Matrix A :" << "\n" << A <<endl;
	cout <<"Vector u :" << "\n" << U <<endl;
	cout <<"Vector u1 :" << "\n" << U1 <<endl;
	cout <<"Vector u2 :" << "\n" << U2 <<endl;
	cout <<"Vector u3 :" << "\n" << U3 <<endl;
	
	cout <<"Matrix A^{T}:" << "\n" << A_transpose <<endl;
	
	cout <<"Matrix A^{T} * A:" << "\n" << A_transpose*A <<endl;
	cout <<"Matrix A^{T} * u:" << "\n" << A_transpose*U <<endl;

	cout <<"\n Solution of the normal system A^{T} *A * x = A^{T} * u:" <<endl;
	cout <<"x: " << "\n" << X <<endl;
	
	cout <<"*************************************" <<endl;
	cout <<"*************************************" <<endl;
	cout <<"The least squares solution of Ax = u: " <<endl;
	cout <<"proj_{W} u = Ax : " << "\n" << A*X <<endl;
	
}