// g++ -o result main.cpp -lginac -lcln
// Merci beaucoup Freya.. et Sentinel..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <ginac/ginac.h>
#include <vector>

using namespace std;
using namespace GiNaC;

// Linear operator T: P_2 -> P_2
// Driver code
int main(int argc, char** argv)
{
	// GiNac codes starts here
	cout << " ******************************************************************** " << endl;
	cout << " ****************************GiNaC Codes***************************** " << endl;
	cout << " ******************************************************************** " << endl;
	
	Digits = 5; // define maximum decimal digits
	symbol x("x"), xpow2("x^2"), a("a"), b("b"), x1("x1"), x2("x2");
	
	ex px = 3*x - 5;
	
	cout << "\n T(1) = " << 1 << endl;
	cout << "\n T(x) = " << px << endl;
	cout << "\n T(x^2) = " << pow(px,2).expand() << endl;
	
	matrix T1 = {{1},{0},{0}};
	matrix Tx = {{-5},{3},{0}};
	matrix Tx2 = {{25},{-30},{9}};
	matrix pB = {{1},{2},{3}};

	cout << "\n [T(1)]_{B} = " << T1 << endl;
	cout << "\n [T(x)]_{B} = " << Tx << endl;
	cout << "\n [T(x^2)]_{B} = " << Tx2 << endl;
	
	matrix TB(3,3);
	TB(0,0) = T1[0];
	TB(0,1) = Tx[0];
	TB(0,2) = Tx2[0];
	TB(1,0) = T1[1];
	TB(1,1) = Tx[1];
	TB(1,2) = Tx2[1];
	TB(2,0) = T1[2];
	TB(2,1) = Tx[2];
	TB(2,2) = Tx2[2];

	ex Tp = (1 + 2*px + 3*(pow(px,2))).expand();

	cout << "\n [T]_{B} = " << TB << endl;
	cout << "\n [p]B = " << pB << endl;
	cout << "\n [T(p)]_{B} = [T]_{B} * [p]B = " << (TB*pB).evalm() << endl;
	
	cout << "\n T(1 + 2x + 3x^2) = " << Tp << endl;

	cout << "\n For T(1 + 2x + 3x^2) : " << endl;

	for (int i = Tp.ldegree(x); i <= Tp.degree(x); ++i)
	{
		cout << " The x^" << i << "-coefficient is " << Tp.coeff(x,i) << endl;
	}

	return 0;
}