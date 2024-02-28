// g++ -o result main.cpp
// Merci beaucoup Freya..
// C++ program determine basis for the row space, and column space

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

const int N = 6; // Define the number of column for A, the amount of data in each row vector

#define C_Mattranspose 4 // Define the number of column for A^T
#define R_Mattranspose 6 // Define the number of row for A^T
#define C_Mat 6 // Define the number of column for A
#define R_Mat 4 // Define the number of row for A
 
// Function to print the matrix

void PrintMatrixC(float a[][6])
{
	int r = 4;
	int c = 6;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << a[i][j] << "\t";
		cout << endl;
	}
}
void PrintMatrixTranspose(float a[][C_Mattranspose])
{
	int r = 6;
	int c = 4;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << a[i][j] << "\t";
		cout << endl;
	}
}

// function to reduce matrix to reduced row echelon form.
int PerformOperation(float a[][C_Mat],  int r, int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pro = 0;

    // Performing elementary operations
	for (i = 0; i < r; i++)
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
		
		for (j = 0; j < n; j++) 
		{
		    // Excluding all i == j
		if (i != j) 
			{                 
		        // Converting Matrix to reduced row echelon form(diagonal matrix)
			float pro = a[j][i] / a[i][i]; 
			for (k = 0; k <= n; k++)                 
				a[j][k] = a[j][k] - (a[i][k]) * pro;                
			}
		}
	}
	return flag;
}
 
int PerformOperation2(float a[][C_Mat],  int r, int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pivot = 0;

    // Performing elementary operations again
	for (i = 2; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 0 && a[i-1][j] !=0) 
			{				
				float pivot = a[i-1][j] / a[i][j]; 
				for (k = 0; k <= n; k++)                
				{ 
					a[i][k] = a[i][k] - (a[i-1][k] * pivot);  
				}
				j = n-1;
			}
		}
	}
	return flag;
}

int PerformOperationAT(float a[][C_Mattranspose], int r, int n)
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

int PerformOperationAT2(float a[][C_Mattranspose], int m, int n)
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

int PerformOperationAT3(float a[][C_Mattranspose], int m, int n)
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
	
	arma::mat A(R_Mat,C_Mat,fill::zeros); //declare matrix A with size of R X C all have 0 entries with Armadillo.
	arma::mat AGauss(R_Mat,C_Mat,fill::zeros); //declare matrix AGauss with size of R X C all have 0 entries with Armadillo.	
	arma::mat A_transpose(C_Mat,R_Mat,fill::zeros); //declare matrix A_transpose with size of C X R all have 0 entries with Armadillo.
	
	float a[R_Mat][C_Mat] = {};
	float c[R_Mat][C_Mat] = {};
	for (int j = 0; j < C_Mat; ++j)
	{
		for(int i = 0; i < R_Mat; ++i)
		{
			if (i==0)
			{
				c[i][j] = ptrvecv[j];
				a[i][j] = ptrvecv[j];
			}
			if (i==1)
			{
				c[i][j] = ptrvecw[j];
				a[i][j] = ptrvecw[j];
			}
			if (i==2)
			{
				c[i][j] = ptrvecx[j];
				a[i][j] = ptrvecx[j];
			}
			if (i==3)
			{
				c[i][j] = ptrvecy[j];
				a[i][j] = ptrvecy[j];
			}
		}			
	}	
	cout << " A : " << endl;	
	PrintMatrixC(c);

	// Fill matrix A from Armadillo with matrix c[4][6] from loading textfile of row vectors v,w,x,y
	for (int i = 0; i < R_Mat; ++i)
	{
		for(int j = 0; j<C_Mat; ++j)
		{
			A[i+j*R_Mat] = c[i][j];
		}			
	}	
	
	A_transpose = A.t();
	A_transpose.print("A^T: (with Armadillo)");
  	cout << endl;
	cout << endl;

	float a_transpose[C_Mat][R_Mat] = {};
	for (int i = 0; i < C_Mat; ++i)
	{
		for(int j = 0; j<R_Mat; ++j)
		{
			a_transpose[i][j] = a[j][i];
		}			
	}

	int flag = 0;

	// Performing row operations to reduced row echelon for A
	PerformOperation(c, R_Mat, C_Mat);
	// Performing row operations again to make leading 1's in all rows
	PerformOperation2(c, R_Mat, C_Mat);
	// Performing row operations again to delete linearly dependent rows
	//PerformOperationA3(a, R_Mat, C_Mat);

	cout << " A in row echelon form: " << endl;	
	PrintMatrixC(c);
	cout <<endl;

	// Save the matrix A that has become reduced row echelon into Armadillo Matrix A_gauss 
	for (int i = 0; i < R_Mat; ++i)
	{
		for(int j = 0; j<C_Mat; ++j)
		{
			AGauss[i+j*R_Mat] = c[i][j];
		}			
	}
	cout <<endl;
	AGauss.print("A in row echelon form with Armadillo:");
  	cout << endl;

	arma::mat BC(4,0, fill::ones); // Declare matrix B to store the basis vectors with 4 rows and 0 columns
	arma::mat BR(0,6, fill::ones); // Declare matrix B to store the basis vectors with 0 rows and 6 columns

	cout << " Basis for the row space of A : " << endl;		
	for (int i = 0; i < R_Mat; ++i)
	{
		for (int j = 0; j < C_Mat; ++j) 
		{	
			if ( c[i][j] !=0 )
			{
				cout << "A.row(" << i << ") : " << endl << AGauss.row(i) << endl;
				BR.insert_rows(i,AGauss.row(i)); // AGauss.row(i) will be added to row i in matrix BR
				j = C_Mat-1;
			}	
		}
		cout << endl;
	}
	cout << " Basis for the column space of A : " << endl;		
	for (int i = 0; i < R_Mat; ++i)
	{
		for (int j = 0; j < C_Mat; ++j) 
		{	
			if ( c[i][j] !=0 )
			{
				cout << "A.col(" << j << ") : " << endl << A.col(j) << endl;
				BC.insert_cols(i,A.col(j)); // A.col(j)  will be added to column i in matrix BC
				j = C_Mat-1;
			}	
		}
		cout << endl;
	}	

	BR.print("BR (Matrix with Basis Vectors for Row Space of A):");
	cout <<  endl;
  	BC.print("BC (Matrix with Basis Vectors for Column Space of A):");
	cout <<  endl;

	// Performing row operations to reduced row echelon for A^T
	// Still not successful to become reduced row echelon
	
	//PrintMatrixTranspose(a_transpose); // Working really great.
  	cout <<  endl;
	PerformOperationAT(a_transpose, R_Mattranspose, C_Mattranspose);
	// Performing row operations again to make leading 1's in all rows
	PerformOperationAT2(a_transpose, R_Mattranspose, C_Mattranspose);
	// Performing row operations again to delete linearly dependent rows
	PerformOperationAT3(a_transpose, R_Mattranspose, C_Mattranspose);
	
	//PrintMatrixTranspose(a_transpose);	
	cout <<  endl;	
}