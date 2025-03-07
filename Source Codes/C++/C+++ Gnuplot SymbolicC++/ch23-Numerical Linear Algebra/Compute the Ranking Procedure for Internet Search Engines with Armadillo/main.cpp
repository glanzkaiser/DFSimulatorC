// g++ -o result main.cpp -larmadillo
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
	mat A;
	A.load("matrixA.txt");
	cx_mat eigvec;
	cx_vec eigval;

	mat I(10,10,fill::eye);
	cout <<"Matrix A:" << "\n" << A <<endl;
		
	vec colsumA, rowsumA, a0, h0;
	colsumA = sum(A.t(),1);
	rowsumA = sum(A,1);
		
	a0 = colsumA/norm(colsumA);
	h0 = rowsumA/norm(rowsumA);
	cout << "Column sums of A:\n" << colsumA << endl;
	cout << "Row sums of A:\n" << rowsumA << endl;
	cout << "a_{0}:\n" << a0 << endl;
	cout << "h_{0}:\n" << h0 << endl;
	
	cout << "\nThe Internet Search Engines Computation:" << endl;
	mat ai_num, hi_num;
	vec ai, hi;
	hi = h0;
	ai = a0;
	int N = 10;
	
	// With for loop for a_{i}
	for (int i = 1; i <=N; i++)
	{
		ai_num = A.t()*A*ai;
		ai = ai_num/norm(ai_num);

		cout <<"\na_{"<< i <<"}:" << "\n" << ai <<endl; 
	}

	// With for loop for h_{i}
	for (int i = 1; i <=N; i++)
	{
		hi_num = A*A.t()*hi;
		hi = hi_num/norm(hi_num);

		cout <<"\nh_{"<< i-1 <<"}:" << "\n" << hi <<endl; 

	}
	return 0;
}