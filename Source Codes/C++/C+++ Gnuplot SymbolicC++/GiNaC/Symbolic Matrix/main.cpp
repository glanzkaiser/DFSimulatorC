// g++ main.cpp -o result -lginac -lcln
#include <iostream>
#include <ginac/ginac.h>

using namespace std;
using namespace GiNaC;

int main()
{
	symbol a("a"), b("b");
	matrix M = { {a,0},
				{0,b}};

	cout << "Matrix M : " << M << endl;
	return 0;
}