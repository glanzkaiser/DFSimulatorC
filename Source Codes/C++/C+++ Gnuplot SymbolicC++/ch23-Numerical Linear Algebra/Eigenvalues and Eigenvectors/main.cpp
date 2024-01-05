// g++ -o result main.cpp 

#include <eigen3/Eigen/Eigenvalues> // header file
#include <iostream>

int main()
{
Eigen::Matrix<double, 2, 2> A; // declare a real (double) 2x2 matrix
//A << 0, 2, 1, 0; // defined the matrix A
A(0,0) = 3.0;
A(0,1) = 0.0;
A(1,0) = 8.0;
A(1,1) = -1.0;

Eigen::EigenSolver<Eigen::Matrix<double, 2,2> > s(A); // the instance s(A) includes the eigensystem
std::cout << A << std::endl;
std::cout << "eigenvalues:" << std::endl;
std::cout << s.eigenvalues() << std::endl;
std::cout << "eigenvectors=" << std::endl;
std::cout << s.eigenvectors() << std::endl;

return(0);
}
