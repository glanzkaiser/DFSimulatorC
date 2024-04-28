// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

// Merci beaucoup Freya et Sentinel

using namespace std;
using namespace GiNaC;

int main()
{
	Digits = 5; // define maximum decimal digits
	symbol q1("q1"), q2("q2");
	
	matrix P = {{0.8, 0.1}, {0.2, 0.9}};
	matrix Q = {{q1}, {q2}};
	
	cout << "\n P = " << P << endl;
	cout << "\n q = " << Q << endl;
	cout << "\n I = " << unit_matrix(2) << endl;
	
	// construct an expression (e/e2) containing matrices with arithmetic operators
	ex e = unit_matrix(2) - P; 
	ex e2 = (unit_matrix(2) - P)*Q;
	ex e3 = e2.evalm()[0].subs(q1 ==1-q2);
	ex q2_ans = lsolve(e3 == 0 , q2) ;

	//cout << "det(P) = " << determinant(P) << endl;

	cout << endl;
	cout << "I-P = " << e << "=\n"  << e.evalm() << endl;
	cout << endl;
	
	cout << "(I-P)q = " << e2 << "=\n"  << e2.evalm() << endl;	
	cout << endl;

	cout << endl;	
	cout << "(I-P)q [q1 = 1-q2]= " << e3<< endl;
	cout << endl;

	cout << "q2 = " << lsolve(e3 == 0 , q2) << endl;
	cout << "q1 = 1 - q2 = " << 1 - q2_ans << endl;	
	cout << endl;

	matrix q = {{1 - q2_ans}, {q2_ans}};
	cout << "q = " << q << endl;
	
	return 0;
}