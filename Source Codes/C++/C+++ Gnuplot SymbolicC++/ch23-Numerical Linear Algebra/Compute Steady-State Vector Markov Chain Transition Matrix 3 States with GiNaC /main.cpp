// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

// Merci beaucoup Freya et Sentinel

using namespace std;
using namespace GiNaC;

int main()
{
	Digits = 5; // define maximum decimal digits
	symbol q1("q1"), q2("q2"), q3("q3");
	
	matrix P = { { 0.97, 0.51, 0.6 }, { 0.02, 0.33, 0.3}, { 0.01, 0.16, 0.1 } };
	matrix Q = {{q1}, {q2}, {q3}};
	
	cout << "\n P = " << P << endl;
	cout << "\n q = " << Q << endl;
	cout << "\n I = " << unit_matrix(3) << endl;
	
	// construct an expression (e/e2) containing matrices with arithmetic operators
	ex e = unit_matrix(3) - P; 
	ex e2 = (unit_matrix(3) - P)*Q;
	ex e31 = e2.evalm()[0].subs(q3 ==1-q2-q1);
	ex e32 = e2.evalm()[1].subs(q3 ==1-q2-q1);
	ex e33 = e2.evalm()[2].subs(q3 ==1-q2-q1);

	//cout << "det(P) = " << determinant(P) << endl;

	cout << endl;
	cout << "I-P = " << e << "=\n"  << e.evalm() << endl;
	cout << endl;
	
	cout << "(I-P)q = " << e2 << "=\n"  << e2.evalm() << endl;	
	cout << endl;

	cout << endl;	
	cout << "Equation 1 = " << e31<< endl;
	cout << endl;
	cout << "Equation 2 = " << e32<< endl;
	cout << endl;
	cout << "Equation 3 = " << e33<< endl;
	cout << endl;
	
	lst eqns = {e32 == 0, e33 ==0}; // list all equations need to be solved
	lst vars = {q1,q2}; // list the variables we want to solve
	ex q1_ans = lsolve(eqns, vars)[0].rhs(); // accessing the right-hand side expression
	ex q2_ans = lsolve(eqns, vars)[1].rhs();
 	ex q3_ans = 1 - q1_ans - q2_ans;

	cout << "q1 = " << q1_ans <<endl;
	cout << "q2 = " << q2_ans <<endl;
	cout << "q3 = " << q3_ans<< endl;
	cout << endl;

	matrix q = {{q1_ans}, {q2_ans}, {q3_ans}};
	cout << "q = " << q << endl;
	
	return 0;
}