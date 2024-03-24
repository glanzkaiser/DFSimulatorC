// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
using namespace std;

#define R 5 // number of rows
#define C 6 // number of columns

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
	B_mat[0][0] = 1;		B_mat[0][1] = 4;	B_mat[0][2] = -2;	B_mat[0][3] = 4;	B_mat[0][4] = 5;	B_mat[0][5] = -3;
	B_mat[1][0] = 3;		B_mat[1][1] = -7;	B_mat[1][2] = 2;	B_mat[1][3] = 0;	B_mat[1][4] = 1;	B_mat[1][5] = 4;
	B_mat[2][0] = 2;		B_mat[2][1] = -5;	B_mat[2][2] = 2;	B_mat[2][3] = 4;	B_mat[2][4] = 6;	B_mat[2][5] = 1;
	B_mat[3][0] = 4;		B_mat[3][1] = -9;	B_mat[3][2] = 2;	B_mat[3][3] = -4;	B_mat[3][4] = -4;	B_mat[3][5] = 7;
	B_mat[4][0] = 14;		B_mat[4][1] = 2;	B_mat[4][2] = 2;	B_mat[4][3] = 5;	B_mat[4][4] = 1;	B_mat[4][5] = 12;
	
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

	// Operation of Gauss-Jordan elimination to make zeroes above all leading 1's
	for (int j = 1; j < C; j++)
	{	
		if (B_mat[j][j] == 0)
		{ 
			break;
		}
		else
		{
			for (int i = 0; i < j; i++) 
			{
				Symbolic pivot = B_mat[i][j]/B_mat[j][j]; 
				//cout << "i : "<< i << endl;
				//cout << "j : "<< j << endl;
				//cout << "pivot: " << pivot << endl;
				for (int k = 0; k < C; k++)      
				{ 
					B_mat[i][k] = B_mat[i][k] - (pivot*B_mat[j][k]) ;  
				}
				/*
				for (int i = 0; i < R; i++) 
				{
					for (int j = 0; j < C; j++) 
					cout <<setw(2) << B_mat[i][j] << "\t";
					cout << endl;
				}
				*/
			}
		}
	}
	
	cout << "B after operation to make zeroes above all the leading 1's:"  <<endl;
	
	for (int i = 0; i < R; i++) 
	{
		for (int j = 0; j < C; j++) 
		cout <<setw(2) << B_mat[i][j] << "\t";
		cout << endl;
	}
	cout << endl;

	// Operation to make leading 1's all 1 at the diagonal
	for (int i = 0; i < R; i++) 
	{
		if (B_mat[i][i] !=1) 
		{
			Symbolic pivot = B_mat[i][i];
			for (int k = 0; k < C; k++)      
			{ 
				B_mat[i][k] = B_mat[i][k] / pivot ;  
			}
		}
	}
	
	cout << "B after operation to make leading 1's at the diagonal:"  <<endl;
	
	for (int i = 0; i < R; i++) 
	{
		for (int j = 0; j < C; j++) 
		cout <<setw(2) << B_mat[i][j] << "\t";
		cout << endl;
	}
	cout << endl;
	return 0;
}