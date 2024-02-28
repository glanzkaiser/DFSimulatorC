// g++ -o result main.cpp -larmadillo
// Merci beaucoup Freya..
// C++ program to find the solution of system of linear equations

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

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
 
// function to reduce matrix to reduced row echelon form.
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
		        // Converting Matrix to reduced row echelon form(diagonal matrix)
			float pro = a[j][i] / a[i][i]; 
			for (k = 0; k <= n; k++)                 
				a[j][k] = a[j][k] - (a[i][k]) * pro;                
			}
		}
	}
	return flag;
}
 
int PerformOperation2(float a[][M], int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pivot = 0;

    // Performing elementary operations again
	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 0 && a[i-1][j] !=0) 
			{				
				float pivot = a[i-1][j] / a[i][j]; 
				for (k = 0; k <= n; k++)                
				{ 
					a[i][k] = a[i][k] - (a[i-1][k] * pivot);  
				}
				j = n-1;
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
 
// To check whether infinite solutions exists or no solution exists
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
int main(int argc, char** argv)
{
	mat A;
	A.load("matrixA.txt");
	mat B;
	B.load("vectorB.txt");
	mat X;
	X = solve(A,B,solve_opts::force_approx); 
	
	cout <<"Matrix A (Coefficient Matrix):" << "\n" << A <<endl;
	cout <<"Vector B (Nonhomogeneous System):" << "\n" << B <<endl;
	cout <<"Solution:" << "\n" << X <<endl;	

	float b[M][M] = {{ 1,-3, 4,-2,5,4,0 }, 
	{ 2,-6,9,-1,8,2,0 }, 
	{ 2,-6,9,-1,9,7,0 }, 
	{ -1,3,-4,2,-5,-4,0 }};

	cout << "Homogeneous System : "  << endl;
	int r = 4;
	int c = 7;
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j) 
		{	
			cout <<setw(6) << b[i][j]<< "\t";	
		}
		cout << endl;
	}	

	// Order of Matrix(n)
	int n = 7, flag = 0;

	// Performing Matrix transformation
	flag = PerformOperation(b, n);
     
	if (flag == 1)     
	flag = CheckConsistency(b, n, flag);    
 
	// Printing Final Matrix
	cout << endl;
	cout << "Gaussian Elimination for Homogeneous System: " << endl;
	PrintMatrix(b);
	cout << endl;

	// Printing Solutions for homogeneous system
	PrintResult(b,n, flag);
	cout << endl;	

	cout << "Row Echelon Form for Homogeneous System : " << endl;
	flag = PerformOperation2(b, n);
	PrintMatrix(b);

	cout << "Basis for Column Space of Matrix A: " << endl;

	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j) 
		{	
			if ( b[i][j] !=0 )
			{
				cout << "A.col(" << j << ") : " << endl << A.col(j) << endl;
				j = c-1;
			}	
		}
		cout << endl;
	}	
}