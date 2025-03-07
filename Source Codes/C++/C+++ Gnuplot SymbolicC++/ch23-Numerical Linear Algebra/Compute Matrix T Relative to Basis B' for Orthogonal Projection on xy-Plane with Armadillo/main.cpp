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
	vec u1 = { 1, 0, 0 };
	vec u2 =	{ 0, 1, 0 };
	vec u3 =	{ 0, 0, 1 };
	vec v1 = { 1, 0, 0 };
	vec v2 =	{ 1, 1, 0 };
	vec v3 =	{ 1, 1, 1 };
	
	mat T;
	T.load("matrixT.txt");
	
	mat Tu1 = T*u1;
	mat Tu2 = T*u2;
	mat Tu3 = T*u3;
	
	cout <<"Matrix T:" << "\n" << T <<endl;
	cout <<"T(u1):" << "\n" << Tu1 <<endl;
	cout <<"T(u2):" << "\n" << Tu2 <<endl;
	cout <<"T(u3):" << "\n" << Tu3 <<endl;
	
	mat A(3,3,fill::zeros);
	A.col(0) = u1;
	A.col(1) = u2;
	A.col(2) = u3;
	mat V1;
	mat V2;
	mat V3;
	V1 = solve(A,v1,solve_opts::force_approx); 
	V2 = solve(A,v2,solve_opts::force_approx); 
	V3 = solve(A,v3,solve_opts::force_approx); 
	
	cout <<"Matrix B [u1 | u2 | u3]:" << "\n" << A <<endl;
	cout <<"v1_{B}:" << "\n" << V1 <<endl;	
	cout <<"v2_{B}:" << "\n" << V2 <<endl;	
	cout <<"v3_{B}:" << "\n" << V3 <<endl;	

	mat P(3,3,fill::zeros);
	P.col(0) = V1;
	P.col(1) = V2;
	P.col(2) = V3;
	cout <<"Transition matrix P:" << "\n" << P <<endl;
	cout <<"P^{-1}:" << "\n" << inv(P) <<endl;
	cout <<"[T]_{B'} = P^{-1} * [T]_{B} * P:" << "\n" << inv(P)*T*P <<endl;
	
	return 0;
}