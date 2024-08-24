// g++ -o result main.cpp
// Merci beaucoup Freya.. et Sentinel

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

using namespace std;
using namespace arma;

// Driver code
int main(int argc, char** argv)
{
	vec v1;
	vec v2;
	vec v3;
	v1.load("vector1.txt");
	v2.load("vector2.txt");
	v3.load("vector3.txt");
	cout <<"Eigenvector 1:" << "\n" << v1 <<endl;
	cout <<"Eigenvector 2:" << "\n" << v2 <<endl;
	cout <<"Eigenvector 3:" << "\n" << v3 <<endl;
	
	float λ1 = -1;
	float λ2 = 3;
	float λ3 = 7;

	// Gram-Schmidt Process
	mat u1 = v1;

	mat u1v2 = (dot(u1,v2)/pow(norm(u1),2) )*u1;
	mat u2 = v2 - u1v2;

	mat u1v3 = (dot(u1,v3)/pow(norm(u1),2) )*u1;
	mat u2v3 = (dot(u2,v3)/pow(norm(u2),2) )*u2;	
	mat u3 = v3 - u1v3 - u2v3;

	// Normalize the orthogonal basis vectors
	u1 = u1/norm(u1);
	u2 = u2/norm(u2);
	u3 = u3/norm(u3);

	mat u1_transpose = u1.t();
	mat u2_transpose = u2.t();
	mat u3_transpose = u3.t();

	cout <<"After Gram-Schmidt Process:" << "\n"  <<endl;
	cout <<"Unit Eigenvector 1:" << "\n" << u1 <<endl;
	cout <<"Unit Eigenvector 2:" << "\n" << u2 <<endl;
	cout <<"Unit Eigenvector 3:" << "\n" << u3 <<endl;

	// Spectral decomposition computation
	mat A(3,3,fill::eye);
	A = λ1*u1*u1_transpose + λ2*u2*u2_transpose + λ3*u3*u3_transpose;
	
	cout <<"Matrix A:" << "\n" << A <<endl;
	// save matrix as a text file
	A.save("matrixA.txt", raw_ascii);
  
	cout <<"P orthogonally diagonalizes A" << "\n"  <<endl;
	cout <<"P is an orthogonal matrix, because P^{T} = P^{-1}" << "\n"  <<endl;
	mat P(3,3,fill::eye);
	P.col(0) = u1;
	P.col(1) = u2;
	P.col(2) = u3;
	cout <<"Matrix P:" << "\n" << P <<endl;
	cout <<"Matrix P^{T}:" << "\n" << P.t() <<endl;
	cout <<"Matrix P^{-1}:" << "\n" << inv(P) <<endl;
	
	Gnuplot gp;

	// We use a separate container for each column, like so:
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
	std::vector<double> pts_H_x;
	std::vector<double> pts_H_y;
	std::vector<double> pts_H_z;
	std::vector<double> pts_H_dx;
	std::vector<double> pts_H_dy;	
	std::vector<double> pts_H_dz;
	std::vector<double> pts_I_x;
	std::vector<double> pts_I_y;
	std::vector<double> pts_I_z;
	std::vector<double> pts_I_dx;
	std::vector<double> pts_I_dy;	
	std::vector<double> pts_I_dz;

	float o = 0;
	
	// Create the eigenvector v1
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_z .push_back(o);
	pts_D_dx.push_back(v1[0]);
	pts_D_dy.push_back(v1[1]);
	pts_D_dz.push_back(v1[2]);
	// Create the eigenvector v2
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_z .push_back(o);
	pts_E_dx.push_back(v2[0]);
	pts_E_dy.push_back(v2[1]);
	pts_E_dz.push_back(v2[2]);
	// Create the eigenvector v3
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_z .push_back(o);
	pts_F_dx.push_back(v3[0]);
	pts_F_dy.push_back(v3[1]);
	pts_F_dz.push_back(v3[2]);

	// Create the orthonormal eigenvector u1
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_z .push_back(o);
	pts_G_dx.push_back(u1[0]);
	pts_G_dy.push_back(u1[1]);
	pts_G_dz.push_back(u1[2]);
	// Create the orthonormal eigenvector u2
	pts_H_x .push_back(o);
	pts_H_y .push_back(o);
	pts_H_z .push_back(o);
	pts_H_dx.push_back(u2[0]);
	pts_H_dy.push_back(u2[1]);
	pts_H_dz.push_back(u2[2]);
	// Create the orthonormal eigenvector u3
	pts_I_x .push_back(o);
	pts_I_y .push_back(o);
	pts_I_z .push_back(o);
	pts_I_dx.push_back(u3[0]);
	pts_I_dy.push_back(u3[1]);
	pts_I_dz.push_back(u3[2]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-1:1]\nset yrange [-1:1]\nset zrange [-1:1]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n set zlabel 'z-axis'\n";
	gp << "set view 80,90,1\n"; // pitch,yaw,zoom for y axis on front	
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "splot '++' using 1:2:(0) with lines lw 2 lc rgb 'gray80' title 'xy-plane',\
		'-' with vectors lw 1 lc rgb 'dark-green' dashtype 4 title '{/:Bold {v}_{1}}',\
		'-' with vectors lw 1 lc rgb 'dark-turquoise' dashtype 4 title '{/:Bold {v}_{2}}',\
		'-' with vectors lw 1 lc rgb 'dark-red' dashtype 4 title '{/:Bold {v}_{3}}',\
		'-' with vectors lw 2 lc rgb 'dark-green' title '{/:Bold {u}_{1}}',\
		'-' with vectors lw 2 lc rgb 'dark-turquoise' title '{/:Bold {u}_{2}}',\
		'-' with vectors lw 2 lc rgb 'dark-red' title '{/:Bold {u}_{3}}'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_z, pts_D_dx, pts_D_dy, pts_D_dz));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_z, pts_E_dx, pts_E_dy, pts_E_dz));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_z, pts_F_dx, pts_F_dy, pts_F_dz));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_z, pts_G_dx, pts_G_dy, pts_G_dz));
	gp.send1d(boost::make_tuple(pts_H_x, pts_H_y, pts_H_z, pts_H_dx, pts_H_dy, pts_H_dz));
	gp.send1d(boost::make_tuple(pts_I_x, pts_I_y, pts_I_z, pts_I_dx, pts_I_dy, pts_I_dz));

	return 0;
}