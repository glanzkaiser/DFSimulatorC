// g++ -o result main.cpp
// Merci beaucoup Freya..
// C++ program manipulate matrix, row space, and column space

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

const int N = 5; // Define the number of column for A, the amount of data in each row vector
const int R = 4; // number of rows for A
const int C = 5; // number of column for A

#define C_Mattranspose 4 // Define the number of column for A^T
#define R_Mattranspose 5 // Define the number of row for A^T
#define N_Mat 5 // Define the number of column for A
 
// Function to print the matrix
void PrintMatrix(float a[][N_Mat])
{
	int r = 4;
	int c = 5;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << a[i][j] << "\t";
		cout << endl;
	}
}
void PrintMatrixTranspose(float a[][C_Mattranspose])
{
	int r = 5;
	int c = 4;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << a[i][j] << "\t";
		cout << endl;
	}
}

int PerformOperation(float a[][C_Mattranspose], int r, int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pro = 0;

    // Performing elementary operations
	for (i = 0; i <= r; i++)
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
		
		for (j = 0; j <= n; j++) 
		{
		    // Excluding all i == j
		if (i != j) 
			{                 
		        // Converting Matrix to reduced row
		        // echelon form(diagonal matrix)
			float pro = a[j][i] / a[i][i]; 
			for (k = 0; k <= n; k++)                 
				a[j][k] = a[j][k] - (a[i][k]) * pro;                
			}
		}
	}
	return flag;
}

int PerformOperation2(float a[][C_Mattranspose], int m, int n)
{
	int flag = 0;
	float pivot = 0; 

    	// Performing elementary operations again to make leading 1 in every rows
	for (int i = 1; i < m; i++)
	{
		for (int j = 0; j < n; j++) 
		{		
			if (a[i][j] !=1 && a[i][j] !=0) 
			{					
				float pivot = a[i][j];		
				for (int k = 0; k < n; k++)                
				{ 
					a[i][k] = a[i][k] / pivot;  
				}
				j = n-1;
			}	
		}
	}	
	return flag;
}

int PerformOperation3(float a[][C_Mattranspose], int m, int n)
{
	int flag = 0;
	float pivot = 0;

    	// Performing elementary operations again to delete linearly dependent row
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) 
		{		
			if (a[i-1][j] == 1 && a[i][j] !=0 ) 
			{					
				float pivot = a[i-1][j]/a[i][j];		
				for (int k = 0; k < n; k++)                
				{ 
					a[i][k] = a[i][k] - (a[i-1][k]  * pivot);  
				}
				j = n-1;
			}	
		}
	}	
	return flag;
}

float* vecv() {
	static float v[N];
	std::fstream in("vectorV.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			v[i] =vectortiles[i];	
	}	
	return v;
}

float* vecw() {
	static float w[N];
	std::fstream in("vectorW.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			w[i] =vectortiles[i];	
	}	
	return w;
}

float* vecx() {
	static float x[N];
	std::fstream in("vectorX.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			x[i] =vectortiles[i];	
	}	
	return x;
}

float* vecy() {
	static float y[N];
	std::fstream in("vectorY.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			y[i] =vectortiles[i];	
	}	
	return y;
}

// Driver code
int main(int argc, char** argv)
{
	float* ptrvecv;
	ptrvecv = vecv();
	float* ptrvecw;
	ptrvecw = vecw();
	float* ptrvecx;
	ptrvecx = vecx();
	float* ptrvecy;
	ptrvecy = vecy();
	
	arma::mat A(R,C,fill::zeros); //declare matrix A with size of R X C all have 0 entries with Armadillo.
	arma::mat A_transpose(C,R,fill::zeros); //declare matrix A_transpose with size of C X R all have 0 entries with Armadillo.
	arma::mat A_gauss(C,R,fill::zeros); //declare matrix A after performing Gaussian elimination with size of R X C 

	float a[R][C] = {};
	for (int j = 0; j < C; ++j)
	{
		for(int i = 0; i < R; ++i)
		{
			if (i==0)
			{
				a[i][j] = ptrvecv[j];
			}
			if (i==1)
			{
				a[i][j] = ptrvecw[j];
			}
			if (i==2)
			{
				a[i][j] = ptrvecx[j];
			}
			if (i==3)
			{
				a[i][j] = ptrvecy[j];
			}
		}			
	}	

	// Fill matrix A from Armadillo with matrix a[R][C] from loading textfile of row vectors v,w,x,y
	for (int i = 0; i < R; ++i)
	{
		for(int j = 0; j<C; ++j)
		{
			A[i+j*R] = a[i][j];
		}			
	}	
	
	A_transpose = A.t();
	float a_transpose[C][R] = {};
	A.print("A:");
  	cout << endl;
	cout <<"A (in simpler form): " << endl;
	PrintMatrix(a);
	cout << endl;
	A_transpose.print("A^T:");
  	cout << endl;
	cout << endl;

	int flag = 0;

	// Transposing matrix A manually
	for (int i = 0; i < C; ++i)
	{
		for(int j = 0; j<R; ++j)
		{
			a_transpose[i][j] = a[j][i];
		}			
	}
	cout << " A^T (in simpler form): " << endl;	
	PrintMatrixTranspose(a_transpose);
	cout << endl;

	// Performing row operations to reduced row echelon
	PerformOperation(a_transpose, R_Mattranspose, C_Mattranspose);
	// Performing row operations again to make leading 1's in all rows
	PerformOperation2(a_transpose, R_Mattranspose, C_Mattranspose);
	// Performing row operations again to delete linearly dependent rows
	PerformOperation3(a_transpose, R_Mattranspose, C_Mattranspose);

	// Save the transposed matrix that has become reduced row echelon into Armadillo Matrix A_gauss 
	for (int i = 0; i < C; ++i)
	{
		for(int j = 0; j<R; ++j)
		{
			A_gauss[i+j*C] = a_transpose[i][j];
		}			
	}	
	cout << " A^T in row echelon form: " << endl;	
	PrintMatrixTranspose(a_transpose);
	cout <<endl;
	A_gauss.print("A^T in row echelon form with Armadillo:");
  	cout << endl;

	arma::mat B(5,0, fill::ones); // Declare matrix B to store the basis vectors with 5 rows and 0 columns

	cout << " Basis for the column space of A^T : " << endl;		
	for (int i = 0; i < R_Mattranspose; ++i)
	{
		for (int j = 0; j < C_Mattranspose; ++j) 
		{	
			if ( a_transpose[i][j] !=0 )
			{
				cout << "A^T.col(" << j << ") : " << endl << A_transpose.col(j) << endl;
				B.insert_cols(i,A_transpose.col(j)); // A_transpose.col(j)  will be added to column i in matrix B 
				j = C_Mattranspose-1;
			}	
		}
		cout << endl;
	}	

	B.print("B (Matrix with Basis Vectors for row Space of A):");
  	// determinant
	//cout << "det(B): " << det(B) << endl;
  
	 // submatrices

	//cout << "B( row_number, span(first col, last col) ):" << endl << A_transpose(span(0,4), span(0,3) ) << endl;
 	//cout << "B( row_number, span(first col, last col) ):" << endl << A_transpose.submat(0,0,4,3) << endl;

}