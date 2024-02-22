// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
using namespace std;

#define R 3 // number of rows
#define C 3 // number of columns

// Driver program
int main()
{
	Symbolic x("x");
	Symbolic y1, dy1, ddy1;
	Symbolic y2, dy2, ddy2;
	Symbolic y3, dy3, ddy3;

	y1 = exp(x);
	dy1 = df(y1, x);
	ddy1 = df(dy1, x);
	
	y2 = x*exp(x);
	dy2 = df(y2, x);
	ddy2 = df(dy2, x);

	y3 = x*x*exp(x);
	dy3 = df(y3, x);
	ddy3 = df(dy3, x);
	       	
 	// Construct a symbolic matrix of size 3 X 3
	Matrix<Symbolic> W_mat(3,3);
	W_mat[0][0] = y1;		W_mat[0][1] = y2;		W_mat[0][2] = y3;	
	W_mat[1][0] = dy1;	W_mat[1][1] = dy2;	W_mat[1][2] = dy3;	
	W_mat[2][0] = ddy1;	W_mat[2][1] = ddy2;	W_mat[2][2] = ddy3;	
	cout << "W:\n" << W_mat <<endl;
	cout << "det(W):\n" << W_mat.determinant() <<endl;
	//cout << "inv(B):\n" << B_mat.inverse() <<endl;
	cout << endl;
	
	// Perform Gaussian Elimination / Forward elimination
	for (int k=0; k<R; k++)
	{
		int i_max = k;
		Symbolic v_max = W_mat[i_max][k];
	
		if (i_max != k)
		
			for (int m=0; m<C; k++)
			{
				Symbolic temp = W_mat[k][m];
				W_mat[k][m] = W_mat[i_max][m];
				W_mat[i_max][m] = temp;
			}
		
			for (int i=k+1; i<R; i++)
			{
				 // factor f to set current row kth element to 0 and subsequently remaining kth column to 0 
				Symbolic f = W_mat[i][k]/W_mat[k][k];

				// subtract fth multiple of corresponding kth row element
					for (int j=k+1; j<C; j++)
					{
						W_mat[i][j] -= W_mat[k][j]*f;
					    // filling lower triangular matrix with zeros
					}
				W_mat[i][k] = 0;
			}
	}
	
	//cout << "W (in reduced row form) :\n" << W_mat <<endl;
	
	for (int i = 0; i < R; i++)
	{
		Symbolic f2 = W_mat[i][i];	
		for (int j = 0; j < C; j++) 
			{	
				W_mat[i][j] = W_mat[i][j]/f2;
			}
	}
	cout << "W (in row reduced echelon form) :\n" << W_mat <<endl;
	cout<<endl;
	return 0;
}