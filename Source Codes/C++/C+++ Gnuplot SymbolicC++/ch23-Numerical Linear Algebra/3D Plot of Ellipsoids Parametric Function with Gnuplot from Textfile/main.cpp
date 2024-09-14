
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// Don't forget to put "\n" at the end of each line!
	gp << "datafile ='ellipsoids.dat' \n"; 
	gp << "stats datafile nooutput \n"; 
	gp << "num_rows = STATS_records \n"; 
	gp << "array centers_x[num_rows] \n"; 
	gp << "array centers_y[num_rows] \n"; 
	gp << "array centers_z[num_rows] \n"; 

	gp << "row = 1 \n"; 
	gp << "stats datafile using (centers_x[row]=$1,\
						      centers_y[row]=$2,\
						      centers_z[row]=$3,\
						      row = row + 1) nooutput\n"; 
	
	gp << "Rx = 0.2 \n"; 
	gp << "Ry = 0.3 \n"; 
	gp << "Rz = 0.7 \n"; 
		
	gp << "set parametric\n"; // To make the plot interactive
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	//gp << "set hidden3d\n"; // to apply the right setting for intersecting surfaces
	gp << "set urange[-pi/2:pi/2]\n set vrange[0:2*pi]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 100,5,1\n"; // pitch,yaw,zoom
	gp << "rgb(r,g,b) = int(r)*65536 + int(g)*256 + int(b)\n"; 
	gp << "splot datafile using 1:2:3 title 'Ellipsoids' with points ps 2 pt 7,\
			for [i=1:num_rows] centers_x[i] + Rx*cos(u)*cos(v),\
							centers_y[i] + Ry*cos(u)*sin(v),\
							centers_z[i] + Rz*sin(u) notitle\n";
	
	return 0;
}