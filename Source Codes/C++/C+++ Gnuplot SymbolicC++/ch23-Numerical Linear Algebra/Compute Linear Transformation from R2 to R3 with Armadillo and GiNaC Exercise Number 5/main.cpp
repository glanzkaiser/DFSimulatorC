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

// Linear transformation T: R^2 -> R^3
// Driver code
int main(int argc, char** argv)
{
	// Armadillo codes starts here
	cout << " ******************************************************************** " << endl;
	cout << " **************************Armadillo Codes*************************** " << endl;
	cout << " ******************************************************************** " << endl;
	mat matrixT;
	matrixT.load("matrixT.txt");
	// column vectors are treated like a matrix with one column, the function is 'vec'
	vec u1 = { 1, 2 };
	vec u2 =	{ 2, -1 };
	vec v1 = { 1, 1, 1 };
	vec v2 =	{ 2, 2, 0 };
	vec v3 = { 3, 0, 0 };

	mat matrix_Tu1 = matrixT*u1 ;
	mat matrix_Tu2 = matrixT*u2 ;
 	mat B(3,3,fill::zeros);
	B.col(0) = v1;
	B.col(1) = v2;
	B.col(2) = v3;
	
	cout << "Old basis B = {u1, u2}"<< endl;
	cout << "u1: \n" << u1 << endl;
	cout << "u2: \n" << u2 << endl;
	cout << "New basis B' = {v1, v2, v3}"<< endl;
	cout << "v1: \n" << v1 << endl;
	cout << "v2: \n" << v2 << endl;
	cout << "v3: \n" << v3 << endl;
	cout << "T(u1): \n" << matrix_Tu1 << endl;
	cout << "T(u2): \n" << matrix_Tu2 << endl;

	// Compute [T(u1)]_{B'} and [T(u2)]_{B'}
	mat Tu1_newBasis;
	mat Tu2_newBasis;
	Tu1_newBasis = solve(B,matrix_Tu1,solve_opts::no_approx); 
	Tu2_newBasis = solve(B,matrix_Tu2,solve_opts::no_approx); 
	
	cout <<"Matrix from new basis B':" << "\n" << B <<endl;
	cout <<"Expressing T(u1) and T(u2) as the linear combinations of v1, v2, and v3:" <<endl;
	cout <<"[T(u1)]_{B'}:" << "\n" << Tu1_newBasis <<endl;	
	cout <<"[T(u2)]_{B'}:" << "\n" << Tu2_newBasis <<endl;

	mat TBnewBold(3,2,fill::zeros);
	TBnewBold.col(0) = Tu1_newBasis ;
	TBnewBold.col(1) = Tu2_newBasis ;
	matrixT.print("[T]:\n");
	TBnewBold.print("[T]_{B',B}:\n");
	
	cout <<"\n B' * Tu1:" << "\n" << B*Tu1_newBasis <<endl;
	cout <<"\n B' * Tu2:" << "\n" << B*Tu2_newBasis <<endl;
	
	return 0;
}