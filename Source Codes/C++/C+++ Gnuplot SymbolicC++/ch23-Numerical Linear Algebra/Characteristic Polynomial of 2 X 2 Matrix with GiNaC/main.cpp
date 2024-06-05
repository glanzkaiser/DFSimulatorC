// g++ main.cpp -o result -lginac -lcln -lsymbolicc++
#include <iostream>
#include <ginac/ginac.h>
#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>

// Merci beaucoup Freya et Sentinel

#define R 2 // number of rows
#define C 2 // number of columns

using namespace std;
using namespace GiNaC;

int main()
{
	
	Digits = 5; // define maximum decimal digits
	symbol λ("λ"), a("a"), b("b"), c("c"), d("d");
	
	matrix A = { { a, b }, { c, d}};
	matrix I = { { λ, 0 }, { 0, λ}};
	cout << "\n A = " << A << endl;
	cout << "\n I = " << I << endl;
	cout << "\n A^{-1}= " << inverse(A) << endl;
	
	matrix B_mat = I.sub(A);
	matrix BInv_mat = I.sub(inverse(A));
	
	cout << endl;
	
	cout << "λI-A = " << B_mat <<endl;
	cout << endl;
	cout << "Characteristic Polynomial : det(λI - A) = " << determinant(B_mat) << endl;
	cout << endl;
	
	cout << "λI-A^{-1} = " << BInv_mat <<endl;
	cout << "Characteristic Polynomial : det(λI - A^{-1}) = " << determinant(BInv_mat) << endl;
	cout << endl;
	
	ex λA = 0.5*((a+d) + pow((a*a-2*a*d+d*d)+4*b*c,0.5)) ;
	ex λAInv = 0.5*(1/(a*d-b*c))*( (a+d) + pow((a*a-2*a*d+d*d)+4*b*c,0.5) ) ;
	
	cout << "λ for A = " << λA << endl;
	cout << endl;
	cout << "λ for A^{-1} = " << λAInv << endl;
	cout << endl;
	/*
	if ((λA/(a*d-b*c) - λAInv).is_zero())
	{
	cout << "λ of A^{-1} = λ of A / (ad-bc) " << endl;
	}
	else
	{
	cout << "λ of A^{-1} != λ of A / (ad-bc)  " << endl;
	}
	*/
	return 0;
}