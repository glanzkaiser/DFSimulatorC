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

const int N = 5;
const int C1 = 3;
const int C2 = 5;

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
	float* ptrvecx;
	ptrvecx = vecx();
	float* ptrvecy;
	ptrvecy = vecy();
	
	arma::mat M(N,C1,fill::zeros); //declare matrix M with size of N X C1 all have 0 entries with Armadillo.
	arma::mat M_transpose(C1,C2,fill::zeros); //declare matrix M_transpose with size of C1 X C2 all have 0 entries with Armadillo.
	arma::mat Y(N,1,fill::zeros);
	arma::mat V(N,1,fill::zeros);
	// Fill matrix M from Armadillo with matrix mat from loading textfile
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<C1; ++j)
		{
			M[i+j*N] = pow(ptrvecx[i],j);
		}			
	}	
	
	M_transpose = M.t();
	
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
	cout << "det(M^T * M): " << det(M_transpose*M) << endl;
	cout << endl;
	cout << "inv(M^T * M): " << endl << arma::inv(M_transpose * M) << endl;
	cout << "inv(M^T * M) * M^T: " << endl << arma::inv(M_transpose * M)*M_transpose << endl;
	cout << "v* = inv(M^T * M) * M^T * y : " << endl << arma::inv(M_transpose * M)*M_transpose * Y << endl;
	cout << "Least Square Quadratic Polynomial Fit :" << endl;
	cout << ("y = ");
	printf("%.3f + ", V[0]);
	printf("%.3f x + ", V[1]);
	printf("%.3f x^2 ", V[2]);
	cout <<endl;
}