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
	mat Real;
	mat Complex;
	Real.load("matrixReal.txt");
	Complex.load("matrixComplex.txt");
	cx_mat A(Real,Complex);

	cout <<"Matrix A:" << "\n" << A <<endl;
	
	int n = 3;
	for (int i = 0; i < n; i++) 
	{
		cout <<"\nSubmatrix A" << i+1 << " : " << "\n" << A.submat(0,0,i,i) <<endl;
		cout << "det(Submatrix A" << i+1 << ") = " << det(A.submat(0,0,i,i)) << endl;
	}
	
	return 0;
}