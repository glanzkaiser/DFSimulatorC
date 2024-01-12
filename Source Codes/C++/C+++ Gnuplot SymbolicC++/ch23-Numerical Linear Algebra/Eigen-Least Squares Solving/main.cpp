// g++ -o result main.cpp 
// The most general and accurate method to solve under- or over-determined linear systems
#include <eigen3/Eigen/Dense> // header file
#include <iostream>

using std::cout;
using std::endl;
using namespace std;
 
int main()
{
	Eigen::MatrixXf A;
	Eigen::VectorXf b;
	Eigen::MatrixXf A = Eigen::MatrixXf::Random(3, 2);
	//A << 4,3,2,1,  
	//12,9,3,4,  
	//-4,-3,-2,4;
		
	cout << "Here is the matrix A:\n" << A << endl;
	Eigen::VectorXf b = Eigen::VectorXf::Random(3);
	//b << 1, 10, 4;	
	cout << "Here is the right hand side b:\n" << b << endl;
	cout << "The least-squares solution is:\n" << A.template bdcSvd<Eigen::ComputeThinU | Eigen::ComputeThinV>().solve(b) << endl;
}