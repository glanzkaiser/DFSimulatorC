// g++ -o result main.cpp -lginac -lcln
// Merci beaucoup Freya..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <ginac/ginac.h>
#include "gnuplot-iostream.h"

using namespace std;
using namespace GiNaC;

// Driver code
int main(int argc, char** argv)
{
	// GiNaC computation starts here for symbolic computation
	Digits = 5; // define maximum decimal digits
	symbol x("x") ;
	
	// Define the upper and lower bound for the integral
	float x0 = -1;
 	float x1 = 1;
	// Define the polynomials
	ex u1 =  1; 
	ex u2 = x ; 
	ex u3 = pow(x,2) ; 
	cout << endl;

	cout << "u1 = " << u1 <<endl;
	cout << "u2 = " << u2 <<endl;
	cout << "u3 = " << u3 <<endl;
	cout << endl;
	
	ex v1 = u1;
	ex u2v1 = integral(x, x0,x1, u2*v1) ;
	ex v1_normpow2 = integral(x, x0,x1, pow(v1,2)) ;

	ex v2 = (u2 - (u2v1/v1_normpow2)*v1).evalf();	
	ex v2_normpow2 =integral(x, x0,x1, pow(v2,2));

	ex u3v1 = integral(x, x0,x1, u3*v1) ;
	ex u3v2 = integral(x, x0,x1, u3*v2) ;
	ex v3 = u3 - (u3v1.evalf()/v1_normpow2.evalf())*v1 - (u3v2.evalf()/v2_normpow2.evalf())*v2;
	
	cout << "<u2,v1> = " << u2v1.evalf() << endl;
	cout << "<u3,v1> = " << u3v1.evalf() << endl;
	cout << "<u3,v2> = " << u3v2.evalf() << endl;
	cout << "\n||v1||^{2} = " << v1_normpow2.evalf() << endl;
	cout << "||v2||^{2} = " << v2_normpow2.evalf()  << endl;
	
	cout << "\nv1 = " << v1 <<endl;
	cout << "v2 = " << v2<<endl;
	cout << "v3 = " << v3 <<endl;

	Gnuplot gp;
	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,1000 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-1.5:3]\nset yrange [-1.5:6]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f1(x) = 1\n";
	gp << "f2(x) = x\n";
	gp << "f3(x) = x*x\n";
	gp << "g1(x) = 1\n";
	gp << "g2(x) = x\n";
	gp << "g3(x) = x*x - 0.333\n";
	gp << "set multiplot layout 2,1 title 'Gram-Schmidt Process and Legendre Polynomials'\n"; // multiplot
	gp << "plot f1(x) title 'u_{1} = 1'  lw 2 lc rgb 'dark-turquoise', f2(x) title 'u_{2} = x' lw 2 lc rgb 'forest-green',\
			f3(x) title 'u_{3} = x^{2}' lw 2 lc rgb 'spring-green'\n";
	gp << "plot g1(x) title 'v_{1} = 1'  lw 2 lc rgb 'green', g2(x) title 'v_{2} = x' lw 2 lc rgb 'forest-green',\
			g3(x) title 'v_{3} = x^{2} - 1/3' lw 2 lc rgb 'spring-green'\n";
	
	return 0;
}