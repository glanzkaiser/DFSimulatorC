// Demo of vector plot.
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include <vector>
#include <cmath>
#include <utility>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

using std::cout;
using std::endl;
using namespace std;

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
	// we choose the value for (x0,y0,z0) = (0,0,1) the origin	
	float x0 = 0;
	float y0 = 0;
	float z0 = 1;
	// normal n 
	float nx = 0;
	float ny = 0;
	float nz = 5;
	// to determine the vector that is passing through the origin (0,0,1) and the point (x,y,z)
	float bx = 1;
	float by = 1;
	float bz = 5;
		
	// Create a vector with origin at (0,0,1) and terminal point at (1,1,6)
	pts_B_x .push_back(x0);
	pts_B_y .push_back(y0);
	pts_B_z .push_back(z0);
	pts_B_dx.push_back(bx);
	pts_B_dy.push_back(by);
	pts_B_dz.push_back(bz);
	
	// Create a vector with origin at (0,0,1) and terminal point at (0,0,6) as the normal
	pts_C_x .push_back(x0);
	pts_C_y .push_back(y0);
	pts_C_z .push_back(z0);
	pts_C_dx.push_back(nx);
	pts_C_dy.push_back(ny);
	pts_C_dz.push_back(nz);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-2:2]\n set yrange [-2:2]\n set zrange [-3:6]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 100,5,1\n"; // pitch,yaw,zoom
	gp << "f(x,y) = 1\n";
	gp << "array point[1]\n"; // using a dummy array of length one
	
	// pt = point type, ps = point size, 
	gp << "splot '-' with vectors title 'P(x,y,z)', point us (1):(1):(6) title '(x,y,z,)' ps 2 lc 2 pt  6, \
		'-' with vectors title 'n', f(x,y) with lines title 'f(x,y)'\n";

	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	
	// to compute the distance, the plane equation is ax + by + cz + d = 0
	float a = 0;
	float b = 0;
	float c = 1;
	float d = -1;
	float D;
	D = abs(a*(bx+x0) + b*(by+y0) + c*(bz+z0) + d ) / (a*a + b*b + c*c);
	cout << endl;
	cout << "The distance between point ( " << bx+x0 << ", " << by+y0 << ", " << bz + z0 << ")" << endl;
	cout << "and the plane is : " << D << endl;

	return 0;
}