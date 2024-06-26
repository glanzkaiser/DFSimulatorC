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
	std::vector<double> pts_B_dx;
	std::vector<double> pts_B_dy;
	std::vector<double> pts_C_x;
	std::vector<double> pts_C_y;
	std::vector<double> pts_C_dx;
	std::vector<double> pts_C_dy;
	std::vector<std::pair<double,double>> data;
	data.emplace_back(0.5,1);
	data.emplace_back(0.5,0);
	
	float o = 0;
	float cx = 0.5;
	float cy = 1;
	float bx = 2;
	float by = 0;
	// Create a vector with origin at (0,0) and terminal point at (2,0)
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_dx.push_back(bx);
	pts_B_dy.push_back(by);
	// Create a vector with origin at (0,0) and terminal point at (0.5,1)
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_dx.push_back(cx);
	pts_C_dy.push_back(cy);
	
	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1:3]\nset yrange [-1:2]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot '-' with vectors title '||v||', '-' with vectors title '||u||', '-' with lines title '||v|| sin θ' dashtype 2  lc 3 \n";
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));
	gp.send1d(data);
}