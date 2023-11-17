// Example for C++ Interface to Gnuplot

// requirements:
// * gnuplot has to be installed (http://www.gnuplot.info/download.html)
// g++ main.cpp
// or
// make
// plot graph in C++ with Gnuplot
// There is gnuplot iostream to send data from c++ to gnuplot. 

#include <iostream>
#include "gnuplot_i.hpp" //Gnuplot class handles POSIX-Pipe-communication with Gnuplot

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
 #include <conio.h>   //for getch(), needed in wait_for_key()
 #include <windows.h> //for Sleep()
 void sleep(int i) { Sleep(i*1000); }
#endif

#define SLEEP_LGTH 2  // sleep time in seconds
#define NPOINTS    50 // length of array

void wait_for_key(); // Programm halts until keypress

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{

    cout << "*** example of gnuplot control through C++ ***" << endl << endl;

    try
    {
        Gnuplot g1("lines");

        cout << "*** plotting slopes" << endl;
        g1.set_title("Function Plotting");

        //cout << "y = sin(x)" << endl;
        //g1.plot_equation("sin(x)","sine");

        //cout << "y = log(x)" << endl;
        //g1.plot_equation("log(x)","logarithm");
	
	cout << "y = exp(x) * tan(2*x)" << endl;
        g1.plot_equation("exp(x)*tan(2*x)","exponential and trigonometric product");
	
        //cout << "y = sin(x) * cos(2*x)" << endl;
        //g1.plot_equation("sin(x)*cos(2*x)","sine product");

	g1.showonscreen(); // window output

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
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}
