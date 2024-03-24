// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
using namespace std;

#define R 5 // number of rows
#define C 3 // number of columns

// Driver program
int main()
{
	Symbolic b1("b1");
	Symbolic b2("b2");
	Symbolic b3("b3");
	Symbolic b4("b4");
	Symbolic b5("b5");
	
 	// Construct a symbolic matrix of size 5 X 3
	Matrix<Symbolic> B_mat(5,3);
	B_mat[0][0] = 1;		B_mat[0][1] = -2;	B_mat[0][2] = b1;	
	B_mat[1][0] = 1;		B_mat[1][1] = -1;	B_mat[1][2] = b2;	
	B_mat[2][0] = 1;		B_mat[2][1] = 1;	B_mat[2][2] = b3;	
	B_mat[3][0] = 1;		B_mat[3][1] = 2;	B_mat[3][2] = b4;	
	B_mat[4][0] = 1;		B_mat[4][1] = 3;	B_mat[4][2] = b5;	
	cout << "B:\n" << B_mat <<endl;
	cout << endl;

	// First operation to make the first leading 1 at the first row, first column
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++) 
		{
			if (B_mat[0][0] != 1 && B_mat[0][0] !=0 )          
			{      
				Symbolic pivot = B_mat[0][0]; 
				for (int k = 0; k < C; k++)      
				{ 
					B_mat[i][k] = B_mat[i][k] / pivot;  
				}
			}
			if (B_mat[0][0] == -1 )          
			{      
				for (int k = 0; k < C; k++)      
				{ 
					B_mat[i][k] = B_mat[i][k] * (-1) ;  
				}
				
			}
			break;
		}
	}
	
	// First operation of Gauss-Jordan elimination to make zeroes under the first leading 1
	for (int i = 1; i < R; i++)
	{
		for (int j = 0; j < C; j++) 
		{
			Symbolic pivot = B_mat[0][0]/B_mat[i][j]; 
			for (int k = 0; k < C; k++)      
			{ 
				B_mat[i][k] = (pivot*B_mat[i][k]) - B_mat[0][k];  
			}
			j = C-1;
		}
	}
	cout << "B after first operation to make zeroes under the first leading 1:"  <<endl;
	// Show the matrix nicely
	for (int i = 0; i < R; i++) 
	{
		for (int j = 0; j < C; j++) 
		cout <<setw(2) << B_mat[i][j] << "\t";
		cout << endl;
	}
	cout <<endl;

	// Second operation of Gauss-Jordan elimination to make zeroes under the second leading 1
	for (int i = 2; i < R; i++)
	{
		for (int j = 1; j < C; j++) 
		{
			Symbolic pivot = B_mat[1][1]/B_mat[i][j]; 
			for (int k = 0; k < C; k++)      
			{ 
				B_mat[i][k] = (pivot*B_mat[i][k]) - B_mat[1][k];  
			}
			j = C-1;
		}
	}
	
	cout << "B after second operation to make zeroes under the second leading 1:"  <<endl;
	
	for (int i = 0; i < R; i++) 
	{
		for (int j = 0; j < C; j++) 
		cout <<setw(2) << B_mat[i][j] << "\t";
		cout << endl;
	}


	// First operation of Gauss-Jordan elimination to make zeroes above the second leading 1
	for (int i = 1; i < R; i++)
	{
		for (int j = 1; j < C; j++) 
		{
			Symbolic pivot = B_mat[i-1][j]/B_mat[1][1]; 
			
			for (int k = 0; k < C; k++)      
			{ 
				B_mat[i-1][k] = B_mat[i-1][k] - (pivot*B_mat[i][k]) ;  
			}
			j = C-1;
			i = R-1;
		}
	}

	cout << "B after first operation to make zeroes above the second leading 1:"  <<endl;
	
	for (int i = 0; i < R; i++) 
	{
		for (int j = 0; j < C; j++) 
		cout <<setw(2) << B_mat[i][j] << "\t";
		cout << endl;
	}

	return 0;
}