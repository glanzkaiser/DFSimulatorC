// g++ -o result main.cpp -lsymbolicc++
// Merci beaucoup Freya et Sentinel
// Kaing bla kaing.. Hasta la meo -Bludut

#include<bits/stdc++.h>
#include<iostream>
#include "symbolicc++.h"
#include<vector>
using namespace std;

#define R 2 // number of rows
#define C 2 // number of columns

// Driver program
int main()
{
	Symbolic w1("w1"); 
	Symbolic w2("w2");
	Matrix<Symbolic> W(R,1);
	W[0][0] = w1;	
	W[1][0] = w2;

 	// Construct a symbolic matrix of size R X C
	Matrix<Symbolic> T_mat(R,C);
	T_mat[0][0] = 2;		T_mat[0][1] = 1;	
	T_mat[1][0] = 3;		T_mat[1][1] = 4;	

	cout << "T:\n" << T_mat <<endl;
	cout << endl;
	Matrix<Symbolic> TI(R,C);
	TI = T_mat.inverse();
	
	cout << "T^{-1}:\n" << TI <<endl;	
	cout << endl;

	cout << "T^{-1} * w :\n" << TI*W <<endl;
	
	return 0;
}