// g++ -o result main.cpp
// Merci beaucoup Freya..
// C++ program to find the regression line

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
using namespace std;

const int N = 3;
const int C1 = 3;
const int C2 = 3;

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

void displayfloat(float mat[N][N], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
	for (int j = 0; j < col; j++)
		cout<<setw(8)  << fixed << setprecision(3) << mat[i][j]<<"\t";	
		cout<<endl;
	}
	cout<<endl;
}

void multiplyMatrix(float matrix1[][C1], float matrix2[C1][C2])
{
	float mat_result[N][C2];
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<C2; ++j)
		{
			mat_result[i][j] = 0;
			for(int k = 0; k<C1; ++k)
			{
				mat_result[i][j] += matrix1[i][k]*matrix2[k][j];
			}
		}			
	}
	displayfloat(mat_result,N,C2);
}

// Driver code
int main()
{
	float* ptrvecx;
	ptrvecx = vecx();
	float* ptrvecy;
	ptrvecy = vecy();
	
	// Create the vandermonde matrix
	float mat[N][N];
	float mat_transpose[N][N];
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			mat[j][i] = pow(ptrvecx[j],i);
			mat[j][0] = 1;
		}			
	}
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			mat_transpose[j][i] = mat[i][j];
		}			
	}
	cout << setw(14) << "Matrix M:" << endl;
 	displayfloat(mat,N,N);
	cout << setw(14) << "Matrix M^T:" << endl;
	displayfloat(mat_transpose,N,N);
	
	cout << setw(14) << "Matrix M^T * M:" << endl;
	multiplyMatrix(mat_transpose, mat);
	
	float mat_result[N][C2];
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<C2; ++j)
		{
			mat_result[i][j] = 0;
			for(int k = 0; k<C1; ++k)
			{
				mat_result[i][j] += mat_transpose[i][k]*mat[k][j];
			}
		}			
	}
	cout << endl;
	return 0;
}