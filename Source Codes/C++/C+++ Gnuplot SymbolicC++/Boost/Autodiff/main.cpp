// g++ main.cpp -o result -lboost_iostreams
// to find second derivative with autodiff from boost needs to convert the function to template first.
// Function of interest are to be converted into templates that may accept either double or boost fvar arguments.
// Boost provides custom implementations of trigonometric functions from standard library (sin,cos,tan) suitable for fvar

#include <boost/math/differentiation/autodiff.hpp>
#include <iostream>
#include <math.h>

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

using namespace std;

constexpr double const radius{2.5};

template <typename T>
T get_x_coordinate(T const & phi)
{
	//return radius * cos(phi);
	return sin(phi);
}

int main()
{
	float theta = 30;
	double const phi{theta*DEGTORAD};
	auto const x{::boost::math::differentiation::make_fvar<double, 5>(phi)}; // to find derivative till order 5
	auto const dx{get_x_coordinate(x)};
	cout << "radius = " << radius << endl;
	cout << "degree = " << theta <<endl;
	cout << "phi = " << phi <<endl;
	cout << "sin(phi) = " << sin(phi) << endl;
	cout << "cos(phi) = " << cos(phi) << endl;
	cout << "x = " << x << endl;
	cout << "dx = " << dx << endl;
	cout << "x = " << dx.derivative(0) << endl; // sin(phi) / sin(theta*DEGTORAD)
	cout << "dx = " << dx.derivative(1) << endl; // d sin(phi)/d phi = cos(phi)
	cout << "d(dx) = " << dx.derivative(2) << endl; // -sin(phi)
	cout << "d^2(dx) = " << dx.derivative(3) << endl; // - cos(phi)
	cout << "d^3(dx) = " << dx.derivative(4) << endl; // sin(phi)
	cout << "d^4(dx) = " << dx.derivative(5) << endl; // cos(phi)
	return 0;
}