
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
	gp << "set title 'Fourier Series f(x) = |x|, at interval -π <= x < π' \n";
	gp << "set xrange [-12:12]\nset yrange [-2:6]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	gp <<"set xtics (0, '{/:Italic π/2}' 0.5*pi, '{/:Italic π}' pi, '{/:Italic 3π/2}' 1.5*pi,\
		'2{/:Italic π}' 2*pi, '{/:Italic 5π/2}' 2.5*pi, '3{/:Italic π}' 3*pi, '{/:Italic 7π/2}' 3.5*pi,\
      		'4{/:Italic π}' 4*pi, '5{/:Italic π}' 5*pi, '6{/:Italic π}' 6*pi)\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = 1.570796 - (1.2732395) * (cos(x))\n";
	gp << "g(x) = 1.570796 - (1.2732395) * (cos(x) + 0.1111*cos(3*x))\n";
	gp << "h(x) = 1.570796 - (1.2732395) * (cos(x) + 0.1111*cos(3*x) + 0.04*cos(5*x))\n";
	gp << "i(x) = 1.570796 - (1.2732395) * (cos(x) + 0.1111*cos(3*x) + 0.04*cos(5*x) + 0.0204*cos(7*x) )\n";	
	gp << "plot f(x) title 'y = π/2 - 4/π * (cos x)' lw 3 lc rgb 'forest-green', \
		g(x) title 'y = π/2 - 4/π * (cos x + (1/9) cos 3x)' lw 3 lc rgb 'spring-green', \
		h(x) title 'y = π/2 - 4/π * (cos x + (1/9) cos 3x + (1/25) cos 5x)' lw 3 lc rgb 'orchid4',\
		i(x) title 'y = π/2 - 4/π * (cos x + (1/9) cos 3x + (1/25) cos 5x + (1/49) cos 7x)' lw 3 lc rgb 'light-salmon'\n";
	
	return 0;
}