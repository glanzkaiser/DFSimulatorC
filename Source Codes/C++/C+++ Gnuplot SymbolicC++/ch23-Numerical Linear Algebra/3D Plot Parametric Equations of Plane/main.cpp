// Demo of vector plot.
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// Don't forget to put "\n" at the end of each line!
	gp << "set parametric\n";
	//gp << "set xrange[-10:20]\n set yrange[-6:6]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 100,5,1\n"; // pitch,yaw,zoom
	gp << "f(x,y) = (y-x+5)/2\n";
	gp << "splot 5 + u - 2*v, u, v title 'plane'\n";
	//gp << "splot f(x,y) title 'plane',point us (1):(1):(6) title '(x,y,z,)' ps 2 lc 2 pt  6\n";
	
	return 0;
}