// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
#include <armadillo>

using namespace std;
using namespace arma;

#define R 2 // number of rows
#define C 2 // number of columns

double division(double x, double y)
{
	return x/y;
}

// Driver program
int main()
{
	Symbolic x("x"), y("y");
	Symbolic f, fx, fy, fxx, fxy, fyy;

	f = division(1,3)*(x*x*x) + x*(y*y) - 8*x*y + 3;
	fx = df(f, x);
	fy = df(f, y);
	fxx = df(fx, x);
	fxy = df(fx, y);
	fyy = df(fy, y);
	
	cout << "f : " << f << endl;
	cout << "fx : " << fx << endl;
	cout << "fy : " << fy << endl;
	cout << "fxx : " << fxx << endl;
   	cout << "fxy : " << fxy << endl;
   	cout << "fyy : " << fyy << endl;
   	
 	// Construct a symbolic matrix of size 2 X 2
	Matrix<Symbolic> H_mat(2,2);
	H_mat[0][0] = fxx;	H_mat[0][1] = fxy;		
	H_mat[1][0] = fxy;	H_mat[1][1] = fyy;
	cout << "\nH(x,y):\n" << H_mat <<endl;
	cout << "det(H):\n" << H_mat.determinant() <<endl;
	//cout << "inv(B):\n" << B_mat.inverse() <<endl;
	cout << endl;
	
	// To find critical point set fx and fy equal to zero and solve the equations
	cout << "Computing the critical points: set fx =0 and fy=0, then solve the equations.\n" << endl;	
	cout << "Determine the critical codes with C++ codes with GSL.\n" << endl;	
	/*
	Equation e1 = fx == 0;
    	Equation e2 = fy == 0;

	Equations eqs = {e1, e2};
	list<Symbolic> symbs = {x, y};
	list<Equations> sols = solve(eqs, symbs);

	Symbolic x_sol, y_sol;
	int i = 1;
	for( auto iter1 = sols.begin(); iter1 != sols.end(); iter1++)
	{
		x_sol = x.subst((*(*iter1).begin()));
		y_sol = y.subst((*(--(*iter1).end())));
		cout << "p" << i << " = {" << x_sol << ", " << y_sol << "};" << endl;
		cout << "fx (x=" << x_sol << "):" << fx[x==x_sol]  << endl;
		cout << "fy (x=" << x_sol << "):" << fy[x==x_sol] << endl;
		cout << "fx (y=" << y_sol << "):"  << fx[y==y_sol] << endl;
		cout << "fy (y=" << y_sol << "):"  << fy[y==y_sol] << endl;
		cout << endl;
		i++;
	}
	*/
	cout << endl;	

	// Compute the critical points with GSL first in the first C++ codes then you can input the critical points here
	mat H1(R,C);
	mat H2(R,C);
	mat H3(R,C);
	mat H4(R,C);
	
	H1[0] = fxx[x==0, y==0];
	H1[1] = fxy[x==0, y==0];
	H1[2] = fxy[x==0, y==0];
	H1[3] = fyy[x==0, y==0];
	H2[0] = fxx[x==0, y==8];
	H2[1] = fxy[x==0, y==8];
	H2[2] = fxy[x==0, y==8];
	H2[3] = fyy[x==0, y==8];
	H3[0] = fxx[x==4, y==4];
	H3[1] = fxy[x==4, y==4];
	H3[2] = fxy[x==4, y==4];
	H3[3] = fyy[x==4, y==4];
	H4[0] = fxx[x==-4, y==4];
	H4[1] = fxy[x==-4, y==4];
	H4[2] = fxy[x==-4, y==4];
	H4[3] = fyy[x==-4, y==4];

	cx_mat eigvec;
	cx_vec eigval;

	mat I(R,C,fill::eye);
	cout <<"Matrix H with critical point (0,0):" << "\n" << H1 <<endl;
	cout <<"Matrix H with critical point (0,8):" << "\n" << H2 <<endl;
	cout <<"Matrix H with critical point (4,4):" << "\n" << H3 <<endl;
	cout <<"Matrix H with critical point (-4,4):" << "\n" << H4 <<endl;
	
	eig_gen(eigval, eigvec, H1); // Eigen decomposition of dense general square matrix
	cout << "Eigenvalues for matrix H with critical point (0,0):" << endl;

	int n = 2;
	for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}
	if (real(eigval[0]) < 0 && real(eigval[1]) < 0 )
	{
		cout << "This is a relative maximum" << endl;
	}
	else if (real(eigval[0]) > 0 && real(eigval[1]) > 0 )
	{
		cout << "This is a relative minimum" << endl;
	}
	else if (real(eigval[0]) < 0 && real(eigval[1]) > 0 )
	{
		cout << "This is a saddle point" << endl;
	}
	else if (real(eigval[0]) > 0 && real(eigval[1]) < 0 )
	{
		cout << "This is a saddle point" << endl;
	}

	eig_gen(eigval, eigvec, H2); // Eigen decomposition of dense general square matrix
	cout << endl;	
	cout << "\nEigenvalues for matrix H with critical point (0,8):" << endl;

	for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}
	if (real(eigval[0]) < 0 && real(eigval[1]) < 0 )
	{
		cout << "This is a relative maximum" << endl;
	}
	else if (real(eigval[0]) > 0 && real(eigval[1]) > 0 )
	{
		cout << "This is a relative minimum" << endl;
	}
	else if (real(eigval[0]) < 0 && real(eigval[1]) > 0 )
	{
		cout << "This is a saddle point" << endl;
	}
	else if (real(eigval[0]) > 0 && real(eigval[1]) < 0 )
	{
		cout << "This is a saddle point" << endl;
	}

	eig_gen(eigval, eigvec, H3); // Eigen decomposition of dense general square matrix
	cout << endl;	
	cout << "\nEigenvalues for matrix H with critical point (4,4):" << endl;

	for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}
	if (real(eigval[0]) < 0 && real(eigval[1]) < 0 )
	{
		cout << "This is a relative maximum" << endl;
	}
	else if (real(eigval[0]) > 0 && real(eigval[1]) > 0 )
	{
		cout << "This is a relative minimum" << endl;
	}
	else if (real(eigval[0]) < 0 && real(eigval[1]) > 0 )
	{
		cout << "This is a saddle point" << endl;
	}
	else if (real(eigval[0]) > 0 && real(eigval[1]) < 0 )
	{
		cout << "This is a saddle point" << endl;
	}

	eig_gen(eigval, eigvec, H4); // Eigen decomposition of dense general square matrix
	cout << endl;	
	cout << "\nEigenvalues for matrix H with critical point (-4,4):" << endl;

	for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " <<real(eigval[i-1]) << " + " << imag(eigval[i-1]) << "i" << endl;
	}
	if (real(eigval[0]) < 0 && real(eigval[1]) < 0 )
	{
		cout << "This is a relative maximum" << endl;
	}
	else if (real(eigval[0]) > 0 && real(eigval[1]) > 0 )
	{
		cout << "This is a relative minimum" << endl;
	}
	else if (real(eigval[0]) < 0 && real(eigval[1]) > 0 )
	{
		cout << "This is a saddle point" << endl;
	}
	else if (real(eigval[0]) > 0 && real(eigval[1]) < 0 )
	{
		cout << "This is a saddle point" << endl;
	}

	/*
	cout << "\nfx (x=0,y=0):\n" << fx[x==0, y==0] <<endl;
	cout << "fx (x=0,y=8):\n" << fx[x==0, y==8] <<endl;
	cout << "fx (x=4,y=4):\n" << fx[x==4, y==4] <<endl;
	cout << "fx (x=-4,y=4):\n" << fx[x==-4, y==4] <<endl;
	cout << "fy (x=0, y=0):\n" << fy[x==0, y==0] <<endl;
	cout << "fy (x=0, y=8):\n" << fy[x==0, y==8] <<endl;
	cout << "fy (x=4, y=4):\n" << fy[x==4, y==4] <<endl;
	cout << "fy (x=-4, y=4):\n" << fy[x==-4, y==4] <<endl;
	*/
	return 0;
}