// polar() – It constructs a complex number from magnitude and phase angle. 
// real = magnitude*cosine(phase angle) imaginary = magnitude*sine(phase angle) 


// Program illustrating the use of polar()
#include <iostream>	 

// std::complex, std::polar
#include <complex>
using namespace std;

// driver function
int main ()
{
cout << "The complex whose magnitude is " << 2.0;
cout << " and phase angle is " << 0.5;

// use of polar()
cout << " is " << polar (2.0, 0.5) << endl;

return 0;
}