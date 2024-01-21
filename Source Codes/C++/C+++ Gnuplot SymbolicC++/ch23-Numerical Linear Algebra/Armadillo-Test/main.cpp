// g++ main.cpp -o result -larmadillo

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
	fmat A;
	
	//A.load("MatrixA.txt");	
	  A = { { 0.165300, 0.454037, 0.995795, 0.124098, 0.047084 },
        { 0.688782, 0.036549, 0.552848, 0.937664, 0.866401 },
        { 0.348740, 0.479388, 0.506228, 0.145673, 0.491547 },
        { 0.148678, 0.682258, 0.571154, 0.874724, 0.444632 },
        { 0.245726, 0.595218, 0.409327, 0.367827, 0.385736 } };

	cout << "Matrix A:" << endl;
	A.print();
	cout << endl;

	// determinant
	cout << "det(A): " << det(A) << endl;
	cout << "Row vector from A: " << endl;
	
	for(int i=0; i < 5; ++i)
	{
		cout << "row " << i << " :" << A.row(i) << endl;
	}
	
	cout << "Column vector from A: " << endl;
	
	for(int i=0; i < 5; ++i)
	{
		cout << "column " << i << " :" <<endl;
		cout << A.col(i) << endl;
	}
	
	rowvec xr(10, fill::ones);
	colvec xc(10, fill::ones);
	cout << "Row vector: " << endl; 
	cout << xr << endl;
	cout << "Column vector: " << endl;
	cout << xc << endl;
	
	cout << endl;
	
	cube B(3,3,3,fill::randn);
	B.print();
	
	return 0;
}


