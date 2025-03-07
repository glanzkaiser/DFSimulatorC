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
	std::vector<double> pts_B_dx;
	std::vector<double> pts_B_dy;

	float o = 0;
	float bx = 0.0015;
	float by = 4500;
	// Create a vector with origin at (0,0) and terminal point at (1,0)
	pts_B_x .push_back(bx);
	pts_B_y .push_back(o);
	pts_B_dx.push_back(o);
	pts_B_dy.push_back(by);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [0:0.003]\nset yrange [0:4550]\n";
	gp << "set xlabel 't'\n set ylabel 'F(t)'\n";
	
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = (6*(10**6))*x - (2*(10**9))*x**2\n";
	gp << "x = 0.0015\n";
	gp << "plot f(x) title '(6 x 10^{6}) t - (2 x 10^{9}) t^{2}', '-' title '' with vectors dashtype 3\n";
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));
	
	
	return 0;
}