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
	Symbolic a("a");
	Symbolic b("b");
	Symbolic c("c");
	
 	// Construct a symbolic matrix of size 3 X 4
	Matrix<Symbolic> B_mat(3,4);
	B_mat[0][0] = 1;		B_mat[0][1] = 0;	B_mat[0][2] = a;	B_mat[0][3] = 0;	
	B_mat[1][0] = -2;		B_mat[1][1] = 5;	B_mat[1][2] = b;	B_mat[1][3] = 0;	
	B_mat[2][0] = 3;		B_mat[2][1] = -3;	B_mat[2][2] = c;	B_mat[2][3] = 0;	
	cout << "The matrix A:\n" << B_mat <<endl;
	cout << endl;
	
	// Perform Gaussian Elimination / Forward elimination
	for (int k=0; k<R; k++)
	{
		int i_max = k;
		Symbolic v_max = B_mat[i_max][k];
	
		if (i_max != k)
		
			for (int m=0; m<C; k++)
			{
				Symbolic temp = B_mat[k][m];
				B_mat[k][m] = B_mat[i_max][m];
				B_mat[i_max][m] = temp;
			}
		
			for (int i=k+1; i<R; i++)
			{
				 // factor f to set current row kth element to 0 and subsequently remaining kth column to 0 
				Symbolic f = B_mat[i][k]/B_mat[k][k];

				// subtract fth multiple of corresponding kth row element
					for (int j=k+1; j<C; j++)
					{
						B_mat[i][j] -= B_mat[k][j]*f;
						//B_mat[i][j] = B_mat[i][j]/B_mat[i][i];
					    // filling lower triangular matrix with zeros
					}
				B_mat[i][k] = 0;
			}
	}
	
	cout << "A (in reduced row form) :\n" << B_mat <<endl;
	
	for (int i = 0; i < R; i++)
	{
		Symbolic f2 = B_mat[i][i];	
		for (int j = 0; j < C; j++) 
			{	
				B_mat[i][j] = B_mat[i][j]/f2;
			}
		
	}
	//cout << "A (in row reduced echelon form) :\n" << B_mat <<endl;
	cout<<endl;
	return 0;
}