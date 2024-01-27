// g++ -o result main.cpp

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function

using namespace std;

const int N = 3;

struct matrix
{
	int arr1[N][N];
};

struct matrix func(int N)
{
	struct matrix matrix_mem;
	std::fstream in("matrix1.txt");
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

void cofactor(int mat[N][N], int temp[N][N], int p,int q, int n)
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

int determinantOfMatrix(int mat[N][N], int dimension)
{
	int Det = 0;

	if (dimension == 1)
		return mat[0][0];

	int cofactorMat[N][N];
	int sign = 1;

	for (int firstRow = 0; firstRow < dimension; firstRow++)
	{
	cofactor(mat, cofactorMat, 0, firstRow, dimension);
	Det += sign * mat[0][firstRow] * determinantOfMatrix(cofactorMat, dimension - 1);
	sign = -sign;
	}
	return Det;
}

void display(int mat[N][N], int row, int col)
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
	int mat[N][N] = {};

	struct matrix a;
	a = func(N); // address of arr1
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			mat[i][j] = a.arr1[i][j];
		}
	}	

	int r=0, c=0;// cofactor of M
	int cofactorMat[N][N];
	int sign = 1;

	cout<<"The matrix A is "<<endl;
	display(mat,N,N);
	cout<<"Determinant of the matrix is "<<determinantOfMatrix(mat, N) << endl ;
	return 0;
}