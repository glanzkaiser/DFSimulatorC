// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya..

#include <iostream>
#include "symbolicc++.h"
using namespace std;

int main(void)
{
	// c is a symbolic constant
	Symbolic x("x"), c("c"), z("z"), y, y_int;

	// We declare z to be dependent on x
	z = z[x];
	y = sin(x)+ x*exp(x) + c + z;
	cout << "y = " << y << endl;

	for (int i = 0; i<3; i++)
	{
		y = integrate(y,x);
		y = y[integrate(x*exp(x),x) == x*exp(x) - exp(x)];
		cout << i+1 << "integral of y = " << y << endl;	
	}
	return 0; 
}