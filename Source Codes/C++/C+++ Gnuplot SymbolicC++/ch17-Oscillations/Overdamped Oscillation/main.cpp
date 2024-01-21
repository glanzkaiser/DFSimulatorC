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
        cout << "Overdamped Oscillations Equations Plot" << endl;
        g1.set_title("Overdamped Oscillations");
	g1.set_xlabel("t");
	g1.set_xrange(0,30).set_samples(200);
	g1.set_yrange(-2,3).set_samples(200);
	// A exp(-ct/2m)
	// c = 2.3; m = 1; A = 5; k = 0.25
        g1.plot_equation("exp(x*(0.5*(-2.3+sqrt(2.3**2 - 1)))) + exp(x*(0.5*(-2.3-sqrt(2.3**2 - 1)))) ", "e^{r_{1} t} +  e^{r_{2} t}");
        g1.plot_equation("2*exp(x*(0.5*(-2.3+sqrt(2.3**2 - 1)))) - exp(x*(0.5*(-2.3-sqrt(2.3**2 - 1)))) ", "2 e^{r_{1} t} - e^{r_{2} t}");
	g1.plot_equation("-1*exp(x*(0.5*(-2.3+sqrt(2.3**2 - 1)))) + 3*exp(x*(0.5*(-2.3-sqrt(2.3**2 - 1)))) ", "- e^{r_{1} t} + 3 e^{r_{2} t}");
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
