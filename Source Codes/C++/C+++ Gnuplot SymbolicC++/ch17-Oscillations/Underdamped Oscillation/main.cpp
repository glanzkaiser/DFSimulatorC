#include <iostream>
#include "gnuplot_i.hpp" //Gnuplot class handles POSIX-Pipe-communication with Gnuplot

void wait_for_key(); // Programm halts until keypress

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{

    cout << "*** example of gnuplot control through C++ ***" << endl << endl;

    try
    {
	Gnuplot g1("lines");
        cout << "Underdamped Oscillations Equations Plot" << endl;
        g1.set_title("Underdamped Oscillations");
	g1.set_xlabel("t");
	g1.set_xrange(0,20).set_samples(200);
	g1.set_yrange(-10,10).set_samples(200);
	// A exp(-ct/2m)
	// c = 0.3; m = 1; A = 5; k = 25
        g1.plot_equation("5*exp(-x*0.3*(0.5))", "A e^{-ct/2m}");
	g1.plot_equation("-5*exp(-x*0.3*(0.5))", "-A e^{-ct/2m}");
	g1.plot_equation("5*exp(-x*0.3*(0.5))*sin(x*0.5*sqrt(4*1*25 - (0.3**2)))","A e^{-ct/2m} sin(omega t + phi_{0})");
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
