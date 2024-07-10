// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel et RK

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
	Symbolic a("a");
	Symbolic b("b");
	Symbolic c("c");
	
 	// Construct a symbolic matrix of size 4 X 6
	Matrix<Symbolic> B_mat(4,6);
	B_mat[0][0] = 1;		B_mat[0][1] = 3;	B_mat[0][2] = -2;	B_mat[0][3] = 0;	B_mat[0][4] = 2;	B_mat[0][5] = 0;	
	B_mat[1][0] = 2;		B_mat[1][1] = 6;	B_mat[1][2] = -5;	B_mat[1][3] = -2;	B_mat[1][4] = 4;	B_mat[1][5] = -3;
	B_mat[2][0] = 0;		B_mat[2][1] = 0;	B_mat[2][2] = 5;	B_mat[2][3] = 10;	B_mat[2][4] = 0;	B_mat[2][5] = 15;
	B_mat[3][0] = 2;		B_mat[3][1] = 6;	B_mat[3][2] = 0;	B_mat[3][3] = 8;	B_mat[3][4] = 4;	B_mat[3][5] = 18;

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
	
	for (int i = 0; i < R; i++) // Better algorithm from RK on July 6, 2024
	{
		Symbolic f2;
		if (B_mat[i][i] != 0)
		{
			f2 = B_mat[i][i];					
		}
		else if (B_mat[i][i] == 0)
		{
			int j = 0;
			while (j < C)
			{
				if (B_mat[i][j] !=0)
				{
					f2 = B_mat[i][j];
				}
				j++;
			}					
		}

		for (int j = 0; j < C; j++) 
		{			
			B_mat[i][j] = B_mat[i][j]/f2;	
		}	
	}
	cout << "A (in row reduced echelon form) :\n" << B_mat <<endl;
	cout<<endl;
	return 0;
}