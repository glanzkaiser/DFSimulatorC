// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya..

#include <iostream>
#include "symbolicc++.h"
using namespace std;

double halving(double x)
{
	double y = 2;
	return x/y;
}

int main(void)
{
	Symbolic x1("x1"), x2("x2"), x3("x3");
	Symbolic xt = ( (  x1 ), (x2), (x3)  );
	Symbolic x =xt.transpose();
	float a11 = 1; //the coefficient for x1^2
	float a22 = 7; //the coefficient for x2^2
	float a33 = -3; //the coefficient for x3^2
	float a12 = halving(4); // the coefficient for x12 divide by 2
	float a13 = halving(-2); // the coefficient for x13 divide by 2
	float a23 = halving(8); // the coefficient for x23 divide by 2
	
	Symbolic A = (  (Symbolic(a11), Symbolic(a12), Symbolic(a13) ),
				( Symbolic(a12), Symbolic(a22), Symbolic(a23) ),
				( Symbolic(a13), Symbolic(a23), Symbolic(a33) ) );
	
	cout << "x = " << x << endl; 
	cout << "x^{T} = " << xt << endl; 
	cout << "A = " <<A << endl; 
	cout << "x^{T} * A* x = " << xt*A*x << endl; 
	
 return 0;
}