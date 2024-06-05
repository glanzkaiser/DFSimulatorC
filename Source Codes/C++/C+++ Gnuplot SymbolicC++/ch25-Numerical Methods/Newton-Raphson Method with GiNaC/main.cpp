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
	Digits = 5; // define maximum decimal digits
	symbol x("x");
	ex f, fd, fp, fpd;
	ex pn;
	ex p0 = (pi/4);
	int N = 5;

	f = cos(x) - x; // the input x has to be in Radian
	fd = diff(f,x);	
	fp = subs(f,x==p0);
	fpd = subs(fd,x==p0);
 
	cout << "f(x) = " << f <<endl;
	cout << endl;
	cout << "f'(x) = " << fd <<endl;
	cout << endl;
	cout << "p_{0} = " << p0 <<endl;
	cout << endl;
	
	cout << setw(6) << "n" << "\t\t" << "p_{n}"  << "\t\t\t" << "p_{n} in Degree" << "\n";
	cout << setw(6) << "0" << "\t\t" << p0 << "\t\t" << p0*RADTODEG << "\n";	
	for (int i = 1; i <=N; i++)
	{
		fp = subs(f,x==p0);
		fpd = subs(fd,x==p0);
		pn = p0 - (fp/fpd);

		cout << setw(6) << i << "\t\t" << pn << "\t\t" << pn*RADTODEG << "\n";
		
		if (abs(p0 - pn) < pow(10,-5))
			{
				cout << "The procedure was successful." << endl;			
				break;
			}
		p0 = pn;
		}	
	return 0;
}