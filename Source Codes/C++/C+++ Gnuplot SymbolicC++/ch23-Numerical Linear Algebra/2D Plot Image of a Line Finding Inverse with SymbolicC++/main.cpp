// g++ -o result main.cpp -lboost_iostreams -lsymbolicc++
// Merci beaucoup Freya et Sentinel
// Kaing bla kaing.. Hasta la meo -Bludut

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
#include "gnuplot-iostream.h"

using namespace std;

#define R 2 // number of rows
#define C 2 // number of columns

// Driver program
int main()
{
	Symbolic w1("w1"); 
	Symbolic w2("w2");
	Symbolic x("x"); 
	Symbolic y("y");
	Symbolic xm("xm"); 
	Symbolic ym("ym");
		
	Matrix<Symbolic> X(R,1);
	Matrix<Symbolic> W(R,1);
	W[0][0] = xm;	
	W[1][0] = ym;

 	// Construct a symbolic matrix of size R X C
	Matrix<Symbolic> A_mat(R,C);
	A_mat[0][0] = 3;		A_mat[0][1] = 1;	
	A_mat[1][0] = 2;		A_mat[1][1] = 1;	

	cout << "The line equation:\n" << "y = 2x+1" <<endl;	
	cout << endl;
	cout << "A:\n" << A_mat <<endl;
	cout << endl;
	Matrix<Symbolic> AI(R,C);
	AI = A_mat.inverse();
	
	cout << "A^{-1}:\n" << AI <<endl;	
	cout << endl;

	cout << "A^{-1} * [xm ym] :\n" << AI*W <<endl;
	
	X = (AI*W);
	// X[0] = x, X[1] = y
	cout << "y = 2x + 1 : \n y - 2x - 1 = 0 \n 0 =" << X[1] - Symbolic(2)*X[0] - Symbolic(1) <<endl;
	
	Gnuplot gp;
	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1.5:2]\nset yrange [-1.5:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	// Put the degree in the equation for f(x) = (theta*DEGTORAD )* x
	gp << "f(x) =2*x + 1 \n";
	gp << "g(x) =(0.8)*x + (0.2) \n";	
	gp << "plot f(x) title 'f(x) = original line' lc 'green', g(x) title 'g(x) = image of line f(x)'  dashtype 3\n";

	return 0;
}