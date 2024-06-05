// http://yang.amp.i.kyoto-u.ac.jp/~yyama/computer/FAQ/eigen/eigensystem.html
// g++ -o result main.cpp 

#include <eigen3/Eigen/Eigenvalues> // header file
#include <iostream>
#include <complex>

int main()
{
std::complex<double> I(0.0, 1.0); 
Eigen::Matrix<std::complex<double>, 3, 3> A;  // declare a real (double) 2x2 matrix
// defined the matrix A
//A << 0.0, I, -I, 0.0; 
A << 0,1,0,  
	0,0,1,  
	4,-17,8;

Eigen::ComplexEigenSolver<Eigen::Matrix<std::complex<double>, 3,3> > s(A);  // the instance s(A) includes the eigensystem
std::cout << "The 1st eigenvalue and eigenvector" << std::endl;
std::cout << real(s.eigenvalues()(0)) << " " << imag(s.eigenvalues()(0)) << std::endl;
std::cout << real(s.eigenvectors()(0,0)) << " " << imag(s.eigenvectors()(0,0)) << std::endl;
std::cout << real(s.eigenvectors()(1,0)) << " " << imag(s.eigenvectors()(1,0)) << std::endl;

std::cout << "The 2nd eigenvalue and eigenvector" << std::endl;
std::cout << real(s.eigenvalues()(1)) << " " << imag(s.eigenvalues()(1)) << std::endl;
std::cout << real(s.eigenvectors()(0,1)) << " " << imag(s.eigenvectors()(0,1)) << std::endl;
std::cout << real(s.eigenvectors()(1,1)) << " " << imag(s.eigenvectors()(1,1)) << std::endl;

std::cout << "The 3rd eigenvalue and eigenvector" << std::endl;
std::cout << real(s.eigenvalues()(2)) << " " << imag(s.eigenvalues()(2)) << std::endl;
std::cout << real(s.eigenvectors()(0,2)) << " " << imag(s.eigenvectors()(0,2)) << std::endl;
std::cout << real(s.eigenvectors()(1,2)) << " " << imag(s.eigenvectors()(1,2)) << std::endl;

return(0);
}
