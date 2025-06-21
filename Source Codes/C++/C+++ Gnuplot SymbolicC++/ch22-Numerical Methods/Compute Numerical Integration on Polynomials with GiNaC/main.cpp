// g++ -o result main.cpp -lginac -lcln
// Merci beaucoup Freya..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <ginac/ginac.h>

using namespace std;
using namespace GiNaC;

// Driver code
int main(int argc, char** argv)
{
	// GiNaC computation starts here for symbolic computation
	Digits = 5; // define maximum decimal digits
	symbol x("x") ;
	
	// Define the polynomials
	ex p = exp(x) ; // polynomial p
	
	cout << "p (x) = " << pow(x,2) <<endl;
	cout << endl;
	
	//GiNaC is not very good at symbolically evaluating integrals, it can only integrate polynomials.
	cout << "integral_{-1}^{1} p(x) = " <<integral(x,0,1,p).evalf() <<endl;
	cout << "integral_{-1}^{1} p(x) = " <<integral(x,0,1,p).eval_integ() <<endl;
	
	return 0;
}