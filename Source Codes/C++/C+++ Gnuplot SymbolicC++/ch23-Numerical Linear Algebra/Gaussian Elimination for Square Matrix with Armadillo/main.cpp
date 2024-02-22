// g++ -o result main.cpp -larmadillo
// Merci beaucoup Freya..
// C++ program to find the solution of system of linear equations

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

// Driver code
int main(int argc, char** argv)
{
	mat A;
	A.load("matrixA.txt");
	mat B;
	B.load("vectorB.txt");
	mat X;
	X = solve(A,B,solve_opts::force_approx); 
	
	cout <<"Matrix A:" << "\n" << A <<endl;
	cout <<"Vector B:" << "\n" << B <<endl;
	cout <<"Solution:" << "\n" << X <<endl;	

}