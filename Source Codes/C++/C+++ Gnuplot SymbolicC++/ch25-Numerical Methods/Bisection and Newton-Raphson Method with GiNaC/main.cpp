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
	symbol λ("λ");
	int N = 17;
	ex f, fd, fp, fpd, fpb, fa, fb;
	ex pn;
	ex p0 = (pi/4);
	
	f = pow(λ,3) - 2*pow(λ,2) + λ + 5;
	
	// Newton-Raphson formula
	fd = diff(f,λ);	
	fp = subs(f,λ==p0);
	fpd = subs(fd,λ==p0);
	
	// Bisection parameters and formula
	float a = -3;
	float b = 2;
	float p = a + (b-a)/2 ;

	fa = subs(f,λ==a);
	fb = subs(f,λ==b);
	fpb = subs(f,λ==p);
	
	cout << "f(x) = " << f <<endl;
	cout << endl;
	cout << "f'(x) = " << fd <<endl;
	cout << endl;
	cout << "p_{0} = " << p0 <<endl;
	cout << endl;
	cout << "a = " << a <<endl;
	cout << "b = " << b <<endl;
	cout << "p = " << p <<endl;
	cout << "f(a) = " << fa << endl;
	cout << "f(b) = " << fb << endl;
	cout << "f(p) = " << fp << endl;
	
	cout << setw(6) << "n" << "\t\t\t" << "p_{n} (Newton-Raphson)"  << "\t\t\t" << "p_{n} (Bisection)" << "\n\n";
	cout << setw(6) << "0" << "\t\t\t" << p0 << "\t\t\t" << p<< "\n";	
	for (int i = 1; i <=N; i++)
	{
		fp = subs(f,λ==p0);
		fpd = subs(fd,λ==p0);
		pn = p0 - (fp/fpd);
		// Bisection
		p = a + (b-a)/2 ;
		fa = subs(f,λ==a);
		fpb = subs(f,λ==p);	
		
		if (fa * fpb > 0)
		{
			cout << setw(6) << i << "\t\t\t" << pn << "\t\t\t" << p << "\n";
			a = p;
			if ((b-a)/2 < pow(10,-4))
			{
				cout << setw(6) << "Bisection method converges" << "\n";
			}
		}	
		else
		{
			cout << setw(6) << i << "\t\t\t" << pn << "\t\t\t" << p << "\n";
			b = p;
			if ((b-a)/2 < pow(10,-4))
			{
				cout << setw(6) << "Bisection method converges" << "\n";
			}
		}

		if (abs(p0 - pn) < pow(10,-5))
			{
				cout << "Newton-Raphson method converges" << endl;			
				//break;
			}
		p0 = pn;
		}	
	return 0;
}