
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
	gp << "set xrange [-10:5]\nset yrange [-3:3]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "i = {0,1}\n";
	gp << "plot real(exp(i*x)), imag(exp(i*x))\n";
		
	// To do parametric plot uncomment below and comment the plot line above
	//gp << "set parametric\n";
	//gp << "plot real(exp(i*t)), imag(exp(i*t))\n";	
	
	return 0;
}