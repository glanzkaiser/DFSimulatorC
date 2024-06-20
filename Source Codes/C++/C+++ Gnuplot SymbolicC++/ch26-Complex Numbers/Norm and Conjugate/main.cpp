// example to illustrate the use of norm() and conj()
#include <iostream>	 
// for std::complex, std::norm, std::conj
#include <complex> 
using namespace std;

// driver function
int main ()
{ 
// initializing the complex: (3.0+4.0i)
std::complex<double> mycomplex (3.0, 4.0);

// use of norm()
cout << "The norm of " << mycomplex << " is " 
	<< norm(mycomplex) <<endl;

cout << "The conjugate of " << mycomplex << " is: ";

// use of conj()
cout << conj(mycomplex) << endl;

return 0;
}
