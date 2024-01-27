// g++ main.cpp -o result -larmadillo

#include <iostream>
#include <armadillo>
#define N 3

using namespace std;
using namespace arma;
int main()
{
	mat A(4, 5, fill::randu);
	mat B(4, 5, fill::randu);

	cout << A*B.t() << endl;
  
	A = { { 0.165300, 0.454037, 0.995795, 0.124098, 0.047084 },
        { 0.688782, 0.036549, 0.552848, 0.937664, 0.866401 },
        { 0.348740, 0.479388, 0.506228, 0.145673, 0.491547 },
        { 0.148678, 0.682258, 0.571154, 0.874724, 0.444632 },
        { 0.245726, 0.595218, 0.409327, 0.367827, 0.385736 } };
        
	mat M(3,3,fill::zeros);
	M = {{0.5,-0.1,-0.1},{-0.2,0.5,-0.3},{-0.1,-0.3,0.6}};

	A.print("A:");	
	M.print("M:");
  	cout << endl;
	
	// determinant
	//cout << "det(A): " << det(A) << endl;
	cout << "det(M): " << det(M) << endl;
	cout << endl;
	//cout << "inv(A): " << endl << inv(A) << endl;
	cout << "inv(M): " << endl << inv(M) << endl;
  
	return 0;
}
