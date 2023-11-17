// Demo of fit curve
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams -lboost_system -lboost_filesystem

#include <fstream>
#include <vector>
#include <cmath>

#include "gnuplot-iostream.h"

const int numRows=11;
const int numCols=1;

using std::cout;
using std::endl;
using namespace std;

int main() {
	std::fstream in("matrix.txt");
	float tiles[numRows][numCols];
	std::vector<std::pair<double, double>> xy_pts;

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			in >>tiles[i][j]; // get data row i column j from the textfile
			cout <<tiles[i][j] << ' '<< endl;	
		}
		xy_pts.emplace_back(i, tiles[i][0]); // Thanks a lot Beautiful Goddess, Freya!!!
	}	
	Gnuplot gp;        

    	gp << "set xrange [0:12]\n";
    	gp << "f(x) = a + b*x + c*x*x\n";
    	gp << "fit f(x) '-' via a,b,c\n";
    	gp.send1d(xy_pts);
    	gp << "plot '-' with points title 'input', f(x) with lines title 'fit'\n";
    	gp.send1d(xy_pts);
}