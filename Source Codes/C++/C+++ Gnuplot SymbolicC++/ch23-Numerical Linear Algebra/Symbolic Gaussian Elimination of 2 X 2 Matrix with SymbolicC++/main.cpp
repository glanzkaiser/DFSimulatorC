// g++ main.cpp -o result -lginac -lcln -lsymbolicc++
#include <iostream>
#include <ginac/ginac.h>
#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>

// Merci beaucoup Freya et Sentinel

#define R 2 // number of rows
#define C 2 // number of columns

using namespace std;
using namespace GiNaC;

int main()
{
	Symbolic λ("λ"), a("a"), b("b"), c("c"), d("d");;

	// Construct a symbolic matrix of size 2 X 2
	Matrix<Symbolic> I_mat(2,2);
	I_mat[0][0] = 1;		I_mat[0][1] = 0;
	I_mat[1][0] = 0;		I_mat[1][1] = 1 ;
	Matrix<Symbolic> A_mat(2,2);
	A_mat[0][0] = a;		A_mat[0][1] = b;
	A_mat[1][0] = c;		A_mat[1][1] = d ;

	cout << "A:\n" << A_mat <<endl;
	cout << "λI - A:\n" << λ*I_mat - A_mat <<endl;

	Matrix<Symbolic> B_mat(2,2);
	B_mat = λ*I_mat - A_mat;

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
	
	cout << " λI - A (in reduced row form) :\n" << B_mat <<endl;

	return 0;
}