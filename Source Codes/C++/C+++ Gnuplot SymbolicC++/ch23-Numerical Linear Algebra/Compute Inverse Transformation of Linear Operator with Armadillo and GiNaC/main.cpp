// g++ -o result main.cpp -larmadillo
// Merci beaucoup Freya.. et Sentinel..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>
#include <ginac/ginac.h>

using namespace std;
using namespace arma;
using namespace GiNaC;

// Driver code
int main(int argc, char** argv)
{
	int N = 3;
	mat T;
	mat T_inv;	
	T.load("matrixT.txt");
	
	mat I(3,3,fill::eye);
	cout <<"[T]:" << "\n" << T <<endl;
	
	cout << "det(T) = " << det(T) << endl;
	cout << "rank(T) = " << arma::rank(T) << endl;

	T_inv = inv(T);
	cout << "\n[T]^{-1} =\n " << T_inv << endl;

	// GiNac codes starts here
	Digits = 5; // define maximum decimal digits
	symbol x1("x1"), x2("x2"), x3("x3");
	
	matrix T_invginac = { { T_inv[0], T_inv[0+N], T_inv[0+2*N] }, 
				{ T_inv[1], T_inv[1+N], T_inv[1+2*N]}, 
				{ T_inv[2], T_inv[2+N], T_inv[2+2*N]} };
	matrix X = {{x1}, {x2}, {x3}};

	cout << "\n [T]^{-1} (ginac) = " << T_invginac << endl;
	cout << "\n x = " << X << endl;
	
	ex Tinv_image = (T_invginac*X).evalm();
	cout << "\n [T]^{-1} * x = " << Tinv_image << endl;
	
	cout << "\n************************************************************"<< endl;
	cout << "\nIf we input (x1,x2,x3) with (1,2,3)"<< endl;
	cout << "then the inverse will be"<< endl;
	
	float a = 1;
	float b = 2;
	float c = 3;

	cout << "\n [T]^{-1}(1,2,3) = " <<  subs(subs(subs(Tinv_image.evalm(), x1 == a), x2 == b), x3 == c) << endl;
	
	return 0;
}