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
	Gnuplot g1;
        cout << "plot_image" << endl;
        const int iWidth  = 255;
        const int iHeight = 255;
        g1.set_xrange(0,iWidth).set_yrange(0,iHeight).set_cbrange(0,255);
        g1.cmd("set palette gray");
        unsigned char ucPicBuf[iWidth*iHeight];
        // generate a greyscale image
        for(int iIndex = 0; iIndex < iHeight*iWidth; iIndex++)
        {
            ucPicBuf[iIndex] = iIndex%255;
        }
        g1.plot_image(ucPicBuf,iWidth,iHeight,"greyscale");

        g1.set_pointsize(0.6).unset_legend().plot_slope(0.8,20);

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
