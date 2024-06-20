// g++ -o result main.cpp
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
	mat Sigma1, Sigma2real, Sigma2complex, Sigma3;

	mat I2(2,2, fill::eye);
	
	Sigma1.load("MatrixSigma1.txt");
	Sigma2real.load("MatrixSigma2real.txt");
	Sigma2complex.load("MatrixSigma2complex.txt");
	Sigma3.load("MatrixSigma3.txt");
	
	cx_mat Sigma2(Sigma2real,Sigma2complex);
	
	cout <<"Matrix I2:" << "\n" << I2 <<endl;
	cout << endl;
	cout <<"Matrix Sigma 1:" << "\n" << Sigma1 <<endl;
	cout << endl;
		
	cout <<"Matrix Sigma 2:" << "\n" << Sigma2 <<endl;
	cout << endl;
	cout <<"Matrix Sigma 3:" << "\n" << Sigma3 <<endl;
	cout << endl;
	
	mat Beta(2,2, fill::zeros);
	Beta.submat(0,0,0,0)  = I2;
	Beta.submat(1,1,1,1) = I2;
	
	cout <<"Matrix Beta:" << "\n" << Beta <<endl;
	cout << endl;
	
	mat Alphax(2,2, fill::zeros);
	cx_mat Alphay(2,2, fill::zeros);
	mat Alphaz(2,2, fill::zeros);
	
	
	//Alphay.set_real(Sigma2real);
	//Alphay.set_imag(Sigma2complex);

	return 0;
}