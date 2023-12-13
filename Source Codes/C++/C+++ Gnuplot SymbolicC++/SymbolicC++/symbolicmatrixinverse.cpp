// g++ -o result symbolicmatrixinverse.cpp -lsymbolicc++
// make 
// (adjust the cpp filename first)
#include <iostream>
#include "symbolicc++.h"
using namespace std;

int main(void)
{
	Symbolic theta("theta");
	Symbolic R = ( (  cos(theta), sin(theta) ),
				( -sin(theta), cos(theta) ) );
	cout << "R = " << R << endl; // 
	cout << "R(0,1) = " << R(0,1) << endl; // sin(theta)
	Symbolic RI = R.inverse();
	cout << "R.inverse()" << RI[ (cos(theta)^2) == 1 - (sin(theta)^2) ] << endl;
	
 return 0;
}