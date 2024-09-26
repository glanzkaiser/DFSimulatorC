
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// Don't forget to put "\n" at the end of each line!
	gp << "unset parametric\n"; // To make the plot interactive
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set hidden3d\n"; // to apply the right setting for intersecting surfaces
	//gp << "set iso 100\n";
	//gp << "set samp 500\n";
	gp << "set xrange[-30:30]\n set yrange[-30:30]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 100,5,1\n"; // pitch,yaw,zoom
	gp << "rgb(r,g,b) = int(r)*65536 + int(g)*256 + int(b)\n"; 
	gp << "a = 5\n";
	gp << "b = 5\n";
	gp << "c = 4\n";
	gp << "f(x,y) = a*x**2 + b*y**2 + c*x*y\n";
	gp << "splot f(x,y) lw 3 lc rgb 'dark-green' title 'f(x,y)=5x^{2} + 5y^{2} + 4xy'\n";
	
	return 0;
}