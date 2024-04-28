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
	Symbolic w1("w1"); 
	Symbolic w2("w2");
	Symbolic x("x"); 
	Symbolic y("y");
	Symbolic xm("xm"); 
	Symbolic ym("ym");
		
	Matrix<Symbolic> X(R,1);
	Matrix<Symbolic> XB(R,1);
	Matrix<Symbolic> XC(R,1);
	Matrix<Symbolic> XD(R,1);
	Matrix<Symbolic> XE(R,1);
	Matrix<Symbolic> W(R,1);
	W[0][0] = xm;	
	W[1][0] = ym;

 	// Construct a symbolic matrix of size R X C
	Matrix<Symbolic> A_mat(R,C);
	A_mat[0][0] = 1;		A_mat[0][1] = 3;	
	A_mat[1][0] = 0;		A_mat[1][1] = 1;	

	Matrix<Symbolic> B_mat(R,C);
	B_mat[0][0] = 1;		B_mat[0][1] = 0;	
	B_mat[1][0] = 0;		B_mat[1][1] = 0.5;	

	Matrix<Symbolic> C_mat(R,C);
	C_mat[0][0] = 0;		C_mat[0][1] = 1;	
	C_mat[1][0] = 1;		C_mat[1][1] = 0;	

	Matrix<Symbolic> D_mat(R,C);
	D_mat[0][0] = -1;		D_mat[0][1] = 0;	
	D_mat[1][0] = 0;		D_mat[1][1] = 1;	

	Matrix<Symbolic> E_mat(R,C);
	E_mat[0][0] = cos(theta*DEGTORAD);		E_mat[0][1] = - sin(theta*DEGTORAD);	
	E_mat[1][0] = sin(theta*DEGTORAD);		E_mat[1][1] = cos(theta*DEGTORAD);	

	cout << "The line equation:\n" << "y = 2x" <<endl;	
	cout << endl;
	cout << "********************************************************************" <<endl;	
	cout << "Shear with factor 3 in the x-direction" <<endl;	
	cout << "********************************************************************" <<endl;	
	cout << "A:\n" << A_mat <<endl;
	cout << endl;
	Matrix<Symbolic> AI(R,C);
	AI = A_mat.inverse();
	
	cout << "A^{-1}:\n" << AI <<endl;	
	cout << endl;

	cout << "A^{-1} * [xm ym] :\n" << AI*W <<endl;
	
	X = (AI*W);
	// X[0] = x, X[1] = y
	cout << "y = 2x : \n y - 2x = 0 \n 0 =" << X[1] - Symbolic(2)*X[0] <<endl;
	
	cout << "********************************************************************" <<endl;	
	cout << "Compression with factor 0.5 in the y-direction" <<endl;	
	cout << "********************************************************************" <<endl;	
	
	cout << "B:\n" << B_mat <<endl;
	cout << endl;
	Matrix<Symbolic> BI(R,C);
	BI = B_mat.inverse();
	
	cout << "B^{-1}:\n" << BI <<endl;	
	cout << endl;

	cout << "B^{-1} * [xm ym] :\n" << BI*W <<endl;
	
	XB = (BI*W);
	// X[0] = x, X[1] = y
	cout << "y = 2x : \n y - 2x = 0 \n 0 =" << XB[1] - Symbolic(2)*XB[0] <<endl;

	cout << "********************************************************************" <<endl;	
	cout << "Reflection about the line y=x" <<endl;	
	cout << "********************************************************************" <<endl;	
	
	cout << "C:\n" << C_mat <<endl;
	cout << endl;
	Matrix<Symbolic> CI(R,C);
	CI = C_mat.inverse();
	
	cout << "C^{-1}:\n" << CI <<endl;	
	cout << endl;

	cout << "C^{-1} * [xm ym] :\n" << CI*W <<endl;
	
	XC = (CI*W);
	// X[0] = x, X[1] = y
	cout << "y = 2x : \n y - 2x = 0 \n 0 =" << XC[1] - Symbolic(2)*XC[0] <<endl;

	cout << "********************************************************************" <<endl;	
	cout << "Reflection about the y-axis" <<endl;	
	cout << "********************************************************************" <<endl;	
	
	cout << "D:\n" << D_mat <<endl;
	cout << endl;
	Matrix<Symbolic> DI(R,C);
	DI = D_mat.inverse();
	
	cout << "D^{-1}:\n" << DI <<endl;	
	cout << endl;

	cout << "D^{-1} * [xm ym] :\n" << DI*W <<endl;
	
	XD = (DI*W);
	// X[0] = x, X[1] = y
	cout << "y = 2x : \n y - 2x = 0 \n 0 =" << XD[1] - Symbolic(2)*XD[0] <<endl;

	cout << "********************************************************************" <<endl;	
	cout << "Counterclocwise rotation through an angle 60 degree" <<endl;	
	cout << "********************************************************************" <<endl;	
	
	cout << "E:\n" << E_mat <<endl;
	cout << endl;
	Matrix<Symbolic> EI(R,C);
	EI = E_mat.inverse();
	
	cout << "E^{-1}:\n" << EI <<endl;	
	cout << endl;

	cout << "E^{-1} * [xm ym] :\n" << EI*W <<endl;
	
	XE = (EI*W);
	// X[0] = x, X[1] = y
	cout << "y = 2x : \n y - 2x = 0 \n 0 =" << XE[1] - Symbolic(2)*XE[0] <<endl;

	Gnuplot gp;
	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1.5:2]\nset yrange [-1.5:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	// Put the degree in the equation for f(x) = (theta*DEGTORAD )* x
	gp << "f(x) = 2*x \n";
	gp << "g(x) = (0.2857)*x  \n";	
	gp << "h(x) = x \n";
	gp << "j(x) = 0.5*x \n";
	gp << "k(x) = -2*x \n";
	gp << "l(x) = -1.514573*x \n";
	
	gp << "plot f(x) title 'original line' lc 'green', g(x) title 'with shear of factor 3 in the x-direction'  dashtype 3, h(x) title 'with compression of factor 1/2 in the y-direction'  dashtype 6, j(x) title 'with reflection about the line y=x'  lc 'red', k(x) title 'with reflection about the y-axis'  lc 'blue', l(x) title 'with counterclockwise rotation of 60 degree'  lc 'orange'\n";

	return 0;
}