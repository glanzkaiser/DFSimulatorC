
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include <cmath>
#include <utility>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-10:10]\nset yrange [-5:5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = 2*sin(x)\n";
	gp << "g(x) = 2*sin(x)-sin(2*x)\n";
	gp << "h(x) = 2*sin(x)-sin(2*x) + 0.6666*sin(3*x)\n";
	gp << "i(x) = 2*sin(x)-sin(2*x) + 0.6666*sin(3*x) - 0.5*sin(4*x)\n";	
	gp << "plot f(x) title 'y = 2 sin x' lw 3 lc rgb 'forest-green', \
		g(x) title 'y = 2 sin x - sin 2x' lw 3 lc rgb 'spring-green', \
		h(x) title 'y = 2 sin x - sin 2x + (2/3) sin 3x' lw 3 lc rgb 'orchid4',\
		i(x) title 'y = 2 sin x - sin 2x + (2/3) sin 3x - (2/4) sin 4x' lw 3 lc rgb 'light-salmon'\n";
	
	return 0;
}