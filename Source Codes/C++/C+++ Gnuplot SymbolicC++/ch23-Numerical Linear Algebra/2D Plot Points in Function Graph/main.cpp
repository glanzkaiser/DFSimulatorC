
// https://gnuplotting.org/tag/points/

// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 
// Here, we define the starting point to be (0,0) and add to it the values 
// from the first and second column for every line of the data file. 
// Note, that the addition is always performed first, 
// before the resulting point is plotted which means we get no point at (0,0). 

#include <vector>
#include <cmath>
#include <utility>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [4:32]\n";
	gp << "set samples (32 - 4)/4 + 1\n";
	gp << "set xtics 4\n";
	gp << "f(x) = 1 - 0.5**x\n";
	
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot f(x) with linespoints pt 7 ps 2\n";
		
	return 0;
}