// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya..

#include <iostream>
#include "symbolicc++.h"
using namespace std;

#define pi  3.1415926535897

int main(void)
{
	Symbolic x("x"), a, y, f1, f2, f3, g1, g2, g3, f1g1_int, f2g2_int, f3g3_int;
	f1 = cos(2*pi*x);
	f2 = x;
	f3 = tan(x*pi/4);
	g1 = sin(2*pi*x);
	g2 = exp(x);
	g3 = 1;

	y = f1*f2;

	cout << "f1 = " << f1 << "\t" << "g1 = " << g1 <<  endl;
	cout << "f2 = " << f2 << "\t" << "g2 = " << g2 <<  endl;
	cout << "f3 = " << f3 << "\t" << "g3 = " << g3 <<  endl;
	cout << endl;
	
	f1g1_int = integrate(f1*g1,x);
	f2g2_int = integrate(f2*g2,x);
	f3g3_int = integrate(f3*g3,x);
	
	cout << "integral of f1*g1 = " << f1g1_int << endl;
	cout << "integral of f1*g1 from 0 to 1 = " << f1g1_int[x==1] - f1g1_int[x==0] << endl;
	cout << endl;
	cout << "integral of f2*g2 = " << f2g2_int << endl;
	cout << "integral of f2*g2 from 0 to 1 = " << f2g2_int[x==1] - f2g2_int[x==0] << endl;
	cout << endl;
	cout << "integral of f3*g3 = " << f3g3_int << endl;
	cout << "integral of f3*g3 from 0 to 1 = " << f3g3_int[x==1] - f3g3_int[x==0] << endl;
	cout << endl;

	for (int i = 0; i<1; i++)
	{
		y = integrate(y,x);
		y = y[integrate(cos(2*pi*x)*sin(2*pi*x),x) == cos(2*pi*x)*sin(2*pi*x) - (x/(2*pi)) ];
		cout << i+1 << "-th integral of y = " << y << endl;	
	}
		
	return 0; 
}