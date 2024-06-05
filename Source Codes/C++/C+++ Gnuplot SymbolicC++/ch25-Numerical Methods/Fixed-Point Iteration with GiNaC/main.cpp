// Merci beaucoup Freya et Sentinel
// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define pi  3.1415926535897

using namespace std;
using namespace GiNaC;

int main()
{
	Digits = 10; // define maximum decimal digits
	symbol x("x");
	ex f, g1, g2, g3, g4, g5, pn1, pn2, pn3, pn4, pn5;
	ex p0 = 1.5;
	ex p01 = 1.5;
	ex p02 = 1.5;
	ex p03 = 1.5;
	ex p04 = 1.5;
	ex p05 = 1.5;
	int N = 20;

	f = pow(x,3) + 4*pow(x,2) - 10;	
	g1 = x - pow(x,3) - 4*pow(x,2) - 10;
	g2 = pow(10/x - 4*x,0.5);
 	g3 = 0.5*pow(10 - pow(x,3),0.5); 
	g4 = pow(10/(4+x),0.5);
	g5 = x - (pow(x,3) + 4*(pow(x,2)) - 10)/(3*pow(x,2) + 8*x);
	
	cout << "f(x) = " << f <<endl;
	cout << "g1(x) = " << g1 <<endl;
	cout << "g2(x) = " << g2 <<endl;
	cout << "g3(x) = " << g3 <<endl;
	cout << "g4(x) = " << g4 <<endl;
	cout << "g5(x) = " << g5 <<endl;
	cout << endl;
	
	cout << setw(6) << "n" << "\t\t" << "p_{n} for g1"  <<  "\t\t\t" << "p_{n} for g2"  << "\n";
	cout << setw(6) << "0" << "\t\t" << p0 << "\t\t\t\t" << p0 << "\n";	
		
	for (int i = 1; i <=4; i++)
	{
		pn1 = subs(g1,x==p01);
		pn2 = subs(g2,x==p02);

		cout << setw(6) << i << "\t\t" << pn1 << "\t\t\t" << pn2 <<  "\n";
		
		if (abs(p0 - pn3) < pow(10,-5))
			{
				cout << "The procedure was successful." << endl;			
				break;
			}
		p01 = pn1;
		p02 = pn2;
	}	
	cout << endl;
	cout << endl;

	cout << setw(6) << "n" << "\t\t" << "p_{n} for g3"  <<  "\t\t\t" << "p_{n} for g4"  <<  "\t\t\t" << "p_{n} for g5"  << "\n";	
	cout << setw(6) << "0" << "\t\t" << p0 << "\t\t\t\t" << p0 << "\t\t\t\t" << p0 << "\n";	
	for (int i = 1; i <=N; i++)
	{
		pn3 = subs(g3,x==p03);
		pn4 = subs(g4,x==p04);
		pn5 = subs(g5,x==p05);

		cout << setw(6) << i << "\t\t" << pn3 << "\t\t" << pn4 << "\t\t" << pn5 << "\n";
		
		if (abs(p0 - pn3) < pow(10,-5))
			{
				cout << "The procedure was successful." << endl;			
				break;
			}
		p03 = pn3;
		p04 = pn4;
		p05 = pn5;
	}
	return 0;
}