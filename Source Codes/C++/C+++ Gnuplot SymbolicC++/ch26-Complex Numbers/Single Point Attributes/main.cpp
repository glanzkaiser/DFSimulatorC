// CPP program to illustrate
// the implementation of single point attributes
#include <iostream>
#include <complex>

using namespace std;

typedef complex<double> point;
#define x real()
#define y imag()

// The constant PI for providing angles in radians
#define PI 3.1415926535897932384626

// Function used to display X and Y coordinates of a point
void displayPoint(point P)
{
	cout << "(" << P.x << ", " << P.y << ")" << endl;
}

int main()
{
	point P(4.0, 3.0);

	// X-Coordinate and Y-coordinate
	cout << "The X-coordinate of point P is: " << P.x << endl;
	cout << "The Y-coordinate of point P is: " << P.y << endl;

	// Distances of P from origin
	cout << "The distance of point P from origin is: " << abs(P) <<endl;
	cout << "The squared distance of point P from origin is: " << norm(P) <<endl;

	// Tangent Angle made by OP with the X-Axis
	cout << "The angle made by OP with the X-Axis is: "
		<< arg(P) << " radians" << endl;
	cout << "The angle made by OP with the X-Axis is: "
		<< arg(P)*(180/PI) << " degrees" << endl;


	// Rotation of P about origin
	// The angle of rotation = 90 degrees
	point P_rotated = P * polar(1.0, PI/2);
	cout<<"The point P on rotating 90 degrees anti-clockwise becomes: P_rotated"; 
	displayPoint(P_rotated);

	return 0;
}