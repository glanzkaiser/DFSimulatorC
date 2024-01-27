// g++ -o result main.cpp 
#include <armadillo>

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
	mat matrixA;
	mat U;
	vec S;
	mat V;
	matrixA.load("MatrixA.txt");	
	
	cout << "Matrix A:" << endl;
	matrixA.print();
	cout << endl;
	
	
	// inverse
	cout << "inv(A): " << endl << svd(U,S,V,matrixA) << endl;
	cout << endl;
	
	
	return 0;
}

