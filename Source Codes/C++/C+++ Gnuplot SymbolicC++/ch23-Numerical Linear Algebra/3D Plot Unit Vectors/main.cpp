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
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_z;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;
	std::vector<double> pts_D_dz;
	std::vector<double> pts_E_x;
	std::vector<double> pts_E_y;
	std::vector<double> pts_E_z;
	std::vector<double> pts_E_dx;
	std::vector<double> pts_E_dy;
	std::vector<double> pts_E_dz;

	// we choose the value for (x0,y0,z0) = (0,0,0) the origin	
	float x0 = 0;
	float y0 = 0;
	float z0 = 0;
	// unit vector i
	float ix = 1;
	float iy = 0;
	float iz = 0;
	// unit vector j
	float jx = 0;
	float jy = 1;
	float jz = 0;
	// unit vector k
	float kx = 0;
	float ky = 0;
	float kz = 1;
	// vector v
	float vx = 0.5;
	float vy = 0.6;
	float vz = 1;
		
	// Create unit vector i
	pts_B_x .push_back(x0);
	pts_B_y .push_back(y0);
	pts_B_z .push_back(z0);
	pts_B_dx.push_back(ix);
	pts_B_dy.push_back(iy);
	pts_B_dz.push_back(iz);
	
	// Create unit vector j
	pts_C_x .push_back(x0);
	pts_C_y .push_back(y0);
	pts_C_z .push_back(z0);
	pts_C_dx.push_back(jx);
	pts_C_dy.push_back(jy);
	pts_C_dz.push_back(jz);
	
	// Create unit vector k
	pts_D_x .push_back(x0);
	pts_D_y .push_back(y0);
	pts_D_z .push_back(z0);
	pts_D_dx.push_back(kx);
	pts_D_dy.push_back(ky);
	pts_D_dz.push_back(kz);
	
	// Create vector v
	pts_E_x .push_back(x0);
	pts_E_y .push_back(y0);
	pts_E_z .push_back(z0);
	pts_E_dx.push_back(vx);
	pts_E_dy.push_back(vy);
	pts_E_dz.push_back(vz);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [0:1.5]\n set yrange [0:1.5]\n set zrange [0:1.5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 80,70,1\n"; // pitch,yaw,zoom
	gp << "splot '-' with vectors title 'i', '-' with vectors title 'j', '-' with vectors title 'k', '-' with vectors title 'v' \n";

	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	
	return 0;
}