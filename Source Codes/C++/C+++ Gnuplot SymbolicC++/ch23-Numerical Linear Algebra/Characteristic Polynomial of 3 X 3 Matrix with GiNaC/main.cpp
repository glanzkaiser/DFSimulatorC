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
	
	matrix A = { { 0, 1, 0 }, { 0, 0, 1}, { 4, -17, 8 } };
	matrix I = { { λ, 0, 0 }, { 0, λ, 0}, { 0, 0, λ } };
	cout << "\n A = " << A << endl;
	cout << "\n I = " << I << endl;
	
	matrix result = I.sub(A);
	
	cout << endl;
	
	cout << "λI-A = " << result <<endl;
	cout << endl;
	cout << "Characteristic Polynomial : det(λI - A) = " << determinant(result) << endl;
	cout << endl;

	return 0;
}