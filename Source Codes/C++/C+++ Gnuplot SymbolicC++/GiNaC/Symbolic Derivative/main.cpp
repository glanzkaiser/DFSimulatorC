// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

using namespace std;
using namespace GiNaC;

int main()
{
	symbol x("x");
	ex fx, dx; // construct expressions 
	fx = tan(x);
	
	dx = diff(fx,x);
	cout << "Derivative of " << fx << " is " << dx << endl;
	return 0;
}