// Demo of vector plot.
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams -lboost_system -lboost_filesystem

#include <fstream>
#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;
	std::vector<std::pair<double, double>> xy_pts;
    	for(double x=-2; x<2; x+=0.5) 
	{
        double y = 0.12 + 0.34*x + 0.56*x*x;
        xy_pts.emplace_back(x, y);
    	}

    	gp << "set xrange [-2:2]\n";
    	gp << "f(x) = a + b*x + c*x*x\n";
    	gp << "fit f(x) '-' via a,b,c\n";
    	gp.send1d(xy_pts);
    	gp << "plot '-' with points title 'input', f(x) with lines title 'fit'\n";
    	gp.send1d(xy_pts);


}