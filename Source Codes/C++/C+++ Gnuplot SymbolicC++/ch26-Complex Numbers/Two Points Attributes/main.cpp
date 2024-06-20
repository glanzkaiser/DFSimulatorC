// CPP program to illustrate 
// the implementation of two point attributes
#include <iostream>
#include <complex>

using namespace std;

typedef complex<double> point;
#define x real()
#define y imag()

// Constant PI for providing angles in radians
#define PI 3.1415926535897932384626

// Function used to display X and Y coordinates of a point
void displayPoint(point P)
{
	cout << "(" << P.x << ", " << P.y << ")" << endl;
}

int main()
{
	point P(2.0, 3.0);
	point Q(3.0, 4.0);
	
	cout << "P : "; displayPoint(P);
	cout << "Q : "; displayPoint(Q);
	
	// Addition and Subtraction
	cout << "Addition of P and Q is: P+Q"; displayPoint(P+Q);
	cout << "Subtraction of P and Q is: P-Q"; displayPoint(P-Q);

	// Distances between points P and Q
	cout << "The distance between point P ans Q is: " << abs(P-Q) <<endl;
	cout << "The squared distance between point P ans Q is: " << norm(P-Q) <<endl;

	// Slope of line PQ
	cout << "The angle of elevation for line PQ is: "
		<< arg(Q-P)*(180/PI) << " degrees" << endl;
	cout << "The slope of line PQ is: " << tan(arg(Q-P)) <<endl;

	// Construction of point A
	point A = conj(P)*Q;

	// Dot Product and Cross Product
	cout << "The dot product P.Q is: " << A.x << endl;
	cout << "The magnitude of cross product PxQ is: " << abs(A.y) << endl;

	return 0;
}