
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// Don't forget to put "\n" at the end of each line!
	gp << "unset parametric\n"; // To make the plot interactive
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set hidden3d\n"; // to apply the right setting for intersecting surfaces
	gp << "set xrange[-5:5]\n set yrange[-5:5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 100,5,1\n"; // pitch,yaw,zoom
	gp << "rgb(r,g,b) = int(r)*65536 + int(g)*256 + int(b)\n"; 
	gp << "f(x,y) = x-y\n";
	gp << "g(x,y) = -x-2*y\n";
	gp << "splot f(x,y) lw 3 lc rgb 'dark-green' title 'x-y-z=0', g(x,y) lw 3 title 'x+2y+z=0' \n";
	
	return 0;
}