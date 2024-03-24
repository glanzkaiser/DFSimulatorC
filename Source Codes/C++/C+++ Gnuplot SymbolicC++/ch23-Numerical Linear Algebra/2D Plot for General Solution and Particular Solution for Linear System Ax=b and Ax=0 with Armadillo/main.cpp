// g++ -o result main.cpp -larmadillo -lboost_iostreams 
// Merci beaucoup Freya..
// C++ program to plot the particular and general solution of linear system Ax=b and Ax=0

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

using namespace std;
using namespace arma;

#define C_Mat 3 // Define the number of column for the linear system Ax=b
#define R_Mat 2 // Define the number of row for the linear system Ax=b
#define C_MatA 2 // Define the number of column for the matrix A
#define R_MatA 2 // Define the number of row for the matrix A

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
int PerformOperation2(float a[][C_Mat],  int r, int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pivot = 0;

	// Performing elementary operations again to make leading 1's
	for (i = 2; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 1 && a[i][j] !=0) 
			{				
				float pivot = a[i][j]; 
				for (k = 0; k <= n; k++)                
				{ 
					a[i][k] = a[i][k] / pivot;  
				}
				j = n-1;
			}
		}
	}
	return flag;
}
int PerformOperation3(float a[][C_Mat],  int r, int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pivot = 0;

	// Performing elementary operations again to make reduced row echelon form
	for (i = 2; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 0 && a[i-1][j] !=0) 
			{	
				if ( a[i-1][j] == -1 )
				{
					for (k = 0; k <= n; k++)                
					{ 
						a[i-1][k] = -1*(a[i-1][k]);  
					}			
				}			
				float pivot = a[i-1][j]/a[i][j]; 
				for (k = 0; k <= n; k++)                
				{ 
					a[i][k] = a[i][k]  - (a[i-1][k] * pivot);  
				}
			}
		}
	}
	for (i = 2; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 0 && a[i-2][j] !=0 && a[i-1][j] == 0) 
			{
				for (k = 0; k <= n; k++)                
				{ 
					swap(a[i][k], a[i-1][k]); // swap row that has zero entry in between two nonzero entries downward
				}			
			}
		}
	}
	for (i = 2; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 0 && a[i-1][j] !=0) 
			{			
				float pivot = a[i-1][j]/a[i][j]; 
				for (k = 0; k < n; k++)                
				{ 
					a[i][k] = a[i][k]  - (a[i-1][k] * pivot);   					
				}
				//break; 
				j = n-1;
				i = r-1;
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
	//cout <<"Rank of matrix A :" << arma::rank(A) << endl;	

	// Order of Matrix(n)
	int n = 7, flag = 0;

	// Performing Matrix transformation
	flag = PerformOperation(matrixc, R_Mat, C_Mat);
	
	if (flag == 1)     
	flag = CheckConsistency(matrixc, R_Mat, C_Mat, flag);    
 	
	cout << endl;
	cout << "G*****************************Freya*****************" << endl;
	cout << endl;

	PerformOperation2(matrixc, R_Mat, C_Mat);
	PerformOperation3(matrixc, R_Mat, C_Mat);	
	PerformOperation2(matrixc, R_Mat, C_Mat);
		
	cout << "Row Echelon Form for linear system Ax=b : " << endl;
	PrintMatrix(matrixc);

	cout << endl;
	cout << "G*****************************Freya*****************" << endl;
	cout << endl;

	PerformOperation(matrixd, R_Mat, C_Mat);
	PerformOperation2(matrixd, R_Mat, C_Mat);
	PerformOperation3(matrixd, R_Mat, C_Mat);	
	PerformOperation2(matrixd, R_Mat, C_Mat);
	cout <<"Row Echelon Form for linear system Ax=0 :" <<endl;	
	PrintMatrix(matrixd);

	// Plotting time
	Gnuplot gp;

	// We use a separate container for each column, like so:
	std::vector<double> pts_B_x;
	std::vector<double> pts_B_y;
	std::vector<double> pts_B_dx;
	std::vector<double> pts_B_dy;
	std::vector<double> pts_C_x;
	std::vector<double> pts_C_y;
	std::vector<double> pts_C_dx;
	std::vector<double> pts_C_dy;
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;	
	
	float o = 0;
	float xx;
	float xy;
	// If conditional for determining vector x
	if (arma::rank(A) == 0)
	{
		xx = 1;
		xy = 0; 
	}
	if (arma::rank(A) == 1)
	{
		xx = -matrixc[0][1];
		xy = 1;
	}
	if (arma::rank(A) == 2)
	{
		xx = 0;
		xy = 0;
		cout << "Matrix A has rank=2, thus has no basis for the null space" << endl;
	}
	// For vector x0
	float x0x = X[0];
	float x0y = X[1];

	// Create a vector x with origin at (0,0) and terminal point at (-3,1)
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_dx.push_back(xx);
	pts_B_dy.push_back(xy);
	// Create a vector x0 with origin at (0,0) and terminal point at (0.2,0.6)
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_dx.push_back(x0x);
	pts_C_dy.push_back(x0y);
	// Create a vector x+x0
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(xx + x0x);
	pts_D_dy.push_back(xy + x0y);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-3.3:1.3]\nset yrange [-1:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = -x/3\n";
	gp << "g(x) = -x/3 + 0.66666 \n";
	gp << "plot '-' with vectors title 'x', '-' with vectors title 'x_{0}','-' with vectors title 'x + x_{0}' lc 'green',f(x) title 'Solution Space of Ax=0' lt 3,g(x) with linespoints pointtype 1 pointsize 0.1 pi -2 lc 'black' title 'Solution Set of Ax=b'\n";
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
}