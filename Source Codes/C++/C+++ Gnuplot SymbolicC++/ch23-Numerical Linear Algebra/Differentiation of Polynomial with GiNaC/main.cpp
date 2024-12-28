// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

// Merci beaucoup Freya et Sentinel

using namespace std;
using namespace GiNaC;

int main()
{
	Digits = 5; // define maximum decimal digits
	symbol a0("a0"), a1("a1"), a2("a2"), a3("a3");
	
	cout << "Suppose we have a polynomial P_{3} : a0 + a1x + a2x^2 + a3x^3 " << endl;
	cout << "We will compute the differentiation transformation" << endl;
	cout << "D: P_{3} -> P_{2} with matrix multiplication" << endl;
	
	matrix A = { { 0, 1, 0, 0 }, { 0, 0, 2, 0}, { 0, 0, 0, 3 } };
	// Store basis vectors as a 4x1 vector in GiNac
	matrix x = {{a0},{a1},{a2},{a3}};

	cout << "\n A = " << A << endl;
	cout << "\n x = " << x << endl;
	ex Ax = (A*x).evalm();
	
	cout << "\n A*x = " << Ax << endl;
	cout << "\n d/dx (a0 + a1x + a2x^2 + a3x^3)  = " << Ax[0] << " + " << Ax[1] << " x + " << Ax[2] << " x^2 "  << endl;
	
	cout << "\n If we try to input value for a0, a1, a2, a3" << endl;
	cout << "\n a0 = 2, a1 = 1, a2 = 4, a3 = -1" << endl;
	matrix x1 = {{2},{1},{4},{-1}};
	ex Ax1 = (A*x1).evalm();
	cout << "\n d/dx (2 + x + 4 x^2 - x^3)  = " << Ax1[0] << " + " << Ax1[1] << " x + " << Ax1[2] << " x^2 "  << endl;
	return 0;
}