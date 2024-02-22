// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
using namespace std;

#define R 4 // number of rows
#define C 6 // number of columns

// Driver program
int main()
{	
 	// Construct a matrix of size 4 X 6
	Matrix<float> A_mat(4,6);
	A_mat[0][0] = 2;		A_mat[0][1] = 2;	A_mat[0][2] = -1;	A_mat[0][3] = 0;	A_mat[0][4] = 1;	A_mat[0][5] = 0;
	A_mat[1][0] = -1;		A_mat[1][1] = -1;	A_mat[1][2] = 2;	A_mat[1][3] = -3;	A_mat[1][4] = 1;	A_mat[1][5] = 0;
	A_mat[2][0] = 1;		A_mat[2][1] = 1;	A_mat[2][2] = -2;	A_mat[2][3] = 0;	A_mat[2][4] = -1;	A_mat[2][5] = 0;
	A_mat[3][0] = 0;		A_mat[3][1] = 0;	A_mat[3][2] = 1;	A_mat[3][3] = 1;	A_mat[3][4] = 1;	A_mat[3][5] = 0;
	
	Matrix<float> A_coeffmat(4,5);
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < R; j++) 
			{	
				A_coeffmat[i][j] = A_mat[i][j];
			}
		
	}
	cout << "A:\n" << A_coeffmat <<endl;
	cout << "A augmented matrix:\n" << A_mat <<endl;
	
	//cout << "det(A):\n" << A_coeffmat.determinant() <<endl;
	//cout << "inv(A):\n" << A_coeffmat.inverse() <<endl;
	cout << endl;
	
	// Perform Gaussian Elimination / Forward elimination
	for (int k=0; k<R; k++)
	{
		int i_max = k;
		float v_max = A_mat[i_max][k];
	
		if (i_max != k)
		
			for (int m=0; m<C; k++)
			{
				float temp = A_mat[k][m];
				A_mat[k][m] = A_mat[i_max][m];
				A_mat[i_max][m] = temp;
			}
		
			for (int i=k+1; i<R; i++)
			{
				 // factor f to set current row kth element to 0 and subsequently remaining kth column to 0 
				float f = A_mat[i][k]/A_mat[k][k];

				// subtract fth multiple of corresponding kth row element
					for (int j=k+1; j<C; j++)
					{
						A_mat[i][j] -= A_mat[k][j]*f;
					    // filling lower triangular matrix with zeros
					}
				A_mat[i][k] = 0;
			}
	}
	
	cout << "A (in reduced row form) :\n" << A_mat <<endl;
	
	for (int i = 0; i < R; i++)
	{
		float f2 = A_mat[i][i];	
		for (int j = 0; j < C; j++) 
			{	
				A_mat[i][j] = A_mat[i][j]/f2;
			}
		
	}
	cout << "A (in row reduced echelon form) :\n" << A_mat <<endl;
	cout<<endl;
	return 0;
}