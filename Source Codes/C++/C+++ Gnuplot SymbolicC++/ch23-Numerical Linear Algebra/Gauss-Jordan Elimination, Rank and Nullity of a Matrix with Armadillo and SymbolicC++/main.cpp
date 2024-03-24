// g++ -o result main.cpp -larmadillo -lsymbolicc++
// Merci beaucoup Freya..

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>
#include "symbolicc++.h"

using namespace std;
using namespace arma;

#define R 5 // number of rows
#define C 5 // number of columns

// Function to print the matrix 
void PrintMatrix(float a[][C])
{
	int r = R;
	int c = C;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << setprecision(0) << a[i][j] << "\t";
		cout << endl;
	}
}

int GaussJordan1(float a[][C], int r, int n)
{
	// First operation of Gauss-Jordan elimination to make zeroes under the leading 1's
	for (int f = 1; f < r; f++)
	{
		for (int i = f; i < r; i++)
		{
			if (a[i][f-1] == 0)
			{
				// Do nothing, just skip.
			}
			else 
			{	
				float pivot = a[f-1][f-1]/a[i][f-1]; 
				for (int k = 0; k < n; k++)      
				{ 
					a[i][k] = (pivot*a[i][k]) - a[f-1][k];  
				}
			}
		}
	}
	return 0;
}

int GaussJordan2(float a[][C], int r, int n)
{
	// Second operation of Gauss-Jordan elimination to make zeroes above the leading 1's
	for (int j = 1; j < n; j++)
	{	
		if (a[j][j] == 0)
		{ 
			
		}
		else
		{
			for (int i = 0; i < j; i++) 
			{
				float pivot = a[i][j]/a[j][j];
				for (int k = 0; k < n; k++)      
				{ 
					a[i][k] = a[i][k] - (pivot*a[j][k]) ;  
				}
			}
		}
	}
	return 0;
}


int GaussJordanS(float a[][C], int r, int n)
{
	// Swap row that has zeroes at j row, j column to the row below that has nonzero at the same j column
	for (int j = 0; j < n; j++) 
	{
		for (int i = j; i < r; i++) 
		{
			if (a[i][j] !=0 && a[j][j] ==0) 
			{
				for (int k = 0; k < n; k++)      
				{ 
					swap(a[i][k], a[j][k]);
				}
			}
		}
	}
	return 0;
}

int GaussJordan3(float a[][C], int r, int n)
{
	// Operation to make Leading 1's in all rows
	for (int i = 0; i < r; i++) 
	{
		if (a[i][i] !=1) 
		{
			float pivot = a[i][i];
			for (int k = 0; k < n; k++)      
			{ 
				a[i][k] = a[i][k] / pivot ;  
			}
		}
	}
	return 0;
}

struct matrix
{
	int arr1[R][C];
};

struct matrix func(int r, int c)
{
	struct matrix matrix_mem;
	std::fstream in("matrixA.txt");
	float matrixtiles[R][C];
	for (int i = 0; i < r; ++i) 
	{
		for (int j = 0; j < c; ++j) 
		{
			in >> matrixtiles[i][j]; 
			matrix_mem.arr1[i][j] = matrixtiles[i][j] ;
		}
	}
	return matrix_mem;
}

