// https://stackoverflow.com/questions/24305090/how-to-visualize-the-intersection-of-surfaces-under-gnuplot
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set parametric\n"; 
	gp << "set hidden3d\n"; // to apply the right setting for intersecting surfaces
	gp << "set samples 101\n"; 
	gp << "set isosamples 101\n"; 
	//gp << "set hidd front\n"; // to apply the right setting for intersecting surfaces
	gp << "set xrange[-5:5]\n set yrange[-5:5]\n set zrange[-5:5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 100,5,1\n"; // pitch,yaw,zoom
	gp << "set multiplot layout 2,1 title 'Intersection of Two Planes in R^{3}'\n"; // multiplot
	gp << "rgb(r,g,b) = int(r)*65536 + int(g)*256 + int(b)\n"; 
	gp << "splot u+v,u,v title 'Plane 1 (u+v,u,v) or (x-y-z=0)' lw 2 lc rgb 'forest-green' ,\
			-2*u-v,u,v title 'Plane 2 (-2u-v,u,v) or (x+2y+z=0)' lw 2 lc rgb 'sienna1'\n";
	gp << "splot (abs(u+v-(-2*u-v)) < 0.3 ? u+v : 1/0), \
			(abs(u-u) < 0.1 ? u : 1/0), \
			(abs(v-v) < 0.1 ? v : 1/0) title 'Intersecting line' lc rgb 'sea-green'\n";
	// The calculation is like this:
	// imagine you want to plot your planes in the intervals x = [-5:5], y = [-5:5] and z = [-5:5], and use 101 samples in each direction:
	// Now, each of the 101 samples corresponds to an interval which has width (5 - (-5))/(101-1) = 0.1. 
	// If you constrain the distance between planes to be below half this threshold for plotting points, 
	// that is (abs(u+v-(-2*u-v)) < 0.3 
	// (abs(u+v-(-2*u-v)) < 0.3  -> we chose to enlarge into 0.3 to make the intersecting line larger
	// (abs(u-u) < 0.1 ? u : 1/0)
	// (abs(v-v) < 0.1 ? v : 1/0) 
	// You will get exactly one point sampled for every interval along every direction
	// where ? something : 1/0 means if condition before ? is satisfied plot something else ignore that point.

	return 0;
}