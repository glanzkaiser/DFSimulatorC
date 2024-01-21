// g++ -o result main.cpp 
// only work for R3 / 3 dimensional vector

#include <iostream> 
#include<time.h>
#include <bits/stdc++.h>
#define n 3
 
using namespace std;
 
// Function that return
// dot product of two vector array.
int dotProduct(float vect_u[], float vect_v[])
{
	float product = 0;
	// Loop for calculate dot product
	for (int i = 0; i < n; i++)
	{
	product = product + vect_u[i] * vect_v[i];
	}
	return product;
}
 
// Function to find
// cross product of two vector array.
void crossProduct(float vect_u[], float vect_v[], float cross_P[]) 
{
	cross_P[0] = vect_u[1] * vect_v[2] - vect_u[2] * vect_v[1];
	cross_P[1] = vect_u[2] * vect_v[0] - vect_u[0] * vect_v[2];
	cross_P[2] = vect_u[0] * vect_v[1] - vect_u[1] * vect_v[0];
}
 
// Driver function
int main()
{
	time_t seconds;
	time(&seconds);

	//srand((unsigned int) seconds);

	float vect_u[] = { 1, 2, -2 };
	float vect_v[] = { 3, 0, 1 };
	float cross_P[n];
	// dotProduct function call
	cout << "Vector u:" << setw(15) << "vector v:" << endl;
	
	for (int i = 0; i < n; i++) 
	{
		cout << vect_u[i]  << "\t" << "\t" << vect_v[i] ;
		cout << endl;
	}
	cout<<endl;

	cout << "Dot product:";
	cout << dotProduct(vect_u, vect_v) << endl;

	// crossProduct function call
	cout << "Cross product: (";
	crossProduct(vect_u, vect_v, cross_P);
	
	// Loop that print
	// cross product of two vector array.
	for (int i = 0; i < n-1; i++)
	{ 
	cout << cross_P[i] << ", ";
	}
	cout << cross_P[n-1] ; // for better looking display of result
	cout << ")"  << endl;

	cout << endl;
	cout << "time (in seconds):" << time << endl ;
	cout << endl;
	return 0;
}
