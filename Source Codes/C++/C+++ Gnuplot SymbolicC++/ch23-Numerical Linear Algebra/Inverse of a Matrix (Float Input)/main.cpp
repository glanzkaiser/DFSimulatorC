// g++ -o result main.cpp
// https://www.tutorialspoint.com/cplusplus-program-to-find-inverse-of-a-graph-matrix

#include <iomanip> // to declare the manipulator of setprecision()
#include<bits/stdc++.h>
using namespace std;
#define N 3

void cofactor(float M[N][N], float temp[N][N], int p,int q, int n)
{
	int i = 0, j = 0;
	for (int row = 0; row < n; row++)
	{		
		for (int column = 0; column < n; column++)
		{
			if (row != p && column != q)
			{
				temp[i][j++] = M[row][column];
				if (j == n - 1)
				{
				j = 0;
				i++;
				}
			}
		}
	}
}

int determinantOfMatrix(float M[N][N], int dimension)
{
	float Det = 0;

	if (dimension == 1)
		return M[0][0];

	float cofactorMat[N][N];
	int sign = 1;

	for (int firstRow = 0; firstRow < dimension; firstRow++)
	{
	cofactor(M, cofactorMat, 0, firstRow, dimension);
	Det += sign * M[0][firstRow] * determinantOfMatrix(cofactorMat, dimension - 1);
	sign = -sign;
	}
	return Det;
}

void ADJ(float M[N][N],float adj[N][N])
//to find adjoint matrix 
{
	if (N == 1) 
	{
	adj[0][0] = 1; 
	return;
	}   
	float s = 1, t[N][N];

	for (int i=0; i<N; i++) 
	{
		for (int j=0; j<N; j++) 
		{
		 //To get cofactor of M[i][j]
		cofactor(M, t, i, j, N);
		s = ((i+j)%2==0)? 1: -1; //sign of adj[j][i] positive if sum of row and column indexes is even.
		adj[j][i] = (s)*(determinantOfMatrix(t, N-1)); //Interchange rows and columns to get the transpose of the cofactor matrix
		}
	}
}

bool INV(float M[N][N], float inv[N][N]) 
{
	int det = determinantOfMatrix(M, N);
	if (det == 0) 
	{
	cout << "can't find its inverse";
	cout<<endl;
	return false;
	}
	float adj[N][N]; 
	ADJ(M, adj);

	for (int i=0; i<N; i++) 
	{
		for (int j=0; j<N; j++) inv[i][j] = adj[i][j]/float(det);
	}
	return true;
}

template<class T> void print(T A[N][N]) //print the matrix. 
{
	for (int i=0; i<N; i++) 
	{ 
		for (int j=0; j<N; j++) 
		{
			cout << A[i][j] << " "; 
		}
		cout<<endl;
	}
}

void display(float M[N][N], int row, int col)
{
for (int i = 0; i < row; i++)
	{
	for (int j = 0; j < col; j++)
		cout<< setw(6) << setprecision(3) << M[i][j]<<"\t";	
		cout<<endl;
	}
	cout<<endl;
}

int main() 
{
	float M[N][N] = {{0.5,-0.1,-0.1},{-0.2,0.5,-0.3},{-0.1,-0.3,0.6}}; // cannot find inverse, better use Armadillo to find inverse for this kind of matrix
	//float M[N][N] = {{0,1,5},{3,-6,9},{2,6,1}};

	float inv[N][N];
	cout << "The input matrix is :\n"; 
	display(M,3,3);
	cout << "The matrix determinant is :\n"; 
	cout << determinantOfMatrix(M, N) << endl;
	//cout << ADJ(M, N) << endl;
	cout << "\nThe Inverse is :\n"; 
	if (INV(M, inv)) 
	{
		display(inv,N,N);
	}
	return 0;
}