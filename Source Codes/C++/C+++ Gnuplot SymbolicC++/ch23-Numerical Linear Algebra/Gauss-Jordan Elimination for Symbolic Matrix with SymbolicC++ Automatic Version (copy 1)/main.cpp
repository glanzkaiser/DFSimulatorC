// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
using namespace std;

#define R 3 // number of rows
#define C 4 // number of columns

// Driver program
int main()
{
	Symbolic b1("b1"); // Don't mind this, only for example, you can replace numeric value below with this symbolic value.
	Symbolic b2("b2");
	Symbolic b3("b3");
	Symbolic b4("b4");
	Symbolic b5("b5");
	
 	// Construct a symbolic matrix of size R X C
	Matrix<Symbolic> B_mat(R,C);
	B_mat[0][0] = 0.5;		B_mat[0][1] =-0.4;	B_mat[0][2] = -0.6;	B_mat[0][3] = 0;
	B_mat[1][0] = -0.2;		B_mat[1][1] = 0.8;	B_mat[1][2] = -0.3;	B_mat[1][3] = 0;	
	B_mat[2][0] = -0.3;		B_mat[2][1] = -0.4;	B_mat[2][2] = 0.9;	B_mat[2][3] = 0;
	
	cout << "B:\n" << B_mat <<endl;
	cout << endl;

	// First operation of Gauss-Jordan elimination to make zeroes under the leading 1's
	for (int f = 1; f < R; f++)
	{
		for (int i = f; i < R; i++)
		{
		
			for (int j = 0; j < C; j++) 
			{	
				Symbolic pivot = B_mat[f-1][f-1]/B_mat[i][f-1]; 
				
				for (int k = 0; k < C; k++)      
				{ 
					B_mat[i][k] = (pivot*B_mat[i][k]) - B_mat[f-1][k];  
					
				}
				j = C-1;
			}
		}
	}

	cout << "B after operation to make zeroes under all the leading 1's:"  <<endl;
	
	for (int i = 0; i < R; i++) 
	{
		for (int j = 0; j < C; j++) 
		cout <<setw(2) << B_mat[i][j] << "\t";
		cout << endl;
	}

	cout << endl;
	return 0;
}