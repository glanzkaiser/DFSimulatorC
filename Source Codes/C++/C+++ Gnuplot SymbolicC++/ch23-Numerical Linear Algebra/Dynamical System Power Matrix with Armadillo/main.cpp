// g++ -o main main.cpp -larmadillo
//
// make 
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(void)
{
	mat A(2,2,fill::zeros);
	mat x(2,1,fill::zeros);
	A = { { 0.97, 0.18 },
        { 0.03, 0.82 } };
	x.load("vectorX.txt");
	
	A.print("A:\n");
	x.print("x:\n");
	
	mat A2(2,2,fill::zeros);
	mat A5(2,2,fill::zeros);
	mat A10(2,2,fill::zeros);
	mat A108(2,2,fill::zeros);
	
	A2 = powmat(A,2);
	A5 = powmat(A,5);
	A10 = powmat(A,10);
	A108 = powmat(A,108);

	cout << "A^2 = \n" << A2 << endl; 
	cout << "A^5 = \n" << A5 << endl; 
	
	cout << "A*x = \n" << A*x << endl; 
	cout << "(A^2)*x = \n" << A2*x << endl; 
	cout << "(A^5)*x = \n" << A5*x << endl; 
	cout << "(A^10)*x = \n" << A10*x << endl; 
	cout << "(A^108)*x = \n" << A108*x << endl; 
	
 return 0;
}