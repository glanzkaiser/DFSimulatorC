// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya..

#include <iostream>
#include "symbolicc++.h"
using namespace std;

int main(void)
{
	Symbolic x("x"), y, y_int;
	y = sin(x);
	cout << "y = " << y << endl;
	y_int = integrate(y,x);
	
	cout << "integral of y = " << y_int << endl;
	cout << "integral of y = " << y_int[x==1] - y_int[x==-1]<< endl;
	return 0; 
}