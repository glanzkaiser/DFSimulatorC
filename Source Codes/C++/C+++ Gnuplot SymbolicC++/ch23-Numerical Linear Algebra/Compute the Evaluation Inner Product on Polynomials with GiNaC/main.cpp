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
	
	// Define points for the evaluation inner product 
	float x0 = -2;
	float x1 = 0;
	float x2 = 2; 
	
	// Define the polynomials
	ex p = pow(x,2) ; // polynomial p
	ex q = 1 + x ; // polynomial q
	cout << endl;

	cout << "p = " << p <<endl;
	cout << "q = " << q <<endl;
	cout << endl;
	
	ex inner_product = p.subs(x==x0)*q.subs(x==x0) +  p.subs(x==x1)*q.subs(x==x1) + p.subs(x==x2)*q.subs(x==x2) ;
	ex norm_p = sqrt(pow(p.subs(x==x0),2) +  pow(p.subs(x==x1),2) + pow(p.subs(x==x2),2) ) ;
	ex norm_q = sqrt(pow(q.subs(x==x0),2) +  pow(q.subs(x==x1),2) + pow(q.subs(x==x2),2) ) ;

	cout << "<p,q> = " << inner_product <<endl;
	cout << "||p|| = " << norm_p <<endl;
	cout << "||q|| = " << norm_q <<endl;
	
	return 0;
}