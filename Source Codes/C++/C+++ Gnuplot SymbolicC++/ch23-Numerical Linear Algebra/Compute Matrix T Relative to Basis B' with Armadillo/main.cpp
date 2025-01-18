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
	// column vectors are treated like a matrix with one column, the function is 'vec'
	vec u1 = { 1, 0 };
	vec u2 =	{ 0, 1 };
	vec v1 = { 1, -3 };
	vec v2 =	{ 3, 0 };
	
	mat T;
	T.load("matrixT.txt");
	
	mat Tu1 = T*u1;
	mat Tu2 = T*u2;
	
	cout <<"Matrix T:" << "\n" << T <<endl;
	cout <<"T(u1):" << "\n" << Tu1 <<endl;
	cout <<"T(u2):" << "\n" << Tu2 <<endl;
	
	mat A(2,2,fill::zeros);
	A.col(0) = u1;
	A.col(1) = u2;
	mat V1;
	mat V2;
	V1 = solve(A,v1,solve_opts::force_approx); 
	V2 = solve(A,v2,solve_opts::force_approx); 
	
	cout <<"Matrix B [u1 | u2]:" << "\n" << A <<endl;
	cout <<"v1_{B}:" << "\n" << V1 <<endl;	
	cout <<"v2_{B}:" << "\n" << V2 <<endl;	

	//cout << "det(T) = " << det(T) << endl;
	//cout << "rank(T) = " << arma::rank(T) << endl;

	mat P(2,2,fill::zeros);
	P.col(0) = V1;
	P.col(1) = V2;
	cout <<"Transition matrix P:" << "\n" << P <<endl;
	cout <<"P^{-1}:" << "\n" << inv(P) <<endl;
	cout <<"[T]_{B'} = P^{-1} * [T]_{B} * P:" << "\n" << inv(P)*T*P <<endl;
	
	return 0;
}