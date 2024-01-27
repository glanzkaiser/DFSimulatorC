// g++ -o result main.cpp

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>

using namespace std;

const int N = 3;

struct matrix
{
	int arr1[N][N];
};

struct matrix func(int N)
{
	struct matrix matrix_mem;
	std::fstream in("matrixA.txt");
	float matrixtiles[N][N];
	for (int i = 0; i < N; ++i) 
	{
		for (int j = 0; j < N; ++j) 
		{
			in >> matrixtiles[i][j]; 
			matrix_mem.arr1[i][j] = matrixtiles[i][j] ;
		}
	}
	return matrix_mem;
}

// take vectorb.txt as input from textfile 
int* vec() {
	static int x[N];
	std::fstream in("vectorb.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			x[i] =vectortiles[i];	
	}	
	return x;
}

void cofactor(float mat[N][N], float temp[N][N], int p,int q, int n)
{
	int i = 0, j = 0;
	for (int row = 0; row < n; row++)
	{		
		for (int column = 0; column < n; column++)
		{
			if (row != p && column != q)
			{
				temp[i][j++] = mat[row][column];
				if (j == n - 1)
				{
				j = 0;
				i++;
				}
			}
		}
	}
}

int determinantOfMatrix(float mat[N][N], int dimension)
{
	float Det = 0;

	if (dimension == 1)
		return mat[0][0];

	float cofactorMat[N][N];
	int sign = 1;

	for (int firstRow = 0; firstRow < dimension; firstRow++)
	{
	cofactor(mat, cofactorMat, 0, firstRow, dimension);
	Det += sign * mat[0][firstRow] * determinantOfMatrix(cofactorMat, dimension - 1);
	sign = -sign;
	}
	return Det;
}

void display(float mat[N][N], int row, int col)
{
for (int i = 0; i < row; i++)
	{
	for (int j = 0; j < col; j++)
		cout<< setw(6) << mat[i][j]<<"\t";	
		cout<<endl;
	}
	cout<<endl;
}

int main(){
	// construct matrix A
	float mat[N][N] = {};
	// contruct vector b
	int* ptrvec;
	ptrvec = vec();

	struct matrix a;
	a = func(N); // address of arr1
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			mat[i][j] = a.arr1[i][j];
		}
	}	

	// construct matrix A1
	float mat1[N][N] = {0};
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			mat1[i][j] = mat[i][j];
			mat1[i][0] = ptrvec[i];
		}			
	}
	// construct matrix A2
	float mat2[N][N] = {0};
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			mat2[i][j] = mat[i][j];
			mat2[i][1] = ptrvec[i];
		}			
	}
	// construct matrix A3
	float mat3[N][N] = {0};
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			mat3[i][j] = mat[i][j];
			mat3[i][2] = ptrvec[i];
		}			
	}
	int r=0, c=0;// cofactor of M
	float cofactorMat[N][N];
	int sign = 1;
	
	cout<<"The matrix A is "<<endl;
	display(mat,N,N);
	
	cout << "Vector b is: " << endl;
	for (int i = 0; i < N; ++i)
	{
		cout <<ptrvec[i]<< ' ' << endl;	
	}	
	cout<< endl ;
	cout<<"The matrix A1 is "<<endl;
	display(mat1,N,N);
	cout<< endl ;
	cout<<"The matrix A2 is "<<endl;
	display(mat2,N,N);
	cout<< endl ;
	cout<<"The matrix A3 is "<<endl;
	display(mat3,N,N);
	cout<< endl ;
	
	cout<<"Determinant of the matrix A is "<<determinantOfMatrix(mat, N) << endl ;
	cout<<"Determinant of the matrix A1 is "<<determinantOfMatrix(mat1, N) << endl ;
	cout<<"Determinant of the matrix A2 is "<<determinantOfMatrix(mat2, N) << endl ;
	cout<<"Determinant of the matrix A3 is "<<determinantOfMatrix(mat3, N) << endl ;
	cout<< endl ;

	float x1 = float(determinantOfMatrix(mat1, N))/float(determinantOfMatrix(mat, N)) ;
	float x2 = float(determinantOfMatrix(mat2, N))/float(determinantOfMatrix(mat, N)) ;
	float x3 = float(determinantOfMatrix(mat3, N))/float(determinantOfMatrix(mat, N)) ;
	cout<<"The solution is: "<< endl ;
	cout<<"x1 = "<< fixed << setprecision(6) << x1 << endl ;
	cout<<"x2 = "<< fixed << setprecision(6) << x2 << endl ;
	cout<<"x3 = "<< fixed << setprecision(6) << x3 << endl ;
	
	return 0;
}