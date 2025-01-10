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
	vec u1 = { 3, 1 };
	vec u2 =	{ 5, 2 };
	vec v1 = { 1, 0, -1 };
	vec v2 =	{ -1, 2, 2 };
	vec v3 = { 0, 1, 2 };

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
	Tu1_newBasis = solve(B,matrix_Tu1,solve_opts::force_approx); 
	Tu2_newBasis = solve(B,matrix_Tu2,solve_opts::force_approx); 
	// Rounding the entries to the nearest integer
	Tu1_newBasis[0] = lround(Tu1_newBasis[0]);
	Tu1_newBasis[1] = lround(Tu1_newBasis[1]);
	Tu1_newBasis[2] = lround(Tu1_newBasis[2]);
	Tu2_newBasis[0] = lround(Tu2_newBasis[0]);
	Tu2_newBasis[1] = lround(Tu2_newBasis[1]);
	Tu2_newBasis[2] = lround(Tu2_newBasis[2]);

	cout <<"Matrix from new basis B':" << "\n" << B <<endl;
	cout <<"Expressing T(u1) and T(u2) as the linear combinations of v1, v2, and v3:" <<endl;
	cout <<"[T(u1)]_{B'}:" << "\n" << Tu1_newBasis <<endl;	
	cout <<"[T(u2)]_{B'}:" << "\n" << Tu2_newBasis <<endl;

	mat TBnewBold(3,2,fill::zeros);
	TBnewBold.col(0) = Tu1_newBasis ;
	TBnewBold.col(1) = Tu2_newBasis ;
	matrixT.print("[T]:\n");
	TBnewBold.print("[T]_{B',B}:\n");
	
	// GiNac codes starts here
	cout << " ******************************************************************** " << endl;
	cout << " ****************************GiNaC Codes***************************** " << endl;
	cout << " ******************************************************************** " << endl;
	
	Digits = 5; // define maximum decimal digits
	symbol x("x"), xpow2("x^2"), a("a"), b("b"), x1("x1"), x2("x2");
	
	matrix T = {{0,1},{-5,13},{-7,16}};

	// Create vector x=(x1, x2)
	matrix vectorx(2,1);
	vectorx(0,0) = x1;
	vectorx(1,0) = x2;

	cout << "\n [T] = " << T << endl;
	cout << "\n [T] * x = " << (T*vectorx).evalm() << endl;
	ex Tx = (T*vectorx).evalm() ;
	matrix X = {{x1}, {x2}};
	cout << "\n [T] * x = " << (T*X).evalm() << endl;

	// Create vector T(u1), with u1 = (3,1) and u2 = (5,2)
	ex Tu1 = subs(subs( (T*X).evalm(), x1==3), x2==1);
	ex Tu2 = subs(subs( (T*X).evalm(), x1==5), x2==2);
	cout << "\n T(u1) = " << Tu1 << endl;
	cout << "\n T(u2) = " << Tu2 << endl;
	
	// Construct matrix [T]_{B,B'}
	matrix TBBnew(3,2);
	TBBnew(0,0) = Tu1[0];
	TBBnew(0,1) = Tu2[0];
	TBBnew(1,0) = Tu1[1];
	TBBnew(1,1) = Tu2[1];
	TBBnew(2,0) = Tu1[2];
	TBBnew(2,1) = Tu2[2];

	matrix xB(2,1);
	xB(0,0) = a;
	xB(1,0) = b;

	//cout << "\n [T]_{B , B'} = " << TBBnew << endl;
	
	return 0;
}