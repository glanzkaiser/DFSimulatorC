// Program illustrating the use of arg() and abs()
#include <iostream>	 

// for std::complex, std::abs, std::atg
#include <complex> 
using namespace std;

// driver function
int main ()
{ 
// defines the complex number: (3.0+4.0i)
std::complex<double> mycomplex (3.0, 4.0);

// prints the absolute value of the complex number
cout << "The absolute value of " << mycomplex << " is: ";
cout << abs(mycomplex) << endl;

// prints the argument of the complex number
cout << "The argument of " << mycomplex << " is: ";
cout << arg(mycomplex) << endl;

return 0;
}