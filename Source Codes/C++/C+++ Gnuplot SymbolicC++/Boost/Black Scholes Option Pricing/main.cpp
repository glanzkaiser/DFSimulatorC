// g++ main.cpp -o result -lboost_iostreams
// to find second derivative with autodiff from boost needs to convert the function to template first.
// Function of interest are to be converted into templates that may accept either double or boost fvar arguments.
// Boost provides custom implementations of trigonometric functions from standard library (sin,cos,tan) suitable for fvar

// Equations and function/variable names are from
// https://en.wikipedia.org/wiki/Greeks_(finance)#Formulas_for_European_option_Greeks

#include <boost/math/differentiation/autodiff.hpp>
#include <iostream>
#include <math.h>

using namespace std;

using namespace boost::math::constants;
using namespace boost::math::differentiation;

// Standard normal cumulative distribution function
template <typename X>
X Phi(X const& x) 
{
	return 0.5 * erfc(-one_div_root_two<X>() * x);
}

enum class CP { call, put };

// Assume zero annual dividend yield (q=0).
template <typename Price, typename Sigma, typename Tau, typename Rate>
promote<Price, Sigma, Tau, Rate> black_scholes_option_price(CP cp,
                                                            double K,
                                                            Price const& S,
                                                            Sigma const& sigma,
                                                            Tau const& tau,
                                                            Rate const& r) 
{
	auto const d1 = (log(S / K) + (r + sigma * sigma / 2) * tau) / (sigma * sqrt(tau));
	auto const d2 = (log(S / K) + (r - sigma * sigma / 2) * tau) / (sigma * sqrt(tau));
	switch (cp) 
	{
		case CP::call:
			return S * Phi(d1) - exp(-r * tau) * K * Phi(d2);
		case CP::put:
			return exp(-r * tau) * K * Phi(-d2) - S * Phi(-d1);
	}
}

int main() 
{
	double const K = 100.0;                    // Strike price.
	auto const S = make_fvar<double, 2>(105);  // Stock price.
	double const sigma = 5;                    // Volatility.
	double const tau = 30.0 / 365;             // Time to expiration in years. (30 days).
	double const r = 1.25 / 100;               // Interest rate.
	auto const call_price = black_scholes_option_price(CP::call, K, S, sigma, tau, r);
	auto const put_price = black_scholes_option_price(CP::put, K, S, sigma, tau, r);

	std::cout << "black-scholes call price = " << call_price.derivative(0) << '\n'
			<< "black-scholes put  price = " << put_price.derivative(0) << '\n'
			<< "call delta = " << call_price.derivative(1) << '\n'
			<< "put  delta = " << put_price.derivative(1) << '\n'
			<< "call gamma = " << call_price.derivative(2) << '\n'
			<< "put  gamma = " << put_price.derivative(2) << '\n';
return 0;
}