// g++ main.cpp -o result -larmadillo

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
	fmat X, Xnew;
	fvec y;
	y.load("vectory.txt");
	X.load("MatrixX.txt");	
	Xnew.load("Xnew.txt");	
	fmat O = ones<fmat>(6,1);
	//mat O(6,1, fill::ones);	
	X.insert_cols(0,O);

	cout << "Matrix X:" << endl;
	X.print();
	cout << "Vector y:" << endl;
	y.print();
	cout << endl;

	fmat Xt = X.t();
	cout << "Matrix X^T:" << endl;
	Xt.print();
	
	fmat B = inv(Xt*X)*Xt*y;
	cout << "\nMatrix B:" << endl;
	B.print();
	
	fmat Test = Xnew*B;
	cout << "\nXnew:" << endl;
	Xnew.print();
	cout << "\nXnew * B:" << endl;
	Test.print();
	
	return 0;
}


