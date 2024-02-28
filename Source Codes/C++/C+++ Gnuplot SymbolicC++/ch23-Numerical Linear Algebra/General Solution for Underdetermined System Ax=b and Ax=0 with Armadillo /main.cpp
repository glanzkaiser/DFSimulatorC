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

#define C_Mat 5 // Define the number of column for the linear system Ax=b
#define R_Mat 4 // Define the number of row for the linear system Ax=b
#define C_MatA 4 // Define the number of column for the matrix A
#define R_MatA 4 // Define the number of row for the matrix A

// Function to print the matrix 
void PrintMatrix(float a[][C_Mat])
{
	int r = R_Mat;
	int c = C_Mat;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << setprecision(4) << a[i][j] << "\t";
		cout << endl;
	}
}

// function to reduce matrix to reduced row echelon form.
int PerformOperation(float a[][C_Mat], int r, int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pro = 0;

    // Performing elementary operations
	for (i = 0; i < r; i++)
	{
		if (a[i][i] == 0) 
		{
			c = 1;
			while ((i + c) < r && a[i + c][i] == 0) 
			c++;            
			if ((i + c) == r) 
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
 
// Function to print the desired result if unique solutions exists, otherwise 
// prints no solution or infinite solutions depending upon the input given.
void PrintResult(float a[][C_Mat], int r, int flag)
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
	for (int i = 0; i < r; i++)         
	cout << "x(" << i  << ") = "<< a[i][r] / a[i][i] << ",  ";        
	}
}
 
// To check whether infinite solutions exists or no solution exists
int CheckConsistency(float a[][C_Mat], int r, int n, int flag)
{
	int i, j;
	float sum;

	// flag == 2 for infinite solution
	// flag == 3 for No solution
	flag = 3;
	for (i = 0; i < r; i++) 
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
	arma::mat A(R_MatA,C_MatA,fill::zeros); //declare matrix A with size of R X C all have 0 entries with Armadillo.
	A.load("matrixA.txt");
	mat B;
	B.load("vectorB.txt");
	mat X;
	X = solve(A,B,solve_opts::force_approx); 
	
	cout <<"Matrix A (Coefficient Matrix):" << "\n" << A <<endl;
	cout <<"Vector B (Nonhomogeneous System):" << "\n" << B <<endl;
	cout <<"Solution:" << "\n" << X <<endl;	
	
	float matrixc[R_Mat][C_Mat] = {};
	float matrixd[R_Mat][C_Mat] = {};
	
	for (int i = 0; i < R_Mat; ++i)
	{
		for(int j = 0; j<C_Mat-1; ++j)
		{
			matrixc[i][j] = A[i+j*R_Mat] ;
			matrixd[i][j] = A[i+j*R_Mat] ;
		}			
	}
	for (int i = 0; i < R_Mat; ++i)
	{
		for(int j = C_Mat-1; j<C_Mat; ++j)
		{
			matrixc[i][j] = B[i] ;
			matrixd[i][j] = 0 ;
		}			
	}

	cout <<"Matrix for the linear system Ax=b :" <<endl;	
	PrintMatrix(matrixc);
	cout <<"Matrix for the linear system Ax=0 :" <<endl;	
	PrintMatrix(matrixd);

	// Order of Matrix(n)
	int n = 7, flag = 0;

	// Performing Matrix transformation
	flag = PerformOperation(matrixc, R_Mat, C_Mat);
	
	if (flag == 1)     
	flag = CheckConsistency(matrixc, R_Mat, C_Mat, flag);    
 	
	cout << endl;
	cout << "G*****************************Freya*****************" << endl;
	cout << endl;

	// Printing Solutions for homogeneous system
	PrintResult(matrixc,R_Mat, flag);
	cout << endl;	

	cout << "Row Echelon Form for linear system Ax=b : " << endl;
	PrintMatrix(matrixc);

	cout << endl;
	cout << "G*****************************Freya*****************" << endl;
	cout << endl;

	PerformOperation(matrixd, R_Mat, C_Mat);
	cout <<"Row Echelon Form for linear system Ax=0 :" <<endl;	
	PrintMatrix(matrixd);

}