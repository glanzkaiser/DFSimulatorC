// Illustrating the use of sqrt()
#include <iostream>
using namespace std;

// For std::complex, std::sqrt
#include <complex>

// driver program
int main()
{ 
	// use of sqrt()
	cout << "Square root of -4 is "
		<< sqrt(std::complex<double>(-4, 0)) << endl
		<< "Square root of (-4,-0), the other side of the cut, is "
		<< sqrt(std::complex<double>(-4, -0.0)) << endl;
}