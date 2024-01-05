// g++ -o result main.cpp 

#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <cmath>

#define N 3
#define M 4
using namespace std;

// Freya merci beaucoup, great efficient coding here.
// this LU decomposition function works
void LUdecomposition(float a[N][N], float l[N][N], float u[N][N], int n) 
{
	int i = 0, j = 0, k = 0;
	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < n; j++) 
		{
			if (j < i)
			l[j][i] = 0;
			else 
			{
			l[j][i] = a[j][i];
		 		for (k = 0; k < i; k++) 
				{
				l[j][i] = l[j][i] - l[j][k] * u[k][i];	
				}
			}
		}
		for (j = 0; j < n; j++) 
		{
		if (j < i)
		u[i][j] = 0;
		else if (j == i)
		u[i][j] = 1;
		else 
		{
			u[i][j] = a[i][j] / l[i][i];
			for (k = 0; k < i; k++) 
			{
			u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
			}
		}
		}
	}
}

// function to reduce matrix to reduced row echelon form.
int PerformOperation(float matL[][M], int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pro = 0;

    // Performing elementary operations
	for (i = 0; i < n; i++)
	{
		if (matL[i][i] == 0) 
		{
			c = 1;
			while ((i + c) < n && matL[i + c][i] == 0) 
			c++;            
			if ((i + c) == n) 
			{
				flag = 1;
				break;
			}
			for (j = i, k = 0; k <= n; k++) 
			swap(matL[j][k], matL[j+c][k]);
		}
		
		for (j = 0; j < n; j++) 
		{
		    // Excluding all i == j
		if (i != j) 
			{                 
		        // Converting Matrix to reduced row
		        // echelon form(diagonal matrix)
			float pro = matL[j][i] / matL[i][i]; 
			for (k = 0; k <= n; k++)                 
				matL[j][k] = matL[j][k] - (matL[i][k]) * pro;                
			}
		}
	}
	return flag;
}

// Function to print the desired result 
void PrintResult(float matL[][M], int n, int flag)
{
	cout << "The solution/s for Ly = b : " << endl;

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
	cout << "y(" << i  << ") = "<< matL[i][n] / matL[i][i] << ",  ";        
	}
}

void PrintResult2(float matU[][M], int n, int flag)
{
	cout << "The solution/s for Ux = y : " << endl;

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
	cout << "x(" << i  << ") = "<< matU[i][n] / matU[i][i] << ",  ";        
	}
}

// To check whether infinite solutions exists or no solution exists
int CheckConsistency(float matL[][M], int n, int flag)
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
			sum = sum + matL[i][j];
		if (sum == matL[i][j]) 
			flag = 2;        
	}
return flag;
}
 
// Function to print the matrix
void PrintMatrix(float matL[][M], int n)
{
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j <= n; j++) 
		cout << setw(6) << matL[i][j] << "\t";
		cout << endl;
	}
	cout<<endl;
}

void display(int matL[N][N], int row, int col)
{
	cout << setw(14) << "Matrix A" << endl;
	for (int i = 0; i < row; i++)
	{
	for (int j = 0; j < col; j++)
		cout<<setw(6)  << matL[i][j]<<"\t";	
		cout<<endl;
	}
	cout<<endl;
}

// take vectorb.txt as input from textfile 
int* vec() {
	static int x[N];
	std::fstream in("vectorb.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			x[i] =vectortiles[i];	
	}	
	return x;
}

// Driver code
int main()
{	
	int mat[N][N] = { { 2, 6, 2 }, { -3, -8, 0 }, { 4, 9, 2 } };
 	display(mat,3,3);
	
	// declare the matrix as float
   	float a[3][3] = { { 2, 6, 2 }, { -3, -8, 0 }, { 4, 9, 2 } };
 	
	float l[3][3], u[3][3];	
	LUdecomposition(a, l, u, N);
	// setw is for displaying nicely
	cout << setw(21) << "Lower Triangular"<< setw(32) << "Upper Triangular" << endl;


	// Displaying the result :
	for (int i = 0; i < N; i++) 
	{
        // Show Lower Triangular Matrix
	for (int j = 0; j < N; j++)
		cout << setw(6) << l[i][j] << "\t";
	cout << "\t";
 
        // Show Upper Triangular Matrix
	for (int j = 0; j < N; j++)
		cout << setw(6) << u[i][j] << "\t";
	cout << endl;
	}
	cout << endl;
	
	
	// Input for the Lower triangular matrix from array of the computed result of LUdecomposition()
	int* ptrvec;
	ptrvec = vec();
			
	float matL[M][M] = {0};
	for(int j=0; j<N; j++)
	{
		for(int k=0; k<N; k++)
		{
			matL[j][k] = l[j][k];
		}
			matL[j][N] = ptrvec[j];
	}

	cout << "Augmented Matrix L to solve Ly = b  : "  << endl;
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N+1; ++j) 
		{	
			cout << setw(6) << matL[i][j]  << "\t";
		}
		cout << endl;
	}	

	int n1 = 3, flag = 0, flagU = 0;
	//Performing Matrix transformation
	// Solving for Ly = b
	flag = PerformOperation(matL, n1);
	
	if (flag == 1)     
	flag = CheckConsistency(matL, n1, flag);    
 
	//Printing Final Matrix
	cout << endl;
	cout << "Reduced Row Echelon for Augmented Matrix L is : " << endl;
	PrintMatrix(matL, n1);

	// Printing Solutions(if exist)
	PrintResult(matL,n1, flag);
	cout << endl;	
	cout << endl;	

	// Solving for Ux = y
	// We can declare y1, y2, y3 after we do the PerformOperation(matL, n1) to make the reduced row echelon form of Ly=b
	// Store the result in vector y[N] of size N
	float y[N];
	for (int i = 0; i < N; ++i) 
	{
		y[i] = matL[i][N] / matL[i][i];	
	}	

	// Input for the Lower triangular matrix from array of the computed result of LUdecomposition()	
	float matU[M][M] = {0};
	for(int j=0; j<N; j++)
	{
		for(int k=0; k<N; k++)
		{
			matU[j][k] = u[j][k];
		}
			matU[j][N] = y[j];
	}

	cout << "Augmented Matrix U to solve Ux = y  : "  << endl;
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N+1; ++j) 
		{	
			cout << setw(6) << matU[i][j]  << "\t";
		}
		cout << endl;
	}	
	flagU = PerformOperation(matU, n1);

	if (flagU == 1)     
	flagU = CheckConsistency(matU, n1, flag);    
 
	cout << "Reduced Row Echelon for Augmented Matrix U is : " << endl;
	PrintMatrix(matU, n1);
	cout << endl;
	PrintResult2(matU,n1, flag);
	
	cout << endl;	

	return 0;
}