// http://yang.amp.i.kyoto-u.ac.jp/~yyama/computer/FAQ/eigen/eigensystem.html
// https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html

// g++ -o result main.cpp 

#include <eigen3/Eigen/Eigenvalues> // header file
#include <iostream>

using namespace std;

int main()
{
Eigen::Matrix<double, 3, 3> A; // declare a real (double) 3x3 matrix
// defined the matrix A
A << 0,1,0,  
	0,0,1,  
	4,-17,8;
/*
A(0,0) = 0.0;
A(0,1) = 1.0;
A(0,2) = 0.0;

A(1,0) = 0.0;
A(1,1) = 0.0;
A(1,2) = 1.0;

A(2,0) = 4.0;
A(2,1) = -17.0;
A(2,2) = 8.0;

*/

Eigen::EigenSolver<Eigen::Matrix<double, 3,3> > s(A); // the instance s(A) includes the eigensystem
cout << "Matrix A:\n" << A << endl;
cout << endl;
cout << "Eigenvalues:" << endl;

int n = 3;
for (int i = 1; i <= n; i++) 
	{
		cout << "λ_" << i << " = " << real(s.eigenvalues()(i-1)) << " + " << imag(s.eigenvalues()(i-1)) << "i" << endl;
	}

//cout << s.eigenvalues() << endl;

cout << endl;
cout << "Eigenvectors:" << endl;

//cout << s.eigenvectors() << endl;

for (int i = 1; i <= n; i++) 
	{
		cout << "x[λ_" << i << "] = (" << real(s.eigenvectors()(0,i-1)) << " + " << imag(s.eigenvectors()(0,i-1)) << "i" ;
		cout << ", " << real(s.eigenvectors()(1,i-1)) << " + " << imag(s.eigenvectors()(1,i-1)) << "i" ;
		cout << ", " << real(s.eigenvectors()(2,i-1)) << " + " << imag(s.eigenvectors()(2,i-1)) << "i )" << endl;
		cout << endl;
	}

return(0);
}
