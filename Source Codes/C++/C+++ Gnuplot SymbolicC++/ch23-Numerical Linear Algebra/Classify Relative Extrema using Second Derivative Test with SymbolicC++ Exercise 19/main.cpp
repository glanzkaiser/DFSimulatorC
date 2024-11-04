// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>

using namespace std;

#define R 2 // number of rows
#define C 2 // number of columns

double division(double x, double y)
{
	return x/y;
}

// Thanks Sentinel for this
Symbolic power(Symbolic x, double n)
{
	Symbolic a = x;
	for (int i = 1; i <n; i++)
	{
		x = x * a;
	}
	return x;
}

// Driver program
int main()
{
	Symbolic x("x"), y("y");
	Symbolic f, fx, fy, fxx, fxy, fyy;
	Symbolic g, gx, gy, gxx, gxy, gyy;

	f = (x*x*x*x) + (y*y*y*y);
	fx = df(f, x);
	fy = df(f, y);
	fxx = df(fx, x);
	fxy = df(fx, y);
	fyy = df(fy, y);
	g = (x^4) - power(y,4);
	gx = df(g, x);
	gy = df(g, y);
	gxx = df(gx, x);
	gxy = df(gx, y);
	gyy = df(gy, y);
	
	cout << "f : " << f << endl;
	cout << "fx : " << fx << endl;
	cout << "fy : " << fy << endl;
	cout << "fxx : " << fxx << endl;
   	cout << "fxy : " << fxy << endl;
   	cout << "fyy : " << fyy << endl;
   	
 	cout << "\ng : " << g << endl;
	cout << "gx : " << gx << endl;
	cout << "gy : " << gy << endl;
	cout << "gxx : " << gxx << endl;
   	cout << "gxy : " << gxy << endl;
   	cout << "gyy : " << gyy << endl;
   	
	// Construct a symbolic matrix of size 2 X 2
	Matrix<Symbolic> Hf_mat(2,2);
	Hf_mat[0][0] = fxx;	Hf_mat[0][1] = fxy;		
	Hf_mat[1][0] = fxy;	Hf_mat[1][1] = fyy;
	cout << "\nH(x,y) for f:\n" << Hf_mat <<endl;
	Matrix<Symbolic> Hg_mat(2,2);
	Hg_mat[0][0] = gxx;	Hf_mat[0][1] = gxy;		
	Hg_mat[1][0] = gxy;	Hf_mat[1][1] = gyy;
	cout << "\nH(x,y) for g:\n" << Hg_mat <<endl;
	cout << endl;
	
	// To find critical point set fx and fy equal to zero and solve the equations
	cout << "fxx * fyy - fxy^2 = " << fxx * fyy - fxy * fxy << endl;	
	cout << "gxx * gyy - gxy^2 = " << gxx * gyy - gxy * gxy << endl;	
	cout << "\nThe second derivative test at (0,0).\n" << endl;	
	cout << "fxx * fyy - fxy^2 = " << fxx[x==0,y==0] * fyy[x==0,y==0] - fxy[x==0,y==0]*fxy[x==0,y==0] << endl;	
	cout << "gxx * gyy - gxy^2 = " << gxx[x==0,y==0] * gyy[x==0,y==0] - gxy[x==0,y==0]*gxy[x==0,y==0] << endl;	
	
	cout << endl;	

	return 0;
}