// g++ -o main main.cpp -larmadillo
//
// make 
#include <iostream>
#include <armadillo>
#include "symbolicc++.h"

using namespace std;
using namespace arma;

int main(void)
{
	Symbolic q1("q1");
	Symbolic q2("q2");
	Symbolic s("s");
	Symbolic x("x");
	Symbolic a("a");
	Symbolic P = ( (Symbolic(0.8), Symbolic(0.1)),
 	  			  (Symbolic(0.2), Symbolic(0.9)) );
	Symbolic I = ( (Symbolic(1), Symbolic(0)),
 	  			  (Symbolic(0), Symbolic(1)) );
	Symbolic q = ( q1, q2 );
	
	Symbolic C = I-P;
	Symbolic MC = C*q .transpose();
	
	cout << "P:\n" << P << endl;
	cout << "I:\n" << I << endl;
	cout << "I-P:\n" << C << endl;
	cout << "(I-P)q:\n" << MC << endl;
	
	Symbolic MC2 = MC[q1==1-q2];

	cout << "(I-P)q [q1 = 1-q2] :\n" << MC2 << endl;
	cout << "row 1: \n" << MC2(0) << endl;
	cout << "row 2: \n" << MC2(1) << endl;
	
	cout << "find q2 :\n" << solve(MC2(0)=0,q2)<< endl;
	
	
	// Armadillo
	//mat P(2,2,fill::zeros);
	//mat B(2,2,fill::zeros);
	//mat I(2,2,fill::eye);

	//mat x(2,1,fill::zeros);
	//P = { { 0.8, 0.1 },
        //{ 0.2, 0.9 } };
	
	//P.print("P:\n");
	//I.print("I:\n");

	//B = 	I-P;
	//x.load("vectorX.txt");
	//mat X;
	//X = solve(B,x,solve_opts::force_approx); 

	//cout <<"Matrix I-P (Coefficient Matrix):" << "\n" << B <<endl;
	//cout <<"Solution / steady-state vector q :" << "\n" << X <<endl;	
	//mat PInv(2,2,fill::zeros);
	//PInv = inv(P);
	//cout << "P^{-1} = \n" << PInv << endl; 
	
 return 0;
}