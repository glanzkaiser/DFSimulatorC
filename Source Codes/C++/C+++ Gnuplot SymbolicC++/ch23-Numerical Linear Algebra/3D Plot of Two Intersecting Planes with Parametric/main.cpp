// Demo of vector plot.
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set parametric\n"; 
	gp << "set hidden3d\n"; // to apply the right setting for intersecting surfaces
	gp << "set samples 25\n"; 
	gp << "set isosamples 25\n"; 
	//gp << "set hidd front\n"; // to apply the right setting for intersecting surfaces
	gp << "set xrange[-1:1]\n set yrange[-1:1]\n set zrange[-1:1]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 100,5,1\n"; // pitch,yaw,zoom
	//gp << "set multiplot layout 2,1 title 'Intersection of Two Planes in R^{3}'\n"; // multiplot
	gp << "rgb(r,g,b) = int(r)*65536 + int(g)*256 + int(b)\n"; 
	gp << "splot u,v,0 title 'Plane 1 (u,v,0)' lw 2 lc rgb 'forest-green' , u,0,v title 'Plane 2 (u,0,v)' lw 2\n";
	//gp << "splot (abs(u-u) < 0.01 ? u : 1/0), \
			(abs(v-0.) < 0.01 ? v : 1/0), \
			(abs(v-0.) < 0.01 ? 0 : 1/0) title 'Intersecting line'\n";

	return 0;
}