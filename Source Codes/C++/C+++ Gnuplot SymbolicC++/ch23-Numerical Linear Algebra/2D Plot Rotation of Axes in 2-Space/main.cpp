
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams -larmadillo

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>
#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

#define theta 45 // Define the degree of rotation
#define N 2 // Define the number of dimension
#define DEGTORAD 0.0174532925199432957f

using namespace std;
using namespace arma;

void PrintMatrix(float a[][N])
{
	int r = N;
	int c = N;
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		cout <<setw(6) << setprecision(0) << a[i][j] << "\t";
		cout << endl;
	}
}

int main() {
	Gnuplot gp;

	// Armadillo
	arma::mat X;
	arma::mat Y;
	arma::vec Q;
	X.load("vectorX.txt");
	Y.load("vectorY.txt");
	Q.load("vectorQ.txt");
	cout <<"The xy-system:" << endl;	
	cout <<"Vector x:" << "\n" << X <<endl;
	cout <<"Vector y:" << "\n" << Y <<endl;
	cout <<"Point Q: ( " << Q[0] << ", " << Q[1] << " )" << endl;
	
	// Old basis B = {(1,0), (0,1)} the standard xy-system
	// New basis B' = {(cos theta, sin theta), (-sin theta, cos theta)} rotate the standard xy-system counterclockwise through angle theta
	
	// Transition matrix from B' to B = standard matrix for counterclockwise rotation through angle theta
	float matrixA[N][N] = {};
	matrixA[0][0] = cos(theta*DEGTORAD);
	matrixA[0][1] = -sin(theta*DEGTORAD);
	matrixA[1][0] = sin(theta*DEGTORAD);
	matrixA[1][1] = cos(theta*DEGTORAD);
	
	arma::mat ArmaA(N,N,fill::zeros); // Declare matrix ArmaA of size N X N with Armadillo
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			ArmaA[i+j*N] = matrixA[i][j] ;
		}			
	}
	
	cout <<"P (Transition matrix from B' to B)" << theta << " :" << "\n" << ArmaA <<endl;

	arma::mat Xrotate = ArmaA*X ;
	arma::mat Yrotate = ArmaA*Y ;
	
	cout <<"The x'y'-system:" << endl;
	cout <<"The rotated vector x / x':" << "\n" << Xrotate <<endl;
	cout <<"The rotated vector y / y':" << "\n" << Yrotate <<endl;
	
	arma::mat ArmaA_Transpose(N,N,fill::zeros);
	ArmaA_Transpose  = ArmaA.t();
	cout <<"P^{-1} = P^{T} (Transition matrix from B to B') " << "\n" << ArmaA_Transpose <<endl;
	arma::mat PTQ;
	PTQ = ArmaA_Transpose*Q;
	cout << endl;
	cout <<"Q relative to the xy-system:" << endl;	
	cout <<"(x, y) = " << "( " << Q[0] << ", " << Q[1] << " )"<<endl;
	cout <<"Q relative to the x'y'-system:" << endl;
	cout <<"(x', y') = " << "( " << PTQ[0] << ", " << PTQ[1] << " )"<<endl;

	// We use a separate container for each column, like so:
	std::vector<double> pts_D_x;
	std::vector<double> pts_D_y;
	std::vector<double> pts_D_dx;
	std::vector<double> pts_D_dy;	
	std::vector<double> pts_E_x;
	std::vector<double> pts_E_y;
	std::vector<double> pts_E_dx;
	std::vector<double> pts_E_dy;	
	std::vector<double> pts_F_x;
	std::vector<double> pts_F_y;
	std::vector<double> pts_F_dx;
	std::vector<double> pts_F_dy;	
	std::vector<double> pts_G_x;
	std::vector<double> pts_G_y;
	std::vector<double> pts_G_dx;
	std::vector<double> pts_G_dy;	
	
	float o = 0;
	
	// Create a vector x
	pts_D_x .push_back(o);
	pts_D_y .push_back(o);
	pts_D_dx.push_back(X[0]);
	pts_D_dy.push_back(X[1]);
	// The counterclockwise rotation of vector x through angle theta
	pts_E_x .push_back(o);
	pts_E_y .push_back(o);
	pts_E_dx.push_back(Xrotate[0]);
	pts_E_dy.push_back(Xrotate[1]);
	// Create a vector y
	pts_F_x .push_back(o);
	pts_F_y .push_back(o);
	pts_F_dx.push_back(Y[0]);
	pts_F_dy.push_back(Y[1]);
	// The counterclockwise rotation of vector y through angle theta
	pts_G_x .push_back(o);
	pts_G_y .push_back(o);
	pts_G_dx.push_back(Yrotate[0]);
	pts_G_dy.push_back(Yrotate[1]);

	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal 'wxt' size 1200,800 enhanced font 'Verdana,10' persist\n"; // To make the plot interactive
	gp << "set xrange [-1.1:2.1]\nset yrange [-1.5:1.5]\n";
	gp << "set xlabel 'x-axis'\n set ylabel 'y-axis'\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "f(x) = x\n";
	gp << "plot 'vectorQ.dat' with points pt 7 ps 2 title 'Q', \
		'-' with vectors lw 1 lc rgb 'dark-green' title '{/:Bold {u}_{1}}','-' with vectors lw 3 lc rgb 'dark-green' title '{/:Bold u_{1}`}',\
		'-' with vectors lw 1 lc rgb 'dark-turquoise' title '{/:Bold {u}_{2}}','-' with vectors lw 3 lc rgb 'dark-turquoise' title '{/:Bold u_{2}`}'\n";
	gp.send1d(boost::make_tuple(pts_D_x, pts_D_y, pts_D_dx, pts_D_dy));
	gp.send1d(boost::make_tuple(pts_E_x, pts_E_y, pts_E_dx, pts_E_dy));
	gp.send1d(boost::make_tuple(pts_F_x, pts_F_y, pts_F_dx, pts_F_dy));
	gp.send1d(boost::make_tuple(pts_G_x, pts_G_y, pts_G_dx, pts_G_dy));
}