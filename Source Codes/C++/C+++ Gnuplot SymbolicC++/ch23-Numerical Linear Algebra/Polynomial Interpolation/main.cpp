// g++ -o result main.cpp -lboost_iostreams

#include <iostream>
#include <bits/stdc++.h>
#include "gnuplot-iostream.h"

using namespace std;
 
#define M 10
const int N = 4;
 
// Function to print the matrix
void PrintMatrix(float a[][M], int n)
{
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j <= n; j++) 
		cout << a[i][j] << " ";
		cout << endl;
	}
}
 
// function to reduce matrix to reduced
// row echelon form.
int PerformOperation(float a[][M], int n)
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
 
// Function to print the desired result 
// if unique solutions exists, otherwise 
// prints no solution or infinite solutions 
// depending upon the input given.
void PrintResult(float a[][M], int n, int flag)
{
	cout << "The solution/s : ";

	if (flag == 2)     
	{
	cout << "Infinite Solutions Exists" << endl;    
	}
	else if (flag == 3)     
	{
	cout << "No Solution Exists" << endl;
	}
     
	// Printing the solution by dividing constants by
	// their respective diagonal elements
	else 
	{
	for (int i = 0; i < n; i++)         
	cout << "x(" << i  << ") = "<< a[i][n] / a[i][i] << ",  ";        
	}
}
 
// To check whether infinite solutions 
// exists or no solution exists
int CheckConsistency(float a[][M], int n, int flag)
{
	int i, j;
	float sum;

	// flag == 2 for infinite solution
	// flag == 3 for No solution
	flag = 3;
	for (i = 0; i < n; i++) 
	{
		sum = 0;
		for (j = 0; j < n; j++)        
			sum = sum + a[i][j];
		if (sum == a[i][j]) 
			flag = 2;        
	}
return flag;
}
 
// Driver code
int main()
{
	float x1 = 1;
	float x2 = 2;
	float x3 = 3;
	float x4 = 4;
	float y1 = 3;
	float y2 = -2;
	float y3 = -5;
	float y4 = 0;
	
	float a[M][M] = {{ 1, x1, x1*x1,x1*x1*x1, y1 }, 
	{ 1, x2, x2*x2, x2*x2*x2, y2 }, 
	{ 1, x3, x3*x3, x3*x3*x3, y3 },
	{ 1, x4, x4*x4, x4*x4*x4, y4 }};

	// Printing matrix A
	cout << "Matrix A : "  << endl;
	int n1 = 4;
	for (int i = 0; i < n1; ++i)
	{
		for (int j = 0; j < n1; ++j) 
		{	
			cout << a[i][j]<< ' ';	
		}
		cout << endl;
	}	

	// Order of Matrix(n)
	int n = 4, flag = 0;

	// Performing Matrix transformation
	flag = PerformOperation(a, n);
     
	if (flag == 1)     
	flag = CheckConsistency(a, n, flag);    
 
	// Printing Final Matrix
	cout << endl;
	cout << "Final Augmented Matrix is : " << endl;
	PrintMatrix(a, n);
	cout << endl;

	// Printing Solutions(if exist)
	cout << "Solutions for Matrix A : " << endl;
	PrintResult(a,n, flag);
	cout << endl;	

	// Plot the points and the polynomial interpolation with Gnuplot
	std::vector<std::pair<double, double>> xy_pts;
	float B[N];
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			B[i] = a[i][n] / a[i][i] ;
		}
		cout << B[i] << endl;
		xy_pts.emplace_back(i, B[i]); 
	}	
	Gnuplot gp;        

    	gp << "set xrange [-1:5]\n";
    	gp << "f(x) = a + b*x + c*x*x + d*x*x*x\n";
    	gp << "fit f(x) '-' via a,b,c,d\n";
    	gp.send1d(xy_pts);
    	gp << "plot '-' with points title 'input', f(x) with lines title 'fit'\n";
    	gp.send1d(xy_pts);

	return 0;
}