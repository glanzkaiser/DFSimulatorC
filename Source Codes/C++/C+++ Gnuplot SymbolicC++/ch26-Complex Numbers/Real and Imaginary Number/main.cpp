// https://www.geeksforgeeks.org/complex-numbers-c-set-1/

// Program illustrating the use of real() and 
// imag() function
#include <iostream>	 

// for std::complex, std::real, std::imag
#include <complex>	 
using namespace std;

// driver function
int main()
{ 
// defines the complex number: (10 + 2i)
std::complex<double> mycomplex(10.0, 2.0);

// prints the real part using the real function
cout << "Complex number: " << real(mycomplex) <<" + (" << imag(mycomplex) << ")i" << endl;

cout << "Real part: " << real(mycomplex) << endl;
cout << "Imaginary part: " << imag(mycomplex) << endl;
return 0;
}
