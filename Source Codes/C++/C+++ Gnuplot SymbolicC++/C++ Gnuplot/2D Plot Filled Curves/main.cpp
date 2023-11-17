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
	Gnuplot g1("filledcurves");
        cout << "filled curves" << endl;
        g1.set_legend("outside right top").set_xrange(-5,5);
        g1.plot_equation("x*x").plot_equation("-x*x+4");

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
