// Merci beaucoup Freya et Sentinel
// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

using namespace std;
using namespace GiNaC;

int main()
{
	Digits = 5; // define maximum decimal digits
	symbol x("x");
	ex f, fa, fp;
	float a = 1;
	float b = 2;
	int N = 17;

	float p = a + (b-a)/2 ;

	f = pow(x,3) + 4*pow(x,2) - 10;
	fa = subs(f,x==a);
	fp = subs(f,x==p);

	cout << "f(x) = " << f <<endl;
	cout << endl;
	cout << "a = " << a <<endl;
	cout << "b = " << b <<endl;
	cout << "p = " << p <<endl;

	cout << "f(p) = " << subs(f,x==p) <<endl;
	cout << "f(b) = " << subs(f,x==b) <<endl;
	cout << "f(a) = " << fa << endl;
	cout << "f(a)*f(p) =" << fa*fp << endl;
	cout << endl;

	cout << setw(6) << "iteration" << "\t\t" << "a" << "\t\t\t" << "b" << "\t\t\t" << "p" << "\t\t\t" << "f(p)" << "\n";
	for (int i = 1; i <=N; i++)
	{
		p = a + (b-a)/2 ;
		fa = subs(f,x==a);
		fp = subs(f,x==p);	
		if (fa * fp > 0)
		{
			cout << setw(6) << i << "\t\t\t" << a << "\t\t\t" << b << "\t\t\t" << p << "\t\t\t" << subs(f,x==p) << "\n";
			a = p;
			if ((b-a)/2 < pow(10,-4))
			{
				cout << setw(6) << "Procedure completed successfully" << "\n";
			}
		}	
		else
		{
			cout << setw(6) << i << "\t\t\t" << a << "\t\t\t"<< b << "\t\t\t" << p << "\t\t\t" << subs(f,x==p) << "\n";
			b = p;
			if ((b-a)/2 < pow(10,-4))
			{
				cout << setw(6) << "Procedure completed successfully" << "\n";
			}
		}
		
		cout << endl;
	}	

	return 0;
}