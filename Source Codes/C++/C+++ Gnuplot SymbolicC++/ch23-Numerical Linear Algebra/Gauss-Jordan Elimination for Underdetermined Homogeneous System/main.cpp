// g++ -o result main.cpp

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
 
#define M 10
 
// Function to print the matrix
void PrintMatrix(float a[][M])
{
	int r = 4;
	int c = 7;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << a[i][j] << "\t";
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
	float a[M][M] = {{ 1,-3, 1,0,0,0,0 }, 
	{ -4,8,0,1,0,0,0 }, 
	{ 2,-4,-0,0,1,0,0 }, 
	{ -3,6,0,0,0,1,0 }};

	// Printing matrix A
	cout << "Matrix A : "  << endl;
	int r = 4;
	int c = 7;
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j) 
		{	
			cout <<setw(6) << a[i][j]<< "\t";	
		}
		cout << endl;
	}	

	// Order of Matrix(n)
	int n = 7, flag = 0;

	// Performing Matrix transformation
	flag = PerformOperation(a, n);
     
	if (flag == 1)     
	flag = CheckConsistency(a, n, flag);    
 
	// Printing Final Matrix
	cout << endl;
	cout << "Final Augmented Matrix is : " << endl;
	PrintMatrix(a);
	cout << endl;

	// Printing Solutions(if exist)
	cout << "Solutions for Matrix A : " << endl;
	PrintResult(a,n, flag);
	cout << endl;	

	return 0;
}