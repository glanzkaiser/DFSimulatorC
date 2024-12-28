// g++ -o result main.cpp -larmadillo
// Merci beaucoup Freya..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>

using namespace std;
using namespace arma;

// Driver code
int main(int argc, char** argv)
{
	mat B;
	mat C;
	B.load("matrixB.txt");
	C.load("matrixC.txt");
	
	cout <<"Matrix A_1:" << "\n" << B <<endl;
	cout <<"Matrix A_2:" << "\n" << C <<endl;
	
	cout << "det(A_1) = " << det(B) << endl;
	cout << "det(A_2) = " << det(C) << endl;
	cout << "rank(A_1) = " << arma::rank(B) << endl;
	cout << "rank(A_2) = " << arma::rank(C) << endl;

	cout << "\n(A_1)^{-1} =\n " << inv(B) << endl;
	cout << "\n(A_2)^{-1} =\n " << inv(C) << endl;
	
	return 0;
}