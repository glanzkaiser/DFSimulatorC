#include <iostream>
#include "gnuplot_i.hpp" //Gnuplot class handles POSIX-Pipe-communication with Gnuplot

#define SLEEP_LGTH 2  // sleep time in seconds
#define NPOINTS 50 // length of array

void wait_for_key(); // Programm halts until keypress

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{

    cout << "*** example of gnuplot control through C++ ***" << endl << endl;

    try
    {
        std::vector<double> x, y;

        for (int i = 0; i < NPOINTS; i++)  // fill double arrays x, y, z
        {
            	x.push_back((double)i);             // x[i] = i
            	y.push_back((double)i * (double)i); // y[i] = i^2
        }
	Gnuplot g1("lines");
        cout << endl << endl << "*** user-defined lists of points (x,y)" << endl;
        g1.set_grid();
        g1.set_style("points").plot_xy(x,y,"user-defined points 2d");

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