// Driver code
int main(int argc, char** argv)
{
	arma::mat A(R,C,fill::zeros); //declare matrix A with size of R X C all have 0 entries with Armadillo.
	A.load("matrixA.txt"); // load matrixA.txt with Armadillo
	Matrix<Symbolic> B(R,C); // Declare matrix B with size R X C with SymbolicC++
	
	// Load matrixA.txt manually
	struct matrix a;
	a = func(R,C); // address of arr1
	for (int i = 0; i < R; ++i)
	{
		for (int j = 0; j < C; ++j) 
		{	
			B[i][j] = a.arr1[i][j];	
		}
	}	

	cout << "G*****************Freya*****************" << endl;
	cout <<"Matrix A (Coefficient Matrix):" << "\n" << A <<endl;

	// Gauss-Jordan computation for matrixc that is loaded with Armadillo still not perfect
	float matrixc[R][C] = {};
	for (int i = 0; i < R; ++i)
	{
		for(int j = 0; j<C; ++j)
		{
			matrixc[i][j] = A[i+j*R] ;
		}			
	}
	cout << endl;
	cout << "A:\n" << B <<endl;
	// *************************Computation**************************
	// Swap row that has zeroes at j row,j column to the row below that has nonzero at the same j column
	for (int j = 0; j < C; j++) 
	{
		for (int i = j; i < R; i++) 
		{
			if (B[i][j] !=0 && B[j][j] ==0) 
			{
				for (int k = 0; k < C; k++)      
				{ 
					swap(B[i][k], B[j][k]);
				}
			}
		}
	}
	// Gauss-Jordan step 1: make zeroes below all leading 1's
	for (int f = 1; f < R; f++)
	{
		for (int i = f; i < R; i++)
		{
			if (B[i][f-1] == 0)
			{
				// Do nothing, just skip.
			}
			else 
			{
				Symbolic pivot = B[f-1][f-1]/B[i][f-1]; 
				for (int k = 0; k < C; k++)      
				{ 
					B[i][k] = (pivot*B[i][k]) - B[f-1][k];  
				}
				//cout << "A:\n" << B <<endl;			
			}
		}
	}
	// Gauss-Jordan step 2: make zeroes above all leading 1's
	for (int j = 1; j < C; j++)
	{	
		if (B[j][j] == 0)
		{ 
			
		}
		else
		{
			for (int i = 0; i < j; i++) 
			{
				Symbolic pivot = B[i][j]/B[j][j];
				//cout << "i: " << i <<endl;
				//cout << "j: " << j <<endl;
				//cout << "pivot: " << pivot <<endl;
				for (int k = 0; k < C; k++)      
				{ 
					B[i][k] = B[i][k] - (pivot*B[j][k]) ;  
				}
				//cout << "A:\n" << B <<endl;
			}
		}
	}
	
	// Operation to make Leading 1's in all rows
	for (int i = 0; i < R; i++) 
	{
		if (B[i][i] !=1) 
		{
			Symbolic pivot = B[i][i];
			for (int k = 0; k < C; k++)      
			{ 
				B[i][k] = B[i][k] / pivot ;  
			}
		}
	}
	
	// ***********************End of Computation**********************
	cout << "****************Reduced Row Echelon Form for matrix A****************" << endl;
	cout << endl;

	cout << "A RREF (with SymbolicC++):\n" << B <<endl;
	cout << endl;

	///*
	GaussJordan1(matrixc, R, C);	
	GaussJordan2(matrixc, R, C);
	GaussJordanS(matrixc, R, C);	
	GaussJordan3(matrixc, R, C);	
	cout << "A RREF (with Armadillo):" << endl;
	PrintMatrix(matrixc);
	cout << endl;
	//*/

	// To compute rank, dimension and nullity.
	int rankA = 0;
	for (int i = 0; i < R; ++i)
	{
		for(int j = 0; j<C; ++j)
		{
			if (B[i][j] == 1)
			{
				rankA = rankA + 1;			
			}
			else
			{
				rankA = rankA;			
			}	
		}		
	}
	int nullity = C - rankA;

	cout << "rank: " << rankA <<endl;
	cout << endl;
	cout << "dimension: " << C <<endl;
	cout << endl;
	cout << "nullity: " << nullity <<endl;
	cout << endl;
	cout << "****************Basis for the Null Space of Matrix A****************" << endl;
	cout << endl;
	
	// To compute the Basis for the Null Space of matrix A, matrixd will have the size of C X nullity
	// for now we can only input the nullity manually, just put as much numbers as you like the computation is amazing
	Symbolic matrixd[C][96] = {};
	
	for (int i = 0; i < rankA; i++) 
	{
		for (int j = 0; j < nullity; j++) 
		{
			matrixd[i][j] = -1*B[i][j + rankA];
		}
	}
	for (int i = rankA; i < C; i++) 
	{
		for (int j = 0; j < nullity; j++) 
		{
			if (i-j == rankA) 
			{
				matrixd[i][j] = 1;
			}
			else 
			{
				matrixd[i][j] = 0;
			}
		}
	}
	
	for (int i = 0; i < C; i++) 
	{
		for (int j = 0; j < nullity; j++) 
		cout <<setw(6) << setprecision(4) << matrixd[i][j] << "\t";
		cout << endl;
	}
  	
	arma::mat ANull(C,nullity,fill::zeros); //declare matrix ANull with size of C X nullity all have 0 entries with Armadillo.
	// Copy from matrixd to ANull
	for (int i = 0; i < C; ++i)
	{
		for(int j = 0; j<nullity; ++j)
		{
			ANull[i+j*C] = matrixd[i][j] ;
		}			
	}
	//ANull.print("Null Basis :\n");
	cout << endl;
	cout << "Basis for Null Space in Column Form: " << endl;

	for (int j = 0; j < nullity; ++j) 
	{	
		cout << "column(" << j << ") : " << endl << ANull.col(j) << endl;			
	}

	// Optional: Armadillo' computation
	cout << endl;
	cout << "****************Armadillo Computation of Matrix A****************" << endl;
	cout << endl;
	
	cout <<"Rank of matrix A :" << arma::rank(A) << endl;	
	cout << endl;

	cout <<"Nullity of matrix A :" << A.n_cols - arma::rank(A) << endl;
	cout << endl;
	cout <<"Orthonormal basis of Null space of matrix A :\n" << arma::null(A) << endl;	
	cout << endl;
}