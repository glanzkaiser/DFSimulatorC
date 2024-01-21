// Demo of vector plot and computation.
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include <iostream> 
#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>
#include <bits/stdc++.h>

#include "gnuplot-iostream.h"

using namespace std;

int n = 3;
 
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

int main() {
	Gnuplot gp;

	float u1 = 3;
	float u2 = 0;
	float u3 = 0;

	float v1 = 0;
	float v2 = 4;
	float v3 = 0;

	float vect_u[] = { u1, u2, u3 };
	float vect_v[] = { v1, v2, v3 };
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

	// We use a separate container for each column, like so:
	std::vector<double> pts_B_x;
	std::vector<double> pts_B_y;
	std::vector<double> pts_B_z;
	std::vector<double> pts_B_dx;
	std::vector<double> pts_B_dy;
	std::vector<double> pts_B_dz;
	std::vector<double> pts_C_x;
	std::vector<double> pts_C_y;
	std::vector<double> pts_C_z;
	std::vector<double> pts_C_dx;
	std::vector<double> pts_C_dy;
	std::vector<double> pts_C_dz;
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_z;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;	
	std::vector<double> pts_D_dz;	
	
	float o = 0;

	// Create a vector with origin at (0,0,0) and terminal point at (u1,u2,u3)
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_z .push_back(o);
	pts_B_dx.push_back(u1);
	pts_B_dy.push_back(u2);
	pts_B_dz.push_back(u3);
	// Create a vector with origin at (0,0) and terminal point at (v1,v2,v3)
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_z .push_back(o);
	pts_C_dx.push_back(v1);
	pts_C_dy.push_back(v2);
	pts_C_dz.push_back(v3);
	// Create a vector from cross product of vectors u and v
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(cross_P[0]);
	pts_D_dy.push_back(cross_P[1]);
	pts_D_dz.push_back(cross_P[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1:3]\nset yrange [-1:3]\nset zrange [-1:5]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '-' with vectors title 'v', '-' with vectors title 'w', '-' with linespoints title 'v x w'\n";
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
}