// g++ main.cpp -o result -lboost_iostreams
// to find second derivative with autodiff from boost needs to convert the function to template first.
// Function of interest are to be converted into templates that may accept either double or boost fvar arguments.
// Boost provides custom implementations of trigonometric functions from standard library (sin,cos,tan) suitable for fvar

#include <boost/math/differentiation/autodiff.hpp>
#include <iostream>
#include <math.h>

using namespace std;

template <typename T>
T get_x_coordinate(T const & phi)
{
	return phi;
}

int main()
{
	float var_x= 30;
	double const phi{var_x};
	auto const x{::boost::math::differentiation::make_fvar<double, 5>(phi)}; // to find derivative till order 5
	auto const dx{get_x_coordinate(x*x*x)};
	cout << "x = " << var_x <<endl;
	cout << "x in autodiff = " << x << endl;
	cout << "dx in autodiff = " << dx << endl;
	cout << "f(x) = x*x*x = " << dx.derivative(0) << endl; // sin(phi) / sin(theta*DEGTORAD)
	cout << "d f(x) = 3*x*x = " << dx.derivative(1) << endl; // d sin(phi)/d phi = cos(phi)
	cout << "d(d f(x))  = 6*x = " << dx.derivative(2) << endl; // -sin(phi)
	cout << "d^2(d f(x)) = " << dx.derivative(3) << endl; // - cos(phi)
	cout << "d^3(d f(x)) = " << dx.derivative(4) << endl; // sin(phi)
	cout << "d^4(d f(x)) = " << dx.derivative(5) << endl; // cos(phi)
	return 0;
}