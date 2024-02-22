// Change Standard Basis by Reflecting through Line
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams 

#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

#define DEGTORAD 0.0174532925199432957f

using namespace std;

float theta = 35; // Angle between the line and positive x-axis
int n = 2;

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
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;	
	std::vector<double> pts_E_x;
	std::vector<double> pts_E_y;
	std::vector<double> pts_E_dx;
	std::vector<double> pts_E_dy;	
	
	float o = 0;
	float e1x = 0;
	float e1y = 1;
	float e2x = 1;
	float e2y = 0;

	float v1x = cos(2*theta*DEGTORAD);
	float v1y = sin(2*theta*DEGTORAD);
	float v2x = sin(2*theta*DEGTORAD);
	float v2y = -cos(2*theta*DEGTORAD);
	
	float vect_e1[] = { e1x,e1y };
	float vect_e2[] = { e2x,e2y };
	float vect_v1[] = { v1x, v1y };
	float vect_v2[] = { v2x, v2y };
	
	cout << "Vector e1:" << setw(15) << "vector e2:"  << endl;
	
	for (int i = 0; i < n; i++) 
	{
		cout << vect_e1[i]  << "\t" << "\t" << vect_e2[i] ;
		cout << endl;
	}
	cout << endl;
	cout << "Vector v1:" << setw(15) << "vector v2:" << endl;
	
	for (int i = 0; i < n; i++) 
	{
		cout << setprecision(4) << vect_v1[i]  << "\t" << "\t" << vect_v2[i]  ;
		cout << endl;
	}
	cout<<endl;
	
	// Create a vector with origin at (0,0) and terminal point at (1,0)
	pts_B_x .push_back(o);
	pts_B_y .push_back(o);
	pts_B_dx.push_back(e1x);
	pts_B_dy.push_back(e1y);
	// Create a vector with origin at (0,0) and terminal point at (0,1)
	pts_C_x .push_back(o);
	pts_C_y .push_back(o);
	pts_C_dx.push_back(e2x);
	pts_C_dy.push_back(e2y);
	// Create a vector v1, reflection of e1 toward the line
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(v1x);
	pts_D_dy.push_back(v1y);
	// Create a vector v2, reflection of e2 toward the line
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(v2x);
	pts_E_dy.push_back(v2y);

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-1:3]\nset yrange [-1:2]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = (atan(35*0.0174532925)*x)\n";
	gp << "plot '-' with vectors title 'e_{1}', '-' with vectors title 'e_{2}', '-' with vectors title 'v_{1}','-' with vectors title 'v_{2}' lc 'green',f(x) title 'Line' lc 'black;\n";
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));
	gp.send1d(boost::make_tuple(pts_C_x, pts_C_y, pts_C_dx, pts_C_dy));
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
}