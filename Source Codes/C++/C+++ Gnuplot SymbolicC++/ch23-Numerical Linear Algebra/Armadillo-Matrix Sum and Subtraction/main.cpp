// g++ main.cpp -o result -larmadillo

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
	mat A;
	mat B;
	
	A.load("MatrixA.txt");	
	B.load("MatrixB.txt");

	cout << "Matrix A:" << endl;
	A.print();
	cout << endl;
	cout << "Matrix B:" << endl;
	B.print();

	// determinant
	cout << "det(A): " << det(A) << endl;
	cout << endl;
	cout << "det(B): " << det(B) << endl;
	cout << endl;
	
	// inverse
	cout << "inv(A): " << endl << inv(A) << endl;
	cout << "inv(B): " << endl << inv(B) << endl;
	cout << endl;
	
	// Matrix summation, subtraction and product
	cout << "A+B: " << endl << A+B << endl;
	cout << "A-B: " << endl << A-B << endl;
	cout << "AB: " << endl << A*B << endl;
	
	return 0;
}


