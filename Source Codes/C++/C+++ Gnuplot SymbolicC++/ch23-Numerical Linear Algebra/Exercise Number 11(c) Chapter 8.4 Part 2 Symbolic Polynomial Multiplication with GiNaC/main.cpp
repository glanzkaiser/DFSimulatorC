// g++ -o result main.cpp -lginac -lcln
// Merci beaucoup Freya.. et Sentinel..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <ginac/ginac.h>
#include <vector>

using namespace std;
using namespace GiNaC;

double division(double x, double y)
{
	return x/y;
}

// Linear operator T: P_2 -> P_2
// Driver code
int main(int argc, char** argv)
{
	// GiNac codes starts here
	cout << " ******************************************************************** " << endl;
	cout << " ****************************GiNaC Codes***************************** " << endl;
	cout << " ******************************************************************** " << endl;
	
	Digits = 5; // define maximum decimal digits
	symbol x("x"), a0("a0"), a1("a1"), a2("a2");
	
	ex c1 = (division(8,28))*a0 + (division(2,28))*a1 - (division(6,28))*a2;
	ex c2 = (division(6,14))*a0 - (division(2,14))*a1 + (division(6,14))*a2;
	ex c3 = -(division(2,7))*a0 + (division(3,7))*a1 - (division(2,7))*a2;

	ex Tv1 = 5 + 2*x - 2*pow(x,2) ;
	ex Tv2 = 3 + 4*pow(x,2) ; 
	ex Tv3 = 3 + 28*x + 18*pow(x,2) ; 

	cout << "\n c_{1} = " << c1 << endl;
	cout << "\n c_{2} = " << c2 << endl;
	cout << "\n c_{3} = " << c3 << endl;

	cout << "\n T(v_{1}) = " << Tv1 << endl;
	cout << "\n T(v_{2}) = " << Tv2 << endl;
	cout << "\n T(v_{3}) = " << Tv3 << endl;
	
	ex Tp2 = (c1*Tv1 + c2*Tv2 + c3*Tv3).expand();

	cout << "\n T(a_{0} + a_{1} x + a_{2} x^2) = " << Tp2 << endl;

	cout << "\n For T(a_{0} + a_{1} x + a_{2} x^2) : " << endl;

	for (int i = Tp2.ldegree(x); i <= Tp2.degree(x); ++i)
	{
		cout << "\n The x^" << i << "-coefficient is " << Tp2.coeff(x,i) << endl;
	}

	cout << "\n T(1 + x^2) = " <<  subs(subs(subs( (Tp2).evalf(), a0==1), a1==0), a2==1)<< endl;
	return 0;
}