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
	std::vector<double> pts_C_x;
	std::vector<double> pts_C_y;
	std::vector<double> pts_C_dx;
	std::vector<double> pts_C_dy;
	
	// Point-normal equation of the line:
	// a(x-x0) + b(y-y0) = 0
	// we choose the value for (x0,y0) = (0,0) the origin	
	float xo = 0;
	float yo = 0;
	// normal n = (a,b) = (2,3)
	float a = 2;
	float b = 1.3;
	// to determine the vector that is passing through the origin (0,0) and (x,y) we choose x then we obtain value for y, y = mx+c
	float bx = -1;
	float by = yo + ( -(a/b)*(bx-xo) ) ;
		
	// Create a vector with origin at (0,0) and terminal point at (x,y) = (bx,by)
	pts_B_x .push_back(xo);
	pts_B_y .push_back(yo);
	pts_B_dx.push_back(bx);
	pts_B_dy.push_back(by);
	// Create a vector with origin at (0,0) and terminal point at (a,b) as the normal
	pts_C_x .push_back(xo);
	pts_C_y .push_back(yo);
	pts_C_dx.push_back(a);
	pts_C_dy.push_back(b);
	
	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-2:3]\nset yrange [-1:2]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = (-(2/1.3)*x)\n";
	gp << "plot '-' with vectors title 'P(x,y)', '-' with vectors title 'n', f(x) title 'Line'\n";

	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));

	return 0;
}