// g++ -o result main.cpp
// Merci beaucoup Freya..
// C++ program to find the regression line

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include<bits/stdc++.h>
using namespace std;

const int N = 3;
const int C1 = 3;
const int C2 = 3;
 
// Function to calculate b
double calculateB(int x[], int y[], int n)
{     
	// sum of array x
	int sx = accumulate(x, x + n, 0);
	// sum of array y
	int sy = accumulate(y, y + n, 0);

	// for sum of product of x and y
	int sxsy = 0;

	// sum of square of x
	int sx2 = 0;
	for(int i = 0; i < n; i++) 
	{
	sxsy += x[i] * y[i];
	sx2 += x[i] * x[i];
	}
	double b = (double)(n * sxsy - sx * sy) /
			(n * sx2 - sx * sx);
 
	return b;
}

double calculateA(int X[], int Y[], int n)
{     
	double b = calculateB(X, Y, n);

	int meanX = accumulate(X, X + n, 0) / n;
	int meanY = accumulate(Y, Y + n, 0) / n;

	// Calculating a
	double a = meanY - b * meanX;
 
	return a;
}
 
// Function to find the least regression line
void leastRegLine(int X[], int Y[], int n)
{ 
	// Finding b
	double b = calculateB(X, Y, n);

	int meanX = accumulate(X, X + n, 0) / n;
	int meanY = accumulate(Y, Y + n, 0) / n;

	// Calculating a
	double a = meanY - b * meanX;

	// Printing regression line
	cout << ("Regression line:") << endl;
	cout << ("Y = ");
	printf("%.3f + ", a);
	printf("%.3f *X", b);
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

void display(int mat[N][N], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
	for (int j = 0; j < col; j++)
		cout<<setw(6)  << mat[i][j]<<"\t";	
		cout<<endl;
	}
	cout<<endl;
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


void cofactor(int M[N][N], int temp[N][N], int p,int q, int n)
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

void cofactorfloat(float M[N][N], float temp[N][N], int p,int q, int n)
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

int determinantOfMatrix(int M[N][N], int dimension)
{
	int Det = 0;

	if (dimension == 1)
		return M[0][0];

	int cofactorMat[N][N];
	int sign = 1;

	for (int firstRow = 0; firstRow < dimension; firstRow++)
	{
	cofactor(M, cofactorMat, 0, firstRow, dimension);
	Det += sign * M[0][firstRow] * determinantOfMatrix(cofactorMat, dimension - 1);
	sign = -sign;
	}
	return Det;
}

int determinantOfMatrixfloat(float M[N][N], int dimension)
{
	int Det = 0;

	if (dimension == 1)
		return M[0][0];

	float cofactorMat[N][N];
	int sign = 1;

	for (int firstRow = 0; firstRow < dimension; firstRow++)
	{
	cofactorfloat(M, cofactorMat, 0, firstRow, dimension);
	Det += sign * M[0][firstRow] * determinantOfMatrixfloat(cofactorMat, dimension - 1);
	sign = -sign;
	}
	return Det;
}

void ADJ(int M[N][N],int adj[N][N])
//to find adjoint matrix 
{
	if (N == 1) 
	{
	adj[0][0] = 1; 
	return;
	}   
	int s = 1,
	t[N][N];

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


void ADJfloat(float M[N][N],int adj[N][N])
//to find adjoint matrix 
{
	if (N == 1) 
	{
	adj[0][0] = 1; 
	return;
	}   
	float s = 1,
	t[N][N];

	for (int i=0; i<N; i++) 
	{
		for (int j=0; j<N; j++) 
		{
		 //To get cofactor of M[i][j]
		cofactorfloat(M, t, i, j, N);
		s = ((i+j)%2==0)? 1: -1; //sign of adj[j][i] positive if sum of row and column indexes is even.
		adj[j][i] = (s)*(determinantOfMatrixfloat(t, N-1)); //Interchange rows and columns to get the transpose of the cofactor matrix
		}
	}
}

bool INV(int M[N][N], float inv[N][N]) 
{
	int det = determinantOfMatrix(M, N);
	if (det == 0) 
	{
	cout << "can't find its inverse";
	cout<<endl;
	return false;
	}
	int adj[N][N]; 
	ADJ(M, adj);

	for (int i=0; i<N; i++) 
	{
		for (int j=0; j<N; j++) inv[i][j] = adj[i][j]/float(det);
	}
	return true;
}


bool INVfloat(float M[N][N], float inv[N][N]) 
{
	int det = determinantOfMatrixfloat(M, N);
	if (det == 0) 
	{
	cout << "can't find its inverse";
	cout<<endl;
	return false;
	}
	int adj[N][N]; 
	ADJfloat(M, adj);

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

void multiplyMatrix(float matrix1[][C1], float matrix2[][C2])
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
	
	float inv[N][N]; //declare the inverse matrix 
	
	//cout << setw(14) << "Inverse of Matrix M: " << endl;
	//if (INV(mat, inv)) 
	//{
	//	displayfloat(inv,N,N);
	//}

	cout << setw(14) << "Matrix M^T * M:" << endl;
	multiplyMatrix(mat_transpose, mat);
	
	// change int mat_result to float mat_result and work out with INV function
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
	cout << setw(14) << "Integer term of (M^T * M): " << endl;
	displayfloat(mat_result,N,N);
	
	float inv_matresult[N][N]; //declare the inverse matrix 
	cout << setw(14) << "Inverse of Matrix (M^T * M): " << endl;
	if (INVfloat(mat_result, inv)) 
	{
		displayfloat(inv_matresult,N,N);
	}
	
	int leontief[N][N] = {{1,0,2},{-3,4,6},{-1,-2,3}};
	display(leontief,N,N);
	int inv_leontief[N][N]; //declare the inverse matrix 
	cout << setw(14) << "Inverse of Leontief Matrix : " << endl;
	if (INV(leontief, inv)) 
	{
		display(inv_leontief,N,N);
	}

	int mat_result2[N][C2];
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<C2; ++j)
		{
			mat_result[i][j] = 0;
			for(int k = 0; k<C1; ++k)
			{
				mat_result2[i][j] += inv_matresult[i][k]*mat_transpose[k][j];
			}
		}			
	}
	cout << setw(14) << "Matrix inv(M^T * M)*M^T:" << endl;
	
	display(mat_result2,N,N);

	float v[N][N];
	float V[N];
	for (int i = 0; i < N; ++i)
	{
		V[i] = 0;
	}
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			v[i][j] = 0;	
		}		
	}	
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			v[i][j] += mat_result2[i][j] * ptrvecy[j];
		}
	}	

	cout << endl;
	cout << "v* = inv(M^T * M)*M^T * y : " << endl;
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			V[i] += v[i][j] ;
		}
		cout << V[i] << endl;
	}
	// End of line for computing v*

	cout << endl;
	cout << "Vector / Data X: " << setw(30) << "Vector / Data Y: " << endl;
	for (int i = 0; i < N; ++i)
	{
		cout <<ptrvecx[i]<< "\t \t \t \t" << ptrvecy[i] << endl;	
	}	
	cout << endl;
	// Statistical data
	int X[N]; // declare an array name X with size of N
	int Y[N];  //int Y[] = { 10, 20, 30 };
	
	for (int i = 0; i < N; ++i)
	{
		X[i] = ptrvecx[i];
		Y[i] = ptrvecy[i];	
	}	
	int n = N;	//int n = sizeof(X) / sizeof(X[0]);
	double a = calculateA(X, Y, n);
	cout << "a = " << a << endl;
	cout << endl;
	double b = calculateB(X, Y, n);
	cout << "b = " << b << endl;
	cout << endl;
	leastRegLine(X, Y, n);
	cout << endl;
	
}