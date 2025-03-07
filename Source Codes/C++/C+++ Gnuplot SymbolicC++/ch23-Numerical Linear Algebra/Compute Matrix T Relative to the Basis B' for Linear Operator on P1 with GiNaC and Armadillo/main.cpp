// g++ -o result main.cpp -larmadillo -lginac -lcln 
// Merci beaucoup Freya.. et Sentinel..

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <ginac/ginac.h>
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;
using namespace GiNaC;

// Linear operator T: P_1 -> P_1
// Driver code
int main(int argc, char** argv)
{
	// GiNac & Armadillo codes starts here
	cout << " ******************************************************************** " << endl;
	cout << " *********************GiNaC & Armadillo Codes*********************** " << endl;
	cout << " ******************************************************************** " << endl;
	
	Digits = 5; // define maximum decimal digits
	symbol x("x"), xpow2("x^2"), a("a"), b("b"), x1("x1"), x2("x2");
	
	ex Tx = x + 1;
	// p1 = 6+3x ; p2 = 10+2x
	ex p1 = 6 + 3*x;
	ex p2 = 10 + 2*x;
	
	cout << "\n T(p1) = " << p1.subs(x==Tx) << endl;
	cout << "\n T(p2) = " << p2.subs(x==Tx) << endl;
	
	ex Tp1 = p1.subs(x==Tx); 
	ex Tp2 = p2.subs(x==Tx); 

	//ex p1_gcd = gcd(Tp1, p1);
	//ex p2_gcd = gcd(Tp1, p2);
	cout << "\n Coefficient of x^0 for T(p1) = " << Tp1.coeff(x,0) << endl;
	cout << "\n Coefficient of x^1 for T(p1) = " << Tp1.coeff(x,1) << endl;
	cout << "\n Coefficient of x^0 for T(p2) = " << Tp2.coeff(x,0) << endl;
	cout << "\n Coefficient of x^1 for T(p2) = " << Tp2.coeff(x,1) << endl;
	
	// To convert GiNaC:: ex to Double
	double tp11 = ex_to<numeric>(Tp1.coeff(x,0)).to_double();
	double tp12 = ex_to<numeric>(Tp1.coeff(x,1)).to_double();
	double tp21 = ex_to<numeric>(Tp2.coeff(x,0)).to_double();
	double tp22 = ex_to<numeric>(Tp2.coeff(x,1)).to_double();
	
	vec bp1 = { tp11, tp12 }; 
	vec bp2 = { tp21, tp22 }; 
	vec v1 = { 6, 3 }; // from p1 = 6 + 3x
	vec v2 =	{ 10, 2 }; // from p2 = 10 + 2x
	mat A(2,2,fill::zeros);
	A.col(0) = v1;
	A.col(1) = v2;

	mat X1;
	mat X2;
	
	X1 = solve(A,bp1,solve_opts::force_approx); 
	X2 = solve(A,bp2,solve_opts::force_approx); 

	mat T_B(2,2,fill::zeros);
	T_B.col(0) = X1;
	T_B.col(1) = X2;
	
	cout << "\n [T]_{B} = \n" << T_B << endl;
	
	// q1 = 2 ; q2 = 3 + 2x
	ex q1 = 2;
	ex q2 = 3 + 2*x;

	// To convert GiNaC:: ex to Double
	double q11 = ex_to<numeric>(q1.coeff(x,0)).to_double();
	double q12 = ex_to<numeric>(q1.coeff(x,1)).to_double();
	double q21 = ex_to<numeric>(q2.coeff(x,0)).to_double();
	double q22 = ex_to<numeric>(q2.coeff(x,1)).to_double();
	
	vec bq1 = { q11, q12 }; 
	vec bq2 = { q21, q22 }; 
	
	mat X_Bnew1;
	mat X_Bnew2;
	
	X_Bnew1 = solve(A,bq1,solve_opts::force_approx); 
	X_Bnew2 = solve(A,bq2,solve_opts::force_approx); 

	mat P(2,2,fill::zeros);
	P.col(0) = X_Bnew1;
	P.col(1) = X_Bnew2;

	cout << "\n Transition matrix from B' to B is P" << endl;
	cout << "\n P = \n" << P << endl;
	cout << "\n P^{-1} = \n" << arma::inv(P) << endl;
	
	mat T_Bnew;
	T_Bnew = arma::inv(P)*T_B*P;

	T_Bnew(0) = lround(T_Bnew(0));
	T_Bnew(1) = lround(T_Bnew(1));
	T_Bnew(2) = lround(T_Bnew(2));
	T_Bnew(3) = lround(T_Bnew(3));
	
	cout << "\n [T]_{B'} = P^{-1} * [T]_{B} * P = \n" << T_Bnew<< endl;
		
	return 0;
}