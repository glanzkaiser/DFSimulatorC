// g++ main.cpp -o result -lsymbolicc++
#include <iostream>
#include "symbolicc++.h"
using namespace std;

int factorial(int N)
{
	int result = 1;
	for(int i = 2; i <= N; i++)
	{
		result *= i;
	}
	return result;
}

int main(void)
{
	int i, j, n=4;
	Symbolic u("u"), x("x"), result;
	Symbolic u0("",n), y("",n);
	u = u[x];
	u0(0) = u*u+x;
	for(j=1;  j<n; j++)
	{
		u0(j) = df(u0(j-1),x);
	}	
	cout << "u0: " << u0 << endl;

	// initial condition u(0)=1
	u0(0)=u0(0)[u==1, x==0];

	y(0) = u;
	for(i=1; i<n; i++)
	{
		for(j=i; j>0; j--)
		{
			u0(i) = u0(i)[y(j) == u0(j-1)];
		}
	}
	cout << "u0: " << u0 << endl;

	for(i=0; i<n; i++)
	{
		result += (Symbolic(1)/factorial(i+1))*u0(i)*(x^(i+1));
	}
	cout << "u(x): " << result << endl;

	return 0;
}