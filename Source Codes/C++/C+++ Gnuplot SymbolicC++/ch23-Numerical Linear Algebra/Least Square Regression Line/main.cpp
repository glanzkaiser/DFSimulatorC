// g++ -o result main.cpp
// https://www.tutorialspoint.com/cplusplus-program-to-find-inverse-of-a-graph-matrix
// Merci beaucoup Freya..
// C++ program to find the regression line

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
using namespace std;

const int N = 3;
 
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
 
int* vecx() {
	static int x[N];
	std::fstream in("vectorX.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			x[i] =vectortiles[i];	
	}	
	return x;
}

int* vecy() {
	static int y[N];
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
int main()
{
	int* ptrvecx;
	ptrvecx = vecx();
	int* ptrvecy;
	ptrvecy = vecy();
	
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