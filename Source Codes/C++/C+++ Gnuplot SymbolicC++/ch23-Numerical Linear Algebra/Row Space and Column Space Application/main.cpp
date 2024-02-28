// g++ -o result main.cpp
// Merci beaucoup Freya..
// C++ program manipulate matrix, row space, and column space

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

const int N = 4;
const int R = 4; // number of rows
const int C = 4; // number of column

#define MN 4
 
// Function to print the matrix
void PrintMatrix(float a[][MN])
{
	int r = 4;
	int c = 4;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << a[i][j] << "\t";
		cout << endl;
	}
}

int PerformOperation(float a[][MN], int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pro = 0;

    // Performing elementary operations
	for (i = 0; i < n; i++)
	{
		if (a[i][i] == 0) 
		{
			c = 1;
			while ((i + c) < n && a[i + c][i] == 0) 
			c++;            
			if ((i + c) == n) 
			{
				flag = 1;
				break;
			}
			for (j = i, k = 0; k <= n; k++) 
			swap(a[j][k], a[j+c][k]);
		}
		
		for (j = 0; j < n; j++) 
		{
		    // Excluding all i == j
		if (i != j) 
			{                 
		        // Converting Matrix to reduced row
		        // echelon form(diagonal matrix)
			float pro = a[j][i] / a[i][i]; 
			for (k = 0; k <= n; k++)                 
				a[j][k] = a[j][k] - (a[i][k]) * pro;                
			}
		}
	}
	return flag;
}

float* vecv() {
	static float v[N];
	std::fstream in("vectorV.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			v[i] =vectortiles[i];	
	}	
	return v;
}

float* vecw() {
	static float w[N];
	std::fstream in("vectorW.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			w[i] =vectortiles[i];	
	}	
	return w;
}

float* vecx() {
	static float x[N];
	std::fstream in("vectorX.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			x[i] =vectortiles[i];	
	}	
	return x;
}

float* vecy() {
	static float y[N];
	std::fstream in("vectorY.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			y[i] =vectortiles[i];	
	}	
	return y;
}

// Driver code
int main(int argc, char** argv)
{
	float* ptrvecv;
	ptrvecv = vecv();
	float* ptrvecw;
	ptrvecw = vecw();
	float* ptrvecx;
	ptrvecx = vecx();
	float* ptrvecy;
	ptrvecy = vecy();
	
	arma::mat A(R,C,fill::zeros); //declare matrix A with size of R X C all have 0 entries with Armadillo.
	arma::mat A_transpose(C,R,fill::zeros); //declare matrix A_transpose with size of C X R all have 0 entries with Armadillo.
	arma::mat A_gauss(R,C,fill::zeros); //declare matrix A after performing Gaussian elimination with size of R X C 

	float a[R][C] = {};
	for (int i = 0; i < R; ++i)
	{
		for(int j = 0; j<C; ++j)
		{
			if (j==0)
			{
				a[i][j] = ptrvecv[i];
			}
			if (j==1)
			{
				a[i][j] = ptrvecw[i];
			}
			if (j==2)
			{
				a[i][j] = ptrvecx[i];
			}
			if (j==3)
			{
				a[i][j] = ptrvecy[i];
			}
		}			
	}	

	// Fill matrix A from Armadillo with matrix a[R][C] from loading textfile of vectors v,w,x,y
	for (int i = 0; i < R; ++i)
	{
		for(int j = 0; j<C; ++j)
		{
			A[i+j*R] = a[i][j];
		}			
	}	
	
	A_transpose = A.t();
	
	A.print("A:");
  	cout << endl;
	cout <<"A (in simpler form): " << endl;
	PrintMatrix(a);
	cout << endl;
	A_transpose.print("A^T:");
  	cout << endl;
	cout << endl;

	int flag = 0;

	// Performing Matrix transformation
	PerformOperation(a, N);
	for (int i = 0; i < R; ++i)
	{
		for(int j = 0; j<C; ++j)
		{
			A_gauss[i+j*R] = a[i][j];
		}			
	}	
	A_gauss.print("A in row echelon form:");
  	cout << endl;

	// determinant and inverse from Armadillo
	cout << "det(A^T * A): " << det(A_transpose*A) << endl;
	cout << endl;
	cout << "inv(A): " << endl << arma::inv(A) << endl;

	cout <<endl;
}