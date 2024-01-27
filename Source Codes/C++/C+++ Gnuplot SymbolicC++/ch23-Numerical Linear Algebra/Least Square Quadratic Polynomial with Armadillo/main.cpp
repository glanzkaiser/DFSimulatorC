// g++ -o result main.cpp
// Merci beaucoup Freya..
// C++ program to find the least square quadratic polynomial

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

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

// Driver code
int main(int argc, char** argv)
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
	//cout << setw(14) << "Matrix M:" << endl;
 	//displayfloat(mat,N,N);
	//cout << setw(14) << "Matrix M^T:" << endl;
	//displayfloat(mat_transpose,N,N);
	
	arma::mat M(N,N,fill::zeros); //declare matrix M with size of 3 X 3 all have 0 entries with Armadillo.
	arma::mat M_transpose(N,N,fill::zeros); //declare matrix M_transpose with size of 3 X 3 all have 0 entries with Armadillo.
	arma::mat Y(N,1,fill::zeros);
	arma::mat V(N,1,fill::zeros);
	// Fill matrix M from Armadillo with matrix mat from loading textfile
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			M[i+j*N] = mat[i][j];
		}			
	}
	// Fill matrix M_Transpose from Armadillo with matrix mat_transpose from loading textfile
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			M_transpose[i+j*N] = pow(ptrvecx[j],i);
		}			
	}
	
	// Fill vector y from Armadillo from loading textfile vectorY.txt
	for (int i = 0; i < N; ++i)
	{
		Y[i] = ptrvecy[i];			
	}
	V = arma::inv(M_transpose * M)*M_transpose * Y ;

	M.print("M:");
  	cout << endl;
	M_transpose.print("M^T:");
  	cout << endl;
	Y.print("y:");
	cout << endl;

	// determinant and inverse from Armadillo
	cout << "det(M): " << det(M) << endl;
	cout << endl;
	cout << "inv(M): " << endl << arma::inv(M) << endl;
	cout << endl;
	cout << "inv(M^T): " << endl << arma::inv(M_transpose) << endl;
	cout << "inv(M^T * M): " << endl << arma::inv(M_transpose * M) << endl;
	cout << "inv(M^T * M) * M^T: " << endl << arma::inv(M_transpose * M)*M_transpose << endl;
	cout << "v* = inv(M^T * M) * M^T * y : " << endl << arma::inv(M_transpose * M)*M_transpose * Y << endl;
	cout << "Least Square Quadratic Polynomial Fit :" << endl;
	cout << ("y = ");
	printf("%.3f + ", V[0]);
	printf("%.3f x + ", V[1]);
	printf("%.3f x^2  ", V[2]);
	cout <<endl;
	return 0;
}