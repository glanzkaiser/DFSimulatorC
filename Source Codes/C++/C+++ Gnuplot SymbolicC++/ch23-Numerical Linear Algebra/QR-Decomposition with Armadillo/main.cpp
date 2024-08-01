// Merci beaucoup Freya et Sentinel
// g++ main.cpp -o result -larmadillo

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
	mat A;
	int n = 3;
	A.load("MatrixA.txt");	
	
	cout << "Matrix A:" << endl;
	A.print();
	cout << endl;

	// determinant
	cout << "det(A): " << det(A) << endl;
	
	cout <<"QR-decomposition with manual computation :\n"<<endl;
	
	arma::vec u1(n,fill::zeros); 
	u1[0] = A.col(0)[0];
	u1[1] = A.col(0)[1];
	u1[2] = A.col(0)[2];
	arma::vec u2(n,fill::zeros); 
	u2[0] = A.col(1)[0];
	u2[1] = A.col(1)[1];
	u2[2] = A.col(1)[2];
	arma::vec u3(n,fill::zeros); 
	u3[0] = A.col(2)[0];
	u3[1] = A.col(2)[1];
	u3[2] = A.col(2)[2];

	cout <<"Vector u1 :" << "\n" << u1 <<endl;
	cout <<"|| u1 || :"  << norm(u1) <<endl;
	cout <<"\nVector u2 :" << "\n" << u2 <<endl;
	cout <<"|| u2 || :"  << norm(u2) <<endl;
	cout <<"\nVector u3 :" << "\n" << u3 <<endl;
	cout <<"|| u3 || :"  << norm(u3) <<endl;

	arma::vec v1(n,fill::zeros); 
	arma::vec v2(n,fill::zeros); 
	arma::vec v3(n,fill::zeros); 
	arma::vec q1(n,fill::zeros); 
	arma::vec q2(n,fill::zeros); 
	arma::vec q3(n,fill::zeros); 
	arma::vec u2projW1(n,fill::zeros); 
	arma::vec u3projW2(n,fill::zeros); 
	arma::mat Q(n,n,fill::zeros);
	
	// The Gram-Schmidt Process
	v1 = u1;
	
	u2projW1 = (dot(u2,v1)/(pow(norm(v1),2)))*v1;	
	v2 = u2 - u2projW1;
	
	u3projW2 = (dot(u3,v1)/(pow(norm(v1),2)))*v1 + (dot(u3,v2)/(pow(norm(v2),2)))*v2;	
	v3 = u3 - u3projW2;
	
	q1 = v1/norm(v1);
	q2 = v2/norm(v2);
	q3 = v3/norm(v3);
	
	cout <<"\nq1 :\n" << q1 <<endl;
	cout <<"q2 :\n" << q2 <<endl;
	cout <<"q3 :\n" << q3 <<endl;

	Q.col(0) = q1;
	Q.col(1) = q2;
	Q.col(2) = q3;

	cout <<"Q :\n" << Q <<endl;

	// Create matrix R
	arma::mat R(n,n,fill::zeros);
	
	for (int i = 0; i <n; ++i)
	{
		for(int j = 0; j<n; ++j)
		{
			R[i+j*n] = dot(Q.col(i),A.col(j));
		}			
	}
	
	cout <<"R :\n" << R <<endl;

	cout <<"Q*R :\n" << Q*R <<endl;

	// QR-Decomposition with Armadillo library	
	mat Q1;
	mat R1;
	qr(Q1,R1,A);

	cout <<"QR-decomposition with automatic Armadillo function :\n"<<endl;
	cout <<"Q :\n" << Q1 <<endl;
	cout <<"R :\n" << R1 <<endl;

	cout << endl;
		
	return 0;
}
