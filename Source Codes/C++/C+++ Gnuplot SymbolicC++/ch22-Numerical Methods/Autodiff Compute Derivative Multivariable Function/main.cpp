// g++ main.cpp -o result -lboost_iostreams
// to find second derivative with autodiff from boost needs to convert the function to template first.
// Function of interest are to be converted into templates that may accept either double or boost fvar arguments.
// Boost provides custom implementations of trigonometric functions from standard library (sin,cos,tan) suitable for fvar

#include <boost/math/differentiation/autodiff.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <iostream>

using namespace boost::math::differentiation;
using namespace std;

template <typename W, typename X, typename Y, typename Z>
promote<W, X, Y, Z> f(const W& w, const X& x, const Y& y, const Z& z) 
{
	using namespace std;
	return exp(w * sin(x * log(y) / z) + sqrt(w * z / (x * y))) + w * w / tan(z);
}

int main() 
{
	using float50 = boost::multiprecision::cpp_bin_float_50;

	constexpr unsigned Nw = 3;  // Max order of derivative to calculate for w
	constexpr unsigned Nx = 2;  // Max order of derivative to calculate for x
	constexpr unsigned Ny = 4;  // Max order of derivative to calculate for y
	constexpr unsigned Nz = 3;  // Max order of derivative to calculate for z
	// Declare 4 independent variables together into a std::tuple.
	auto const variables = make_ftuple<float50, Nw, Nx, Ny, Nz>(11, 12, 13, 14);
	auto const& w = std::get<0>(variables);  // Up to Nw derivatives at w=11
	auto const& x = std::get<1>(variables);  // Up to Nx derivatives at x=12
	auto const& y = std::get<2>(variables);  // Up to Ny derivatives at y=13
	auto const& z = std::get<3>(variables);  // Up to Nz derivatives at z=14
	auto const v = f(w, x, y, z);
	// Calculated from Mathematica symbolic differentiation.
	float50 const answer("1976.319600747797717779881875290418720908121189218755");
	cout << setprecision(std::numeric_limits<float50>::digits10)
		<< "mathematica   : " << answer << '\n'
		<< "autodiff      : " << v.derivative(Nw, Nx, Ny, Nz) << '\n'
		<< setprecision(3)
		<< "relative error: " << (v.derivative(Nw, Nx, Ny, Nz) / answer - 1) << '\n';
	return 0;
}


