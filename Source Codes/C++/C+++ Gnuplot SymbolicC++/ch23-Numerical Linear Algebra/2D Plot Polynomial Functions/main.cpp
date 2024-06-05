// Demo of vector plot.
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include <vector>
#include <cmath>
#include <utility>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-50:10]\nset yrange [-960:960]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = (x**3)-(2*x**2) + x + 5\n";
	gp << "g(x) = (x**3)-(2*x**2) + x + 180\n";
	gp << "plot f(x) title 'λ^{3} - 2λ^{2}  + λ + 5 = 0', g(x) title 'λ^{3} - 2λ^{2}  + λ + 5 = -175'\n";

	
	return 0;
}