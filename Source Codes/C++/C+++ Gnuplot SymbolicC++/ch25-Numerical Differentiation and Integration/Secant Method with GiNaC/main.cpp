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
	ex f, fp0, fp1, fpn;
	ex pn;
	ex p0 = 0.5;
	ex p1 = (pi/4);
	int N = 10;

	f = cos(x) - x; // the input x has to be in Radian
	fp0 = subs(f,x==p0);
	fp1 = subs(f,x==p1);
 
	cout << "f(x) = " << f <<endl;
	cout << endl;
	cout << "p_{0} = " << p0 <<endl;
	cout << endl;
	cout << "p_{1} = " << p1 <<endl;
	cout << endl;
	
	cout << setw(6) << "n" << "\t\t" << "p_{n}"  << "\t\t\t\t" << "p_{n} in Degree" << "\n";
	cout << setw(6) << "0" << "\t\t" << p0 << "\t\t\t\t" << p0*RADTODEG << "\n";	
	cout << setw(6) << "1" << "\t\t" << p1 << "\t\t" << p1*RADTODEG << "\n";	
	for (int i = 2; i <=N; i++)
	{
		fp0 = subs(f,x==p0);
		fp1 = subs(f,x==p1);
		pn = p1 - ((fp1*(p1-p0)) / (fp1 - fp0));

		cout << setw(6) << i << "\t\t" << pn << "\t\t" << pn*RADTODEG << "\n";
		
		if (abs(p1 - pn) < pow(10,-5))
			{
				cout << "The procedure was successful." << endl;			
				break;
			}
		p0 = p1;
		fp0 = fp1;
		p1 = pn;
		fpn = subs(f,x==pn);
		fp1 = fpn;
		
		}	
	return 0;
}