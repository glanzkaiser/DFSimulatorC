// g++ -o result main.cpp
// Merci beaucoup Freya..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <armadillo>

using namespace std;
using namespace arma;

// Driver code
int main(int argc, char** argv)
{
	
	vec vreal, vcomplex, ureal, ucomplex;
	vreal.load("vectorvreal.txt");
	vcomplex.load("vectorvcomplex.txt");
	ureal.load("vectorureal.txt");
	ucomplex.load("vectorucomplex.txt");
	cx_vec v(vreal,vcomplex);
	cx_vec u(ureal,ucomplex);

	cout <<"Vector v:" << "\n" << v <<endl;
	cout << endl;
	cout <<"Vector u:" << "\n" << u <<endl;
	cout << endl;
	
	cout <<"u . v :" << "\n" << dot(u,conj(v)) <<endl;
	cout << endl;
	cout <<"v . u :" << "\n" << dot(v,conj(u)) <<endl;
	cout << endl;
	
	cout <<"|| v || :" << "\n" << norm(v) <<endl;
	cout << endl;
	cout <<"|| u || :" << "\n" << norm(u) <<endl;
	
	cout <<"| 1+i | :" << "\n" << u[0] <<endl;
	cout <<"| 1+i | :" << "\n" << abs(u[0]) <<endl;
	cout <<"| 1 | :" << "\n" << abs(1) <<endl;
	cout <<"| -1 | :" << "\n" << abs(-1) <<endl;
	
	cout <<"| i | :" << "\n" << abs(u[1]) <<endl;
	cout <<"| i |^{2} :" << "\n" << abs(u[1])*abs(u[1]) <<endl;
	cout <<"| - i | :" << "\n" << abs(-u[1]) <<endl;
	
	cout <<"| 3 - i | :" << "\n" << abs(u[2]) <<endl;
	
	return 0;
}