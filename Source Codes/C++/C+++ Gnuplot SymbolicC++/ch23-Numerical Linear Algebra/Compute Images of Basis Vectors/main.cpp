// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

// Merci beaucoup Freya et Sentinel

using namespace std;
using namespace GiNaC;

int main()
{
	Digits = 5; // define maximum decimal digits
	symbol x1("x1"), x2("x2"), x3("x3"), c1("c1"), c2("c2"), c3("c3");

	// Store basis vectors as a 3x1 vector in GiNac
	matrix v1 = {{1,1,1}};
	matrix v2 = {{1,1,0}};
	matrix v3 = {{1,0,0}};

	matrix Tv1 = {{1,0}};
	matrix Tv2 = {{2,-1}};
	matrix Tv3 = {{4,3}};

	matrix A(3,3);
	A(0,0) = v1[0];	A(1,0) = v2[0];	A(2,0) = v3[0];
	A(0,1) = v1[1];	A(1,1) = v2[1];	A(2,1) = v3[1];
	A(0,2) = v1[2];	A(1,2) = v2[2];	A(2,2) = v3[2];
	
	ex c = lst_to_matrix(lst{lst{c1},lst{c2},lst{c3}});
	ex x = lst_to_matrix(lst{lst{x1},lst{x2},lst{x3}});
	ex d = (A*c).evalm();
	cout << "\nMatrix A consists of basis vector S ={v1, v2, v3} for R3"<< endl;
	cout << "\n A = " << A << endl;
	cout << "\n c = " << c << endl;
	cout << "\n x = " << x << endl;
	cout << "\nLet T: R3 -> R2 be the linear transformation for which"<< endl;
	cout << "\n T(v1) = " << Tv1 << endl;
	cout << "\n T(v2) = " << Tv2 << endl;
	cout << "\n T(v3) = " << Tv3 << endl;
	cout << "\n A*c = " << d << endl;
	
	lst eqns = {d[0] == x1, d[1] ==x2, d[2] == x3}; // list all equations need to be solved
	lst vars = {c1,c2,c3}; // list the variables we want to solve
	ex c1_ans = lsolve(eqns, vars)[0].rhs(); // accessing the right-hand side expression
	ex c2_ans = lsolve(eqns, vars)[1].rhs(); // accessing the right-hand side expression
	ex c3_ans = lsolve(eqns, vars)[2].rhs(); // accessing the right-hand side expression
	
	cout << "\nExpress x(x1,x2,x3) as a linear combination of v1, v2, v3"<< endl;
	cout << "then solve A*c=x will yields"<< endl;
	cout << "\n  " << lsolve(eqns, vars)<< endl;
	
	ex dom = c1_ans*v1 + c2_ans*v2 + c3_ans*v3 ;
	ex image = c1_ans*Tv1 + c2_ans*Tv2 + c3_ans*Tv3 ;

	cout << "\n (x1,x2,x3) = " <<  dom << endl;
	cout << "\n T(x1,x2,x3) = " <<  image << endl;
	cout << " T(x1,x2,x3) = " <<  image.evalm() << endl;
	
	cout << "\n T(2,-3,5) = " <<  subs(subs(subs(image.evalm(), x1 == 2), x2 == -3), x3 == 5) << endl;
	cout << endl;

	return 0;
}