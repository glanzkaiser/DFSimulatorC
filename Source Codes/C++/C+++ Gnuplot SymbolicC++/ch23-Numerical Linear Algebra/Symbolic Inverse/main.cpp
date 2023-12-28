// g++ -o result main.cpp -lsymbolicc++
// make 
// (adjust the cpp filename first)

#include <iostream>
#include "symbolicc++.h"
using namespace std;

int main(void)
{
	Symbolic a("a");
	Symbolic b("b");
	Symbolic c("c");
	Symbolic d("d");

	Symbolic A = ( (  a, b ),
				( c, d ) );
	cout << "A = " << A << endl; // 
	Symbolic AI = A.inverse();
	cout << "A^{-1} = " << AI << endl;
	
 return 0;
}