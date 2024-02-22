// Demo of vector plot and computation.
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include <iostream> 
#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>
#include <bits/stdc++.h>

#include "gnuplot-iostream.h"

#define RADTODEG 57.295779513082320876f
#define DEGTORAD 0.0174532925199432957f

using namespace std;

int n = 3;
float phi = 30; // Angle of elevation between positive z-axis and xy-plane
float theta = 35; // Angle between the line and positive x-axis

int main() {
	Gnuplot gp;

	float u1 = 1;
	float u2 = 0;
	float u3 = 0;

	float v1 = 0;
	float v2 = 1;
	float v3 = 0;

	float w1 = 0;
	float w2 = 0;
	float w3 = 1;
	// Define the line that  makes an angle theta with the positive x-axis and angle of elevation of phi with the xy-plane
	float l1 = cos(DEGTORAD*theta);
	float l2 = sin(DEGTORAD*theta);
	float l3 = sin(DEGTORAD*phi);

	// The new basis that reflected about the line that makes an angle theta with the positive x-axis
	// and angle of elevation of phi with the xy-plane
	float r1 = cos(2*DEGTORAD*theta) * cos(2*DEGTORAD*phi);
	float r2 = sin(2*DEGTORAD*theta) * cos(2*DEGTORAD*phi);
	float r3 = sin(2*DEGTORAD*phi);

	float s1 = sin(2*DEGTORAD*theta) * cos(2*DEGTORAD*phi);
	float s2 = -cos(2*DEGTORAD*theta) * cos(2*DEGTORAD*phi);
	float s3 = sin(2*DEGTORAD*phi);

	float t1 = sin(2*DEGTORAD*phi) * cos(DEGTORAD*theta);
	float t2 = sin(2*DEGTORAD*phi) * sin(DEGTORAD*theta);
	float t3 = -cos(2*DEGTORAD*phi);

	float vect_u[] = { u1, u2, u3 };
	float vect_v[] = { v1, v2, v3 };
	float vect_w[] = { w1, w2, w3 };
	float vect_s[] = { r1, r2, r3 };
	float vect_t[] = { s1, s2, s3  };
	float vect_r[] = { t1, t2, t3 };
	
	cout << "Vector e1:" << setw(15) << "vector e2:" << setw(15) << "vector e3:" << endl;
	
	for (int i = 0; i < n; i++) 
	{
		cout << vect_u[i]  << "\t" << "\t" << vect_v[i] << "\t" << "\t" << vect_w[i] ;
		cout << endl;
	}
	cout << endl;
	cout << "Vector v1:" << setw(15) << "vector v2:" << setw(15) << "vector v3:" << endl;
	
	for (int i = 0; i < n; i++) 
	{
		cout << setprecision(4) << vect_s[i]  << "\t" << "\t" << vect_t[i] << "\t" << "\t" << vect_r[i] ;
		cout << endl;
	}
	cout<<endl;

	cout << "θ between the line and positive x-axis (degrees) = " << theta <<endl;
	cout << "Angle of elevation between the line and the xy-plane (degrees) = " << phi <<endl;
	
	// We use a separate container for each column, like so:
	std::vector<double> pts_A_x;
	std::vector<double> pts_A_y;
	std::vector<double> pts_A_z;
	std::vector<double> pts_A_dx;
	std::vector<double> pts_A_dy;
	std::vector<double> pts_A_dz;
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
	std::vector<double> pts_F_x;
	std::vector<double> pts_F_y;
	std::vector<double> pts_F_z;
	std::vector<double> pts_F_dx;
	std::vector<double> pts_F_dy;	
	std::vector<double> pts_F_dz;	
	std::vector<double> pts_G_x;
	std::vector<double> pts_G_y;
	std::vector<double> pts_G_z;
	std::vector<double> pts_G_dx;
	std::vector<double> pts_G_dy;	
	std::vector<double> pts_G_dz;	
	
	float o = 0;

	// Create a vector e1 with origin at (0,0,0) and terminal point at (1,0,0)
	pts_A_x .push_back(o);
	pts_A_y .push_back(o);
	pts_A_z .push_back(o);
	pts_A_dx.push_back(u1);
	pts_A_dy.push_back(u2);
	pts_A_dz.push_back(u3);	
	// Create a vector e2 with origin at (0,0,0) and terminal point at (0,1,0)
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_z .push_back(o);
	pts_B_dx.push_back(v1);
	pts_B_dy.push_back(v2);
	pts_B_dz.push_back(v3);
	// Create a vector e3 with origin at (0,0) and terminal point at (0,0,1)
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_z .push_back(o);
	pts_C_dx.push_back(w1);
	pts_C_dy.push_back(w2);
	pts_C_dz.push_back(w3);
	// the red line = a line that makes angle θ toward positive x-axis and elevation angle of phi
	// Create a vector v1, the vector resulting from reflecting e1=(1,0,0) toward the red line
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(r1);
	pts_D_dy.push_back(r2);
	pts_D_dz.push_back(r3);
	// Create a vector v2, the vector resulting from reflecting e2=(0,1,0) toward the red line 
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(s1);
	pts_E_dy.push_back(s2);
	pts_E_dz.push_back(s3);
	// Create a vector v3, the vector resulting from reflecting e3=(0,0,1) toward the red line
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(t1);
	pts_F_dy.push_back(t2);
	pts_F_dz.push_back(t3);
	// Create the line
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_z .push_back(o);
	pts_G_dx.push_back(l1);
	pts_G_dy.push_back(l2);
	pts_G_dz.push_back(l3);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1:2]\nset yrange [-1:2]\nset zrange [-1:2]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "set view 70,10,1.2\n"; // pitch,yaw,zoom
	gp << "splot '-' with vectors title 'e_{1}', '-' with vectors title 'e_{2}', '-' with vectors title 'e_{3}', '-' with vectors title 'v_{1}', '-' with vectors title 'v_{2}','-' with vectors title 'v_{3}','-' with vectors title 'line' \n";
	gp.send1d(boost::make_tuple(pts_A_x, pts_A_y,  pts_A_z, pts_A_dx, pts_A_dy, pts_A_dz));
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y,  pts_B_z, pts_B_dx, pts_B_dy, pts_B_dz));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_z, pts_C_dx, pts_C_dy, pts_C_dz));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_z, pts_G_dx, pts_G_dy, pts_G_dz));
}