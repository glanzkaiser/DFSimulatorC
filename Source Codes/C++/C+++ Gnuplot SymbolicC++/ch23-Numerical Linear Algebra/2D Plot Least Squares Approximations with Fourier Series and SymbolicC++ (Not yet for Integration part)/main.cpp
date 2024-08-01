// g++ -o result main.cpp -lboost_iostreams -lsymbolicc++
// Merci beaucoup Freya et Sentinel
// Kaing bla kaing.. Hasta la meo -Bludut

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
#include "gnuplot-iostream.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

using namespace std;

#define R 2 // number of rows
#define C 2 // number of columns
#define theta 60

// Driver program
int main()
{
	
	Symbolic x("x"), π("π"),k("k");
	Symbolic a0, a0_raw, ak_raw, ak, bk_raw, bk, fx;

	// the function we want to approximate
	fx = x;
	
	a0_raw = integrate((1/π)*(fx),x);
	a0 = a0_raw[x==2*π] - a0_raw[x==0];

	ak_raw = integrate((1/π)*(fx)*(cos(k*x)),x);
	//ak = ak_raw[x==2*π] - ak_raw[x==0];

	bk_raw = integrate((1/π)*(fx)*(sin(k*x)),x);
	bk = bk_raw[x==2*π] - bk_raw[x==0];

	cout << "a0 = " << a0 << endl;
	//cout << "ak = " << ak << endl;
	//cout << "bk = " << bk << endl;

	for(int i=0;i<1;i++)
	{
		ak = integrate((1/π)*(fx)*(cos(k*x)),x);
		bk = integrate((1/π)*(fx)*(sin(k*x)),x);
		
		ak = ak[integrate((1/π)*(fx)*(cos(k*x)),x) == x*cos(k*x) - (1/k)*sin(k*x)];
		ak = bk[integrate((1/π)*(fx)*(sin(k*x)),x) == x*sin(k*x) + (1/k)*cos(k*x)];

		cout << "ak = " << ak[x==2*π] - ak[x==0] << endl;
		cout << "bk = " << bk[x==2*π] - bk[x==0] << endl;
	}

	Gnuplot gp;
	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [0:15]\nset yrange [0:9]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	// Put the degree in the equation for f(x) = (theta*DEGTORAD )* x
	gp << "f1(x) = x  \n";	
	gp << "f(x) = 3.14 - 2*sin(x)  \n";	
	gp << "g(x) = 3.14 - 2*sin(x) - sin(2*x) \n";
	gp << "h(x) = 3.14 - 2*sin(x) - sin(2*x) - 2*sin(3*x)/3 \n";
	
	gp << "plot f1(x) title 'y=x' lc 'black',\
			f(x) title 'y=π - 2 sin x' lc 'green', g(x) title 'y = π - 2 ( sin x + sin(2x) / 2 ) '  lc 'blue',\
			h(x) title 'y = π - 2 ( sin x + sin(2x) / 2 + sin(3x) / 2 ) '  lc 'orange'\n";

	return 0;
}