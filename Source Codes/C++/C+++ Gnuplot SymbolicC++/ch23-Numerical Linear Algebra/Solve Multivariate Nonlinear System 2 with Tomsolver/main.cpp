// g++ -o result main.cpp
// Merci beaucoup Freya et Sentinel
#include <tomsolver/tomsolver.hpp>

using namespace tomsolver;

int main() {
	std::setlocale(LC_ALL, ".UTF8");

	try 
	{
	// create equations as a symbolic vector
	SymVec f
	{
	Parse("(x)^2 + (y)^2 - 8*y") - Var("d1"),
	Parse("2*x*y - 8*x") - Var("d2"),
	};

	// replace known values
	f.Subs(VarsTable
	{
		{"a", 1.0},
		{"b", 2.0},
		{"c", 3.0},
		{"d", 4.0},
		{"d1", 0.0},
		{"d2", 0.0},
	});

	cout << f << endl;

	// solve
	auto ans = Solve(f);

	cout << "x = " << ans["x"] << endl;
	cout << "y = " << ans["y"] << endl;
	} 
	catch (const std::exception &err) 
	{
	std::cerr << err.what() << std::endl;
	return -1;
	}

	return 0;
}