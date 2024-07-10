
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 
// graph a direction field for the differential equation y'=y*sin(x).
// the special filename '++' generates a set of points equally spaced over the x and y plot ranges.
// See 'help special-filenames' for more details on that.
// https://stackoverflow.com/questions/35441630/gnuplot-can-a-function-be-plotted-with-vectors

#include <vector>
#include <cmath>
#include <utility>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;
	
	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-3:3]\nset yrange [-3:3]\n";
	gp << "set samples 30\n";
	gp << "set isosamples 30\n";
	gp << "unset key\n";
	gp << "f(x,y) = y*sin(x)\n";
	gp << "lf(x,y) = sqrt(1+f(x,y)**2)\n";
	gp << "lyf(x,y) = f(x,y)/lf(x,y)\n";
	gp << "set title 'Direction field for dy = y*sin(x) ' \n";
	gp << "plot '++' u 1:2:(0.1/lf($1,$2)):(0.1*lyf($1,$2)) with vectors \n";
			
	return 0;
}