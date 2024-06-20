// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

// Merci beaucoup Freya et Sentinel

using namespace std;
using namespace GiNaC;

int main()
{
	Digits = 5; // define maximum decimal digits
	symbol x("x") ;
	symbol y1("y1"), y2("y2"), y3("y3") ;
	symbol c1("c1"), c2("c2"), c3("c3") ;
	
	matrix A = { { 3, 0, 0 }, { 0, -2, 0}, { 0, 0, 5 } };
	matrix y = { { y1}, { y2}, { y3} };
	cout << "\n A = " << A << endl;
	cout << "\n y = " << y << endl;
	
	matrix result = A.mul(y);
	
	cout << endl;
	
	cout << "y' = Ay = " << result <<endl;
	cout << endl;
	cout << "y1' = " << result[0] <<endl;
	cout << "y2' = " << result[1] <<endl;
	cout << "y3' = " << result[2] <<endl;
	
	ex a1 = result[0] / y1 ;
	ex a2 = result[1] / y2 ;
	ex a3 = result[2] / y3 ;
	ex fx1 = c1*exp(a1*x) ;
	ex fx2 = c2*exp(a2*x) ;
	ex fx3 = c3*exp(a3*x) ;
	cout << endl;

	cout << "y1 = " << fx1 <<endl;
	cout << "y2 = " << fx2 <<endl;
	cout << "y3 = " << fx3 <<endl;
	cout << endl;

	cout << "Solving the differential equations with initial conditions " << endl;
	cout << "y1(0) = 1, y2(0) = 4, y3(0) = -2 " << endl;
	cout << endl;
		
	// Define the initial conditions y1(0) = ic1, y2(0) = ic2, y3(0) = ic3
	ex ic1 = 1 ;
	ex ic2 = 4 ;
	ex ic3 = -2;

	ex c1_ans =  lsolve(fx1.subs(x==0) == ic1, c1) ;
	ex c2_ans =  lsolve(fx2.subs(x==0) == ic2, c2) ;
	ex c3_ans =  lsolve(fx3.subs(x==0) == ic3, c3) ;

	cout << "c1 = " << c1_ans<<endl;
	cout << "c2 = " << c2_ans <<endl;
	cout << "c3 = " << c3_ans <<endl;
	cout << endl;
	
	ex fx1_sol = c1_ans*exp(a1*x) ;
	ex fx2_sol = c2_ans*exp(a2*x) ;
	ex fx3_sol = c3_ans*exp(a3*x) ;

	cout << "The general solution satisfying the initial conditions are" << endl;
	cout << endl;
	
	cout << "y1 = " << fx1_sol <<endl;
	cout << "y2 = " << fx2_sol <<endl;
	cout << "y3 = " << fx3_sol <<endl;
	cout << endl;
	
	matrix y_sol = { { fx1_sol}, { fx2_sol}, { fx3_sol} };
	cout << "The general solution in matrix notation:" << endl;
	cout << "\n y = " << y_sol << endl;
	
	return 0;
}