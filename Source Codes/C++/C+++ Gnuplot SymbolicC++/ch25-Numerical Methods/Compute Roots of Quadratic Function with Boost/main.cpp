// g++ main.cpp -o result -lboost_iostreams
// to find the root of a quadratic function

#include <iostream>
#include <boost/math/tools/roots.hpp>

using namespace std;

int main()
{
auto [x0, x1] = boost::math::tools::quadratic_roots(2, 2, 0);

cout << "x0 =  " << x0 <<endl;
cout << "x1 = " << x1 <<endl;

}

