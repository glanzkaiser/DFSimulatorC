// g++ -o main main.cpp -larmadillo
//
// make 
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(void)
{
	mat P(3,3,fill::zeros);
	mat x(3,1,fill::zeros);
	P = { { 0.97, 0.51, 0.6 },
	{ 0.02, 0.33, 0.3},
        { 0.01, 0.16, 0.1 } };
	x.load("vectorX.txt");
	
	P.print("P:\n");
	x.print("x(0):\n");
	
	for (int i = 1; i < 50; i++)
	{
		cout << "x(" << i <<") = \n" << powmat(P,i)*x << endl; 
	}
	
	return 0;
}