
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
	int N = 3;
	arma::vec u(N,fill::zeros); 
	u[0] = 1;
	u[1] = 1;
	u[2] = 1;
	arma::vec v1(N,fill::zeros); 
	v1[0] = 0;
	v1[1] = division(1,1);
	v1[2] = 0;
	arma::vec v2(N,fill::zeros); 
	v2[0] = division(-4,5);
	v2[1] = 0;
	v2[2] = division(3,5);
	arma::vec v3(N,fill::zeros); 
	v3[0] = division(3,5);
	v3[1] = 0;
	v3[2] = division(4,5);
	
	cout <<"Vector v1 :" << "\n" << v1 <<endl;
	cout <<"|| v1 || :"  << norm(v1) <<endl;
	cout <<"\nVector v2 :" << "\n" << v2 <<endl;
	cout <<"|| v2 || :"  << norm(v2) <<endl;
	cout <<"\nVector v3 :" << "\n" << v3 <<endl;
	cout <<"|| v3 || :"  << norm(v3) <<endl;
	cout <<"\nVector u :" << "\n" << u <<endl;
	cout <<"|| u || :"  << norm(u) <<endl;
	
	double uv1 = dot(u,v1);
	double uv2 = dot(u,v2);
	double uv3 = dot(u,v3);
	
	cout <<"\n<u,v1> :" << uv1 <<endl;
	cout <<"<u,v2> :" << uv2 <<endl;
	cout <<"<u,v3> :" << uv3 <<endl;
	
	arma::vec uS(N,fill::zeros); 
	uS[0] = uv1;
	uS[1] = uv2;
	uS[2] = uv3;

	cout <<"\nThe coordinate vector of u relative to S is:" <<endl;
	cout <<"(u)_{S} =\n" << uS <<endl;
	
	return 0;
}