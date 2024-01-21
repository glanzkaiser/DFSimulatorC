// g++ main.cpp -o result -larmadillo

#include <iostream>
#include <armadillo>

using namespace std;

int main()
{
	mat A(4, 5, fill::randu);
	mat B(4, 5, fill::randu);

	cout << A*B.t() << endl;
  
	return 0;
}


