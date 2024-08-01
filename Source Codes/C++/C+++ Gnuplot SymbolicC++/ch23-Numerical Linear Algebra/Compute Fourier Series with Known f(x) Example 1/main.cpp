// g++ -o result main.cpp -lboost_iostreams -lsymbolicc++
// Merci beaucoup Freya et Sentinel
// Kaing bla kaing.. Hasta la meo -Bludut
// make
// https://cplusplus.com/forum/beginner/251672/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include "gnuplot-iostream.h"
#include "symbolicc++.h"

using namespace std;

const double PI = 3.14159265358979;

double division(double x, double y)
{
	return x/y;
}

int main()
{
	Symbolic x("x"), y, n("n"), π("π");
	const double period = 1.0;               // Period of function
	const int N = 10;                             // Order for the trigonometric polynomial

	y = π; // this is a0/2 = π

	//freopen ("fourierseries.txt","w",stdout); // You can redirect stdout, stderr and stdin using std::freopen
	// Fourier series of the function f(x)=x, 0 <= x <= 2π
	// x = sum_{1}^{N} (-2/n)  * sin(nx)	
	for ( int n = 1; n <= N; n++ ) 
	{
		y +=  division(-2,n)*sin( n*x );
		cout << n <<" " << y << endl;
	}

	return 0;
}
