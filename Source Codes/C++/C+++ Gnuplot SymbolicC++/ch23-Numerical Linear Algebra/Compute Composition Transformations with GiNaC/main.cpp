// g++ -o result main.cpp -lginac -lcln -larmadillo
// Merci beaucoup Freya.. et Sentinel..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <ginac/ginac.h>
#include <vector>
#include <armadillo>

using namespace std;
using namespace GiNaC;
using namespace arma;

// Linear operator T_{1}: P_2 -> P_2
// Linear operator T_{2}: P_2 -> P_2
// Driver code
int main(int argc, char** argv)
{
	// GiNac codes starts here
	cout << " ******************************************************************** " << endl;
	cout << " ****************************GiNaC Codes***************************** " << endl;
	cout << " ******************************************************************** " << endl;
	
	Digits = 5; // define maximum decimal digits
	symbol x("x"), xpow2("x^2"), a("a"), b("b"), x1("x1"), x2("x2");
	
	ex px = 3*x - 5;
	
	cout << "\n T(1) = " << 1 << endl;
	cout << "\n T(x) = " << px << endl;
	cout << "\n T(x^2) = " << pow(px,2).expand() << endl;
	
	matrix T2col1 = {{1},{0},{0}};
	matrix T2col2 = {{-5},{3},{0}};
	matrix T2col3 = {{25},{-30},{9}};

	matrix T1col1 = {{0},{1},{0}};
	matrix T1col2 = {{0},{0},{1}};
			
	matrix T2Bnew(3,3);
	T2Bnew(0,0) = T2col1[0];
	T2Bnew(0,1) = T2col2[0];
	T2Bnew(0,2) = T2col3[0];
	T2Bnew(1,0) = T2col1[1];
	T2Bnew(1,1) = T2col2[1];
	T2Bnew(1,2) = T2col3[1];
	T2Bnew(2,0) = T2col1[2];
	T2Bnew(2,1) = T2col2[2];
	T2Bnew(2,2) = T2col3[2];

	matrix T1BBnew(3,2);
	T1BBnew(0,0) = T1col1[0];
	T1BBnew(0,1) = T1col2[0];
	T1BBnew(1,0) = T1col1[1];
	T1BBnew(1,1) = T1col2[1];
	T1BBnew(2,0) = T1col1[2];
	T1BBnew(2,1) = T1col2[2];
	
	cout << "\n [T_{2}]_{B'} = " << T2Bnew << endl;
	cout << "\n [T_{1}]_{B',B} = " << T1BBnew << endl;
	cout << "\n [T_{2} o T_{1}]_{B', B} = " << (T2Bnew*T1BBnew).evalm() << endl;
	
	cout << " ******************************************************************** " << endl;
	cout << " ****************************Armadillo Codes************************** " << endl;
	cout << " ******************************************************************** " << endl;
	arma::mat A(3,3, fill::zeros);
	int N = 3;
//	A[0+0*N] = T2Bnew(0)(0);	A[1+0*N] = T2Bnew(0)(1);	A[2+0*N] = T2Bnew(0)(2);
//	A[0+1*N] = T2Bnew(1)(0);	A[1+1*N] = T2Bnew(1)(1);	A[2+1*N] = T2Bnew(1)(2);
//	A[0+2*N] = T2Bnew(2)(0);	A[1+2*N] = T2Bnew(2)(1);	A[2+2*N] = T2Bnew(2)(2);
	
	float matrixA[N][N] = {};
/*
	// Cannot convert GiNaC::ex to float in initialization
	float a00 = evalf(T2col1[0]);		float a10 = evalf(T2col1[1]);		float a20 = evalf(T2col1[2]);
	float a01 = evalf(T2col2[0]);		float a11 = evalf(T2col2[1]);		float a21 = evalf(T2col2[2]);
	float a02 = evalf(T2col3[0]);		float a12 = evalf(T2col3[1]);		float a22 = evalf(T2col3[2]);
	
	matrixA[0][0] = a00;
	matrixA[0][1] = a01;
	matrixA[0][2] = a02;
	matrixA[1][0] = a10;
	matrixA[1][1] = a11;
	matrixA[1][2] = a12;
	matrixA[2][0] = a20;
	matrixA[2][1] = a21;
	matrixA[2][2] = a22;

	for (int i = 0; i < N; ++i)
		{
			for(int j = 0; j<N; ++j)
			{
				A[i+j*N] = matrixA[i][j];
			}			
		}
*/		
	numeric f(2,3);
	cout << f << endl;	
	// to compute f with floating term do this:
//	cout << f.evalf() << endl;	
	
	cout << "ginac : " << T2Bnew(2,2)  << endl;	
	cout << "A =" << A <<endl;
	return 0;
}