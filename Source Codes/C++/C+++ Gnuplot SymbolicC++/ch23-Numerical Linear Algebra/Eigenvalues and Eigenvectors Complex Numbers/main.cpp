// http://yang.amp.i.kyoto-u.ac.jp/~yyama/computer/FAQ/eigen/eigensystem.html
// g++ -o result main.cpp 

#include <eigen3/Eigen/Eigenvalues> // header file
#include <iostream>
#include <complex>

int main()
{
std::complex<double> I(0.0, 1.0);  // imaginary unit
Eigen::Matrix<std::complex<double>, 2, 2> A;  // declare a real (double) 2x2 matrix
// defined the matrix A
A << 0.0, I, -I, 0.0; 

Eigen::ComplexEigenSolver<Eigen::Matrix<std::complex<double>, 2,2> > s(A);  
std::cout << A << std::endl;
std::cout << "eigenvalues:" << std::endl;
std::cout << s.eigenvalues() << std::endl;
std::cout << "eigenvectors=" << std::endl;
std::cout << s.eigenvectors() << std::endl;

return(0);
}
