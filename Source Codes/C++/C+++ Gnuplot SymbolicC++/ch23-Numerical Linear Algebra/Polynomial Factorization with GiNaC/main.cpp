// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

// Merci beaucoup Freya et Sentinel

using namespace std;
using namespace GiNaC;

int main()
{
	Digits = 5; // define maximum decimal digits
	symbol λ("λ");
	
	// construct an expression with arithmetic operators
	ex characteristic_polynomial = pow(λ,3) - 2 * (pow(λ,2)) + λ + 5;
	//ex characteristic_polynomial = pow(λ,3) - 8 * (pow(λ,2)) + 17*λ - 4;

	cout << endl;
	cout << "p(λ) = " << characteristic_polynomial << endl;
	cout << endl;
	// cout << factor(characteristic_polynomial, factor_options::all) << endl;
	// quo = compute the quotient of univariate polynomials in polynomial division
	// rem = compute the reminder of univariate polynomials in polynomial division
	
	ex a = quo(characteristic_polynomial, λ + 5, λ) ;
	ex b = rem(characteristic_polynomial, λ + 5, λ);
	ex c = a + b;	
	
	cout << "Quotient of p(λ) / (λ+5) = " << a << endl;
	cout << "Reminder of p(λ) / (λ+5) = " << b << endl;
	cout << endl;
	
	cout << "Quotient * (λ+5) = " << expand((λ+5) * a) << endl;
	
	cout << "[ Quotient * (λ+5) ] + reminder = " << expand((λ+5) * a) + b << endl;
			
	return 0;
}