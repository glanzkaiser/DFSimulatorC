
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
	gp << "set xrange [0:12]\nset yrange [0:8]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	gp <<"set xtics nomirror (0, '{/:Italic π/2}' 0.5*pi, '{/:Italic π}' pi, '{/:Italic 3π/2}' 1.5*pi,\
		'2{/:Italic π}' 2*pi, '{/:Italic 5π/2}' 2.5*pi, '3{/:Italic π}' 3*pi, '{/:Italic 7π/2}' 3.5*pi,\
      		'4{/:Italic π}' 4*pi, '5{/:Italic π}' 5*pi, '6{/:Italic π}' 6*pi)\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f1(x) = x\n";
	gp << "f(x) = 3.14159 - 2*sin(x)\n";
	gp << "g(x) = 3.14159 - 2*sin(x) - sin(2*x)\n";
	gp << "h(x) = 3.14159 - 2*sin(x)-sin(2*x) - 0.6666*sin(3*x)\n";
	gp << "i(x) = 3.14159 - 2*sin(x)-sin(2*x) - 0.6666*sin(3*x) - 0.5*sin(4*x)\n";	
	gp << "plot f1(x) title 'y = x' lw 2 lc rgb 'black',\
		f(x) title 'y = π - 2 sin x' lw 3 lc rgb 'forest-green', \
		g(x) title 'y = π - (2 sin x + sin 2x)' lw 3 lc rgb 'spring-green', \
		h(x) title 'y = π - (2 sin x + sin 2x + (2/3) sin 3x)' lw 3 lc rgb 'orchid4',\
		i(x) title 'y = π - (2 sin x + sin 2x + (2/3) sin 3x + (2/4) sin 4x)' lw 3 lc rgb 'light-salmon'\n";
	
	return 0;
}