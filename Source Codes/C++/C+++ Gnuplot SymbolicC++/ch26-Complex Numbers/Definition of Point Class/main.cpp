#include <iostream>
#include <complex>

using namespace std;

typedef complex<double> point;

// X-coordinate is equivalent to the real part
// Y-coordinate is equivalent to the imaginary part
#define x real()
#define y imag()

int main()
{
	point P(2.0, 3.0);
	cout << "Point P is: " << P << endl;
	cout << "The X-coordinate of point P is: " << P.x << endl;
	cout << "The Y-coordinate of point P is: " << P.y << endl;

	return 0;
}