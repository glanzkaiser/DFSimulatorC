// g++ -o result main.cpp -larmadillo
// Merci beaucoup Freya..

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

#define C_MatA 6 // Define the number of column for the matrix A
#define R_MatA 4 // Define the number of row for the matrix A

// Function to print the matrix 
void PrintMatrix(float a[][C_MatA])
{
	int r = R_MatA;
	int c = C_MatA;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << setprecision(4) << a[i][j] << "\t";
		cout << endl;
	}
}

// function to reduce matrix to reduced row echelon form.
int PerformOperation(float a[][C_MatA], int r, int n)
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
int PerformOperation2(float a[][C_MatA],  int r, int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pivot = 0;

	// Performing elementary operations again to make leading 1's
	for (i = 2; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 1 && a[i][j] !=0) 
			{				
				float pivot = a[i][j]; 
				for (k = 0; k <= n; k++)                
				{ 
					a[i][k] = a[i][k] / pivot;  
				}
				j = n-1;
			}
		}
	}
	return flag;
}
int PerformOperation3(float a[][C_MatA],  int r, int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pivot = 0;

	// Performing elementary operations again to make reduced row echelon form
	for (i = 2; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 0 && a[i-1][j] !=0) 
			{	
				if ( a[i-1][j] == -1 )
				{
					for (k = 0; k <= n; k++)                
					{ 
						a[i-1][k] = -1*(a[i-1][k]);  
					}			
				}			
				float pivot = a[i-1][j]/a[i][j]; 
				for (k = 0; k <= n; k++)                
				{ 
					a[i][k] = a[i][k]  - (a[i-1][k] * pivot);  
				}
			}
		}
	}
	for (i = 2; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 0 && a[i-2][j] !=0 && a[i-1][j] == 0) 
			{
				for (k = 0; k <= n; k++)                
				{ 
					swap(a[i][k], a[i-1][k]); // swap row that has zero entry in between two nonzero entries downward
				}			
			}
		}
	}
	for (i = 2; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] != 0 && a[i-1][j] !=0) 
			{			
				float pivot = a[i-1][j]/a[i][j]; 
				for (k = 0; k < n; k++)                
				{ 
					a[i][k] = a[i][k]  - (a[i-1][k] * pivot);   					
				}
				//break; 
				j = n-1;
				i = r-1;
			}				
		}
		
	}

	return flag;
}

int PerformOperation4(float a[][C_MatA],  int r, int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;

	// Performing elementary operations again if the leading 1's is negative, turns it into positive
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < n; j++) 
		{
			if (a[i][j] == -1) 
			{				 
				for (k = 0; k <= n; k++)                
				{ 
					a[i][k] = -1*a[i][k];  
				}
				j = n-1;
			}
		}
	}
	return flag;
}
 
// To check whether infinite solutions exists or no solution exists
int CheckConsistency(float a[][C_MatA], int r, int n, int flag)
{
	int i, j;
	float sum;

	// flag == 2 for infinite solution
	// flag == 3 for No solution
	flag = 3;
	for (i = 0; i < r; i++) 
	{
		sum = 0;
		for (j = 0; j < n; j++)        
			sum = sum + a[i][j];
		if (sum == a[i][j]) 
			flag = 2;        
	}
return flag;
}


// Driver code
int main(int argc, char** argv)
{
	arma::mat A(R_MatA,C_MatA,fill::zeros); //declare matrix A with size of R_MatA X C_MatA all have 0 entries with Armadillo.
	A.load("matrixA.txt");
	
	cout <<"Matrix A (Coefficient Matrix):" << "\n" << A <<endl;
	
	cout << endl;

	cout << "G*****************Freya*****************" << endl;
	cout << endl;

	float matrixc[R_MatA][C_MatA] = {};
	for (int i = 0; i < R_MatA; ++i)
	{
		for(int j = 0; j<C_MatA; ++j)
		{
			matrixc[i][j] = A[i+j*R_MatA] ;
		}			
	}
	
	
	// Order of Matrix(n)
	int n = 6, flag = 0;

	// Performing Matrix transformation
	flag = PerformOperation(matrixc, R_MatA, C_MatA);
	
	if (flag == 1)     
	flag = CheckConsistency(matrixc, R_MatA, C_MatA, flag);    
 	
	cout << endl;
	cout << "****************Row Echelon Form for matrix A****************" << endl;
	cout << endl;

	PerformOperation2(matrixc, R_MatA, C_MatA);
	PerformOperation3(matrixc, R_MatA, C_MatA);	
	PerformOperation2(matrixc, R_MatA, C_MatA);
	PerformOperation4(matrixc, R_MatA, C_MatA);
		
	PrintMatrix(matrixc);
  	cout << endl;

	// To compute rank, dimension and nullity.
	int rankA = 0;
	for (int i = 0; i < R_MatA; ++i)
	{
		for(int j = 0; j<C_MatA; ++j)
		{
			if (matrixc[i][j] == 1)
			{
				rankA = rankA + 1;			
			}
			else
			{
				rankA = rankA;			
			}	
		}		
	}
	int nullity = C_MatA - rankA;

	cout << "rank: " << rankA <<endl;
	cout << endl;
	cout << "dimension: " << C_MatA <<endl;
	cout << endl;
	cout << "nullity: " << nullity <<endl;
	cout << endl;
	cout << "****************Basis for the Null Space of Matrix A****************" << endl;
	cout << endl;
	
	// To compute the Basis for the Null Space of matrix A
	float matrixd[C_MatA][4] = {};
	
	for (int i = 0; i < rankA; i++) 
	{
		for (int j = 0; j < nullity; j++) 
		{
			matrixd[i][j] = -1*matrixc[i][j + rankA];
		}
	}
	for (int i = rankA; i < C_MatA; i++) 
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
	
	for (int i = 0; i < C_MatA; i++) 
	{
		for (int j = 0; j < nullity; j++) 
		cout <<setw(6) << setprecision(4) << matrixd[i][j] << "\t";
		cout << endl;
	}
  	
	arma::mat ANull(C_MatA,nullity,fill::zeros); //declare matrix ANull with size of C_MatA X nullity all have 0 entries with Armadillo.
	// Copy from matrixd to ANull
	for (int i = 0; i < C_MatA; ++i)
	{
		for(int j = 0; j<nullity; ++j)
		{
			ANull[i+j*C_MatA] = matrixd[i][j] ;
		}			
	}
	//ANull.print("Null Basis :\n");
	cout << endl;
	cout << "Basis for Null Space of Matrix A: " << endl;

	for (int j = 0; j < nullity; ++j) 
	{	
		cout << "column(" << j << ") : " << endl << ANull.col(j) << endl;			
	}
	cout << endl;

	// Optional: Armadillo' computation
	/*
	cout <<"Rank of matrix A :" << arma::rank(A) << endl;	
	cout << endl;

	cout <<"Nullity of matrix A :" << A.n_cols - arma::rank(A) << endl;
	cout << endl;
	cout <<"Orthonormal basis of Null space of matrix A :\n" << arma::null(A) << endl;	
	cout << endl;
	*/
}