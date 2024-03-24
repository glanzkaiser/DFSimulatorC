// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
using namespace std;

#define R 3 // number of rows
#define C 3 // number of columns

// Driver program
int main()
{
	Symbolic a("a");
	Symbolic b("b");
	Symbolic c("c");
	Symbolic θ("θ");
	
 	// Construct a symbolic matrix of size 3 X 3
	Matrix<Symbolic> B_mat(3,3);
	B_mat[0][0] = a*a*(1-cos(θ)) + cos(θ);	B_mat[0][1] = a*b*(1-cos(θ)) - c*sin(θ);	B_mat[0][2] = a*c*(1-cos(θ)) + b*sin(θ);	
	B_mat[1][0] = a*b*(1-cos(θ)) + c*sin(θ);	B_mat[1][1] = b*b*(1-cos(θ)) + cos(θ);	B_mat[1][2] = b*c*(1-cos(θ)) - a*sin(θ);	
	B_mat[2][0] = a*c*(1-cos(θ)) - b*sin(θ);	B_mat[2][1] = b*c*(1-cos(θ)) + a*sin(θ);	B_mat[2][2] = c*c*(1-cos(θ)) + cos(θ);	

	cout << endl;
	cout << "Standard matrix for counterclockwise rotation"  <<endl;
	cout << "through an angle θ in 3 dimensional space:"  <<endl;
	cout << "B:\n" << B_mat <<endl;
	cout << endl;
	
	Symbolic traceB = 0;
	// Operation to compute the trace of a matrix 
	for (int i = 0; i < R; i++)
	{
		traceB += B_mat[i][i];;
	}
	cout << "tr(B): " << traceB << endl;
	cout << endl;
	Symbolic x = (traceB-1)/2;
	cout << "(tr(B) - 1 ) / 2: \n" << x << endl;
	cout << endl;
	cout << "(tr(B) - 1 ) / 2 with a=0, b=0, c=1: " << x[a ==0, b==0, c==1] << endl;
	
	// Compute determinant with manual Cofactor expansion along the first row
	Symbolic b11 = B_mat[0][0];
	Symbolic b12 = B_mat[0][1];
	Symbolic b13 = B_mat[0][2];
	Symbolic C11 = B_mat[1][1]*B_mat[2][2] - B_mat[1][2]*B_mat[2][1];
	Symbolic C12 = B_mat[1][0]*B_mat[2][2] - B_mat[1][2]*B_mat[2][0];
	Symbolic C13 = B_mat[1][0]*B_mat[2][1] - B_mat[1][1]*B_mat[2][0];
	cout << endl;

	Symbolic detB = b11*C11 - b12*C12 + b13*C13;
	cout << "det(B) in symbolic term:\n" << detB <<endl;
	cout << endl;
	cout << "det(B) with a=0, b=0, c=1:\n" << detB[ a == 0, b == 0, c ==1 ] << " = 1"<< endl;
	cout << endl;

	return 0;
}