// g++ -o result main.cpp -larmadillo -lsymbolicc++
// Merci beaucoup Freya..

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>
#include "symbolicc++.h"

using namespace std;
using namespace arma;

#define R 4 // number of rows
#define C 6 // number of columns

// Driver code
int main(int argc, char** argv)
{
	arma::mat A(R,C,fill::zeros); //declare matrix A with size of R X C all have 0 entries with Armadillo.
	A.load("matrixA.txt"); // load matrixA.txt with Armadillo
	
	// Optional: Armadillo' computation
	cout << endl;
	cout << "****************Armadillo Computation of Matrix A****************" << endl;
	cout << endl;
	
	cout <<"Rank of matrix A :" << arma::rank(A) << endl;	
	cout << endl;

	cout <<"Nullity of matrix A :" << A.n_cols - arma::rank(A) << endl;
	cout << endl;

	arma::mat nullA(R,C,fill::zeros);
	nullA = arma::null(A);
	cout <<"Orthonormal basis of the null space of matrix A :\n" << nullA << endl;	
	cout << endl;
	
	arma::vec V1(C,1,fill::zeros);
	arma::vec V2(C,1,fill::zeros);
	arma::vec V3(C,1,fill::zeros);
	V1 = {-3,1,0,0,0,0} ; // extract the first column of A as vector V1
	V2 = {-4,0,-2,1,0,0} ; // extract the second column of A as vector V2
	V3 = {2,0,0,0,1,0} ; // extract the third column of A as vector V3

	cout <<"Normalize v1 from Armadillo : \n" << nullA.col(0) << endl;	
	cout <<"Normalize v2 from Armadillo : \n" << nullA.col(1) << endl;	
	cout <<"Normalize v3 from Armadillo : \n" << nullA.col(2) << endl;	
	
	cout <<"v1 from manual computation:\n " << V1 << endl;	
	cout <<"Norm of v1 : " << norm(V1) << endl;	
	cout <<"Normalize v1 manual computation: \n" << V1/norm(V1)<< endl;	
	cout << endl;

	cout <<"v2 from manual computation:\n " << V2 << endl;	
	cout <<"Norm of v2 : " << norm(V2) << endl;	
	cout <<"Normalize v2 manual computation: \n" << V2/norm(V2)<< endl;	
	cout << endl;

	cout <<"v3 from manual computation:\n " << V3 << endl;	
	cout <<"Norm of v3 : " << norm(V3) << endl;	
	cout <<"Normalize v3 manual computation: \n" << V3/norm(V3)<< endl;	
	cout << endl;

	cout <<"Orthonormal basis of the range space of matrix A :\n" << arma::orth(A) << endl;	
	cout << endl;
}