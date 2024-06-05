
// https://stackoverflow.com/questions/23707979/gnuplot-plotting-points-with-variable-point-types

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
	gp << "set key inside bottom right\n";
	gp << "set xlabel 'Deflection (m)'\n";
	gp << "set ylabel 'Force (kN)'\n";
	gp << "set title 'Some Data'\n";
	gp << "set style line 1 lc rgb 'red' pt 7\n";
	gp << "set style line 2 lc rgb 'blue' pt 5\n";
	
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot  'data.txt' using 1:2 title 'Col-Force' with points ls 1, 'data.txt' using 1:3 title 'Beam-Force' with points ls 2 \n";
		
	return 0;
}