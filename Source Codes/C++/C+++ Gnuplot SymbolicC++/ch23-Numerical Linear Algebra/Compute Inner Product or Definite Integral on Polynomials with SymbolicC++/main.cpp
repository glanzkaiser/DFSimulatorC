// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya..

#include <iostream>
#include "symbolicc++.h"
using namespace std;

int main(void)
{
	Symbolic x("x"), p, p1, p2, p3, q, p1_int, p2_int, p3_int, pq_int;
	p1 = 1;
	p2 = x;
	p3 = x^(2);
	p = 1;
	q = x;

	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	cout << "p3 = " << p3 << endl;
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << endl;
	
	p1_int = integrate(p1^(2),x);
	p2_int = integrate(p2^(2),x);
	p3_int = integrate(p3^(2),x);
	pq_int = integrate((p-q)^(2),x);
	
	cout << "integral of p1 = " << p1_int << endl;
	cout << "integral of p1 from -1 to 1 = " << p1_int[x==1] - p1_int[x==-1] << endl;
	cout << "|| p1 || = " << sqrt(p1_int[x==1] - p1_int[x==-1]) << endl;
	cout << endl;
	cout << "integral of p2 = " << p2_int << endl;
	cout << "integral of p2  from -1 to 1 = " << p2_int[x==1] - p2_int[x==-1]<< endl;
	cout << "|| p2 || = " << sqrt(p2_int[x==1] - p2_int[x==-1]) << endl;
	cout << endl;
	cout << "integral of p3 = " << p3_int << endl;
	cout << "integral of p3  from -1 to 1 = " << p3_int[x==1] - p3_int[x==-1]<< endl;
	cout << "|| p3 || = " << sqrt(p3_int[x==1] - p3_int[x==-1]) << endl;
	cout << endl;
	cout << "d(p,q) = || p-q || = " << sqrt(pq_int[x==1] - pq_int[x==-1]) << endl;
	
	return 0; 
}