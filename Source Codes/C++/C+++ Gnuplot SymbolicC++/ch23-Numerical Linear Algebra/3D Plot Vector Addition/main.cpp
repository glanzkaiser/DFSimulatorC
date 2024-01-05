// Demo of vector plot.
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include <vector>
#include <cmath>
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
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_z;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;	
	std::vector<double> pts_D_dz;	
	
	float o = 0;
	float cx = 1;
	float cy = 1;
	float cz = 5;
	float bx = 1;
	float by = 0;
	float bz = 0;
	// Create a vector with origin at (0,0,0) and terminal point at (1,0,0)
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_z .push_back(o);
	pts_B_dx.push_back(bx);
	pts_B_dy.push_back(by);
	pts_B_dz.push_back(bz);
	// Create a vector with origin at (0,0) and terminal point at (1,1,5)
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_z .push_back(o);
	pts_C_dx.push_back(cx);
	pts_C_dy.push_back(cy);
	pts_C_dz.push_back(cz);
	// Create a vector from addition of B and C
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(cx+bx);
	pts_D_dy.push_back(cy+by);
	pts_D_dz.push_back(cz+bz);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1:3]\nset yrange [-1:3]\nset zrange [-1:5]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '-' with vectors title 'v', '-' with vectors title 'w', '-' with vectors title 'v+w'\n";
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
}