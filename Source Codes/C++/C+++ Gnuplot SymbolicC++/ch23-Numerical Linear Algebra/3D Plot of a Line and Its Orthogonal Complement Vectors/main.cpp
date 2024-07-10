
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

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

	// Point-normal equation of the plane:
	// a(x-x0) + b(y-y0) + c(z-z0) = 0
	// we choose the value for (x0,y0,z0) = (0,0,0) the origin	
	float x0 = 0;
	float y0 = 0;
	float z0 = 0;
	// The line W with parametric equation x=2t, y = -5t, z=4t
	float wx = 2;
	float wy = -5;
	float wz = 4;
	// to determine the first basis vector for W^{⊥} that is passing through the origin (0,0,0) and (2.5,1,0)
	float bx = 2.5;
	float by = 1;
	float bz = 0;
	// to determine the second basis vector for W^{⊥} that is passing through the origin (0,0,0) and (-2,0,1)
	float vx = -2;
	float vy = 0;
	float vz = 1;
		
	// Create a vector with origin at (0,0,0) and terminal point at (x,y,z) = (bx,by,bz)
	pts_B_x .push_back(x0);
	pts_B_y .push_back(y0);
	pts_B_z .push_back(z0);
	pts_B_dx.push_back(bx);
	pts_B_dy.push_back(by);
	pts_B_dz.push_back(bz);
	
	// Create a vector with origin at (0,0,0) and terminal point at (x,y,z) = (vx,vy,vz)
	pts_C_x .push_back(x0);
	pts_C_y .push_back(y0);
	pts_C_z .push_back(z0);
	pts_C_dx.push_back(vx);
	pts_C_dy.push_back(vy);
	pts_C_dz.push_back(vz);

	// Create the line W
	pts_D_x .push_back(x0);
	pts_D_y .push_back(y0);
	pts_D_z .push_back(z0);
	pts_D_dx.push_back(wx);
	pts_D_dy.push_back(wy);
	pts_D_dz.push_back(wz);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt'\n"; // To make the plot interactive
	gp << "set xrange[-2:2]\n set yrange[-2:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 100,5,1\n"; // pitch,yaw,zoom
	gp << "rgb(r,g,b) = int(r)*65536 + int(g)*256 + int(b)\n"; 
	gp << "fwt(x,y) = (-2*x + 5*y)/4\n";
	gp << "splot '-' with vectors filled head lw 3 lc rgb 'dark-green' title 'v_{1} = (2.5,1,0)', \
			'-' with vectors filled head lw 3 lc rgb 'forest-green' title 'v_{2} = (-2,0,1)', \
			'-' with vectors filled head lw 3 lc rgb 'blue' title 'W', \
			fwt(x,y) title 'W^{⊥} Plane (2x - 5y + 4z = 0)'\n";

	// Option 2 : plot from vector.dat and orthogonalvector.dat
	//gp << "splot fwt(x,y) title 'W^{⊥} plane (2x-5y+4z=0)',\
			'vector.dat' using 1:2:3:4:5:6 with vectors filled head lw 3 lc rgb 'forest-green' title 'Vector spanning W', \
			'orthogonalvector.dat' using 1:2:3:4:5:6 with vectors filled head lw 3 lc rgb 'blue' title 'Orthogonal vectors spanning W^{⊥}' \n";

	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	
	return 0;
}