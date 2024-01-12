// Demo of vector plot.
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include <vector>
#include <cmath>
#include <utility>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	// We use a separate container for each column, like so:
	std::vector<double> pts_B_x;
	std::vector<double> pts_B_y;
	std::vector<double> pts_B_z;
	std::vector<double> pts_B_dx;
	std::vector<double> pts_B_dy;
	std::vector<double> pts_B_dz;
	std::vector<double> pts_C_x;
	std::vector<double> pts_C_y;
	std::vector<double> pts_C_z;
	std::vector<double> pts_C_dx;
	std::vector<double> pts_C_dy;
	std::vector<double> pts_C_dz;

	// Point-normal equation of the plane:
	// a(x-x0) + b(y-y0) + c(z-z0) = 0
	// we choose the value for (x0,y0,z0) = (0,0,0) the origin	
	float x0 = 0;
	float y0 = 0;
	float z0 = 0;
	// normal n = (a,b,c) = (1,1,-2)
	float a = 1;
	float b = 1;
	float c = -2;
	// to determine the vector that is passing through the origin (0,0,0) and (x,y,z)
	float bx = 1;
	float by = 1;
	float bz = 1;
		
	// Create a vector with origin at (0,0,0) and terminal point at (x,y,z) = (bx,by)
	pts_B_x .push_back(x0);
	pts_B_y .push_back(y0);
	pts_B_z .push_back(z0);
	pts_B_dx.push_back(bx);
	pts_B_dy.push_back(by);
	pts_B_dz.push_back(bz);
	
	// Create a vector with origin at (0,0,0) and terminal point at (a,b,c) as the normal
	pts_C_x .push_back(x0);
	pts_C_y .push_back(y0);
	pts_C_z .push_back(z0);
	pts_C_dx.push_back(a);
	pts_C_dy.push_back(b);
	pts_C_dz.push_back(c);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-2:3]\n set yrange [-1:2]\n set zrange [-2:5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 60,5,1\n"; // pitch,yaw,zoom
	gp << "g(x,y) = x \n";
	gp << "h(x,y) = y \n";
	// h(x,y) title 'z=y',  g(x,y) title 'z = x'
	gp << "splot '-' with vectors title 'P(x,y,z)', '-' with vectors title 'n', \
			'+' using 1:(g($1,$1)):(h($1,$1)) title 'plane' with filledcurves lc rgb 'blue'\n";

	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	
	return 0;
}