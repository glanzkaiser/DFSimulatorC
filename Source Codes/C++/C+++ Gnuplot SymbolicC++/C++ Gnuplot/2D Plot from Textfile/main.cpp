// Use fstream to read from a file, and ofstream to write to a file.
// g++ -o result main.cpp

#include <iostream>
#include <fstream>
#include <string>
#include "gnuplot_i.hpp" //Gnuplot class handles POSIX-Pipe-communication with Gnuplot

#define NPOINTS 11 // length of array

const int numRows=11;
const int numCols=1;

void wait_for_key(); // Programm halts until keypress

using std::cout;
using std::endl;
using namespace std;

int main(int argc, char* argv[])
{
	cout << "*** Example of Gnuplot plot data from txt through C++ ***" << endl << endl;
	std::fstream in("matrix.txt");
	float tiles[numRows][numCols];
	std::vector<double> y;
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			in >>tiles[i][j]; // get data row i column j from the textfile
			cout <<tiles[i][j] << ' '<< endl;	
		}
		y.push_back((float)tiles[i][0]); // Thanks for telling me this trick Freya.. I owe you a lot.
	}	

	try
	{
        std::vector<double> x;
        for (int i = 0; i < NPOINTS; i++)  // fill double array x
        {
            	x.push_back((double)i);             // x[i] = i	
        }
	Gnuplot g1("lines");
        cout << endl << endl << "*** user-defined lists of points (x,y)" << endl;
        g1.set_grid();
        g1.set_style("linespoints").plot_xy(x,y,"(x,y)");
	
        wait_for_key();

	}
	catch (GnuplotException ge)
	{
        cout << ge.what() << endl;
	}

    cout << endl << "*** end of gnuplot example" << endl;

    return 0;
}

void wait_for_key ()
{
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    return;
}
