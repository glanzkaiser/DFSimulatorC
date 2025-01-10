// g++ -o result main.cpp -lginac -lcln
// Merci beaucoup Freya.. et Sentinel..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <ginac/ginac.h>

using namespace std;
using namespace GiNaC;

// T(a+bx) = x(a+bx) = ax + bx^2
// Driver code
int main(int argc, char** argv)
{
	// GiNac codes starts here
	Digits = 5; // define maximum decimal digits
	symbol x("x"), xpow2("x^2"), a("a"), b("b");
	
	// Initialize vector T(u1) and T(u2) as zero vectors first
	matrix Tu1 = {{0},{0},{0}};
	matrix Tu2 = {{0},{0},{0}};
	ex u1 = x;
	ex u2 = xpow2;

	cout << "\n u1 = " << u1 << endl;
	cout << "\n u2 = " << u2 << endl;
		
	// If else conditional to compute [T(u1)]_{B'}
	if (u1 == 1)
	{
		Tu1 = {{1}, {0}, {0}};
	}
	else if (u1 == x)
	{
		Tu1 = {{0}, {1}, {0}};
	}
	else if (u1 == xpow2)
	{
		Tu1 = {{0}, {0}, {1}};
	}

	// If else conditional to compute [T(u2)]_{B'}
	if (u2 == 1)
	{
		Tu2 = {{1}, {0}, {0}};
	}
	else if (u2 == x)
	{
		Tu2 = {{0}, {1}, {0}};
	}
	else if (u2 == xpow2)
	{
		Tu2 = {{0}, {0}, {1}};
	}

	cout << "\n T(u1) = " << Tu1 << endl;
	cout << "\n T(u2) = " << Tu2 << endl;
	
	// Construct matrix [T]_{B',B}
	matrix TBBnew(3,2);
	TBBnew(0,0) = Tu1[0];
	TBBnew(0,1) = Tu2[0];
	TBBnew(1,0) = Tu1[1];
	TBBnew(1,1) = Tu2[1];
	TBBnew(2,0) = Tu1[2];
	TBBnew(2,1) = Tu2[2];

	matrix xB(2,1);
	xB(0,0) = a;
	xB(1,0) = b;

	// Construct a vector 1X3 as the new basis vector = {1,x,x^2}
	matrix newBasis(1,3);
	newBasis(0,0) = 1;
	newBasis(0,1) = x;
	newBasis(0,2) = xpow2;

	cout << "\n [T]_{B',B} = " << TBBnew << endl;
	cout << "\n [x]_{B} = " << xB << endl;
	
	ex TxBnew = (TBBnew*xB).evalm();
	cout << "\n [T]_{B',B} * [x]_{B}= " << TxBnew << endl;
	
	ex Tx = (newBasis*TxBnew).evalm();
	cout << "\n T(a+bx)= " << Tx << endl;

	return 0;
}