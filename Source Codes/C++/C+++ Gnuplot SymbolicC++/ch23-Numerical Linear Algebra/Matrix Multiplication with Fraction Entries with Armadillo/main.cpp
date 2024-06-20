
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams -larmadillo

#include <vector>
#include <cmath>
#include <utility>
#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <armadillo>

using namespace std;
using namespace arma;

double division(double x, double y)
{
	return x/y;
}

int main() {
	int N = 2;
	arma::mat P(N,N,fill::zeros); 
	P[0] = division(1,1);
	P[1] = division(1,1);
	P[2] = division(1,6);
	P[3] = division(1,1);

	arma::mat A(N,N,fill::zeros); 
	A[0] = 0;
	A[1] = -6;
	A[2] = 1;
	A[3] = 7;
	
	cout <<"Matrix A :" << "\n" << A <<endl;
	cout <<"Matrix P :" << "\n" << P <<endl;
	cout <<"Matrix P^{-1} :" << "\n" << inv(P) <<endl;
	cout <<"Matrix P^{-1} A P :" << "\n" << inv(P)*A*P <<endl;
	
	return 0;
}