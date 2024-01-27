// g++ main.cpp -o result -lboost_iostreams
// to find second derivative with autodiff from boost needs to convert the function to template first.
// Function of interest are to be converted into templates that may accept either double or boost fvar arguments.
// Boost provides custom implementations of trigonometric functions from standard library (sin,cos,tan) suitable for fvar

#include <boost/math/differentiation/autodiff.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <iostream>

using namespace std;

template <typename T>
T fourth_power(T const& x) 
{
	T x4 = x * x;  // retval in operator*() uses x4's memory via NRVO.
	x4 *= x4;      // No copies of x4 are made within operator*=() even when squaring.
	return x4;     // x4 uses y's memory in main() via NRVO.
}

int main() 
{
	using namespace boost::math::differentiation;

	constexpr unsigned Order = 5;                  // Highest order derivative to be calculated.
	auto const x = make_fvar<double, Order>(2.0);  // Find derivatives at x=2.
	auto const y = fourth_power(x);
	for (unsigned i = 0; i <= Order; ++i)
	{
		std::cout << "y.derivative(" << i << ") = " << y.derivative(i) << std::endl;
	}
	return 0;
}