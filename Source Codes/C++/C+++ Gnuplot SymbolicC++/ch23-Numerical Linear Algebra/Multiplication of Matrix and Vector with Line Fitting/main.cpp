// 
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams -lboost_system -lboost_filesystem

#include <fstream>
#include <vector>
#include <cmath>

#include "gnuplot-iostream.h"

const int N = 4;

using std::cout;
using std::endl;
using namespace std;

void printArray(int** arr) {
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cout <<arr[i][j] << ' ';	
		}
		cout << endl;
	}	
}

int* vec() {
	static int x[N];
	std::fstream in("vector1.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			x[i] =vectortiles[i];	
	}	
	return x;
}

struct matrix
{
	int arr1[N][N];
};

struct matrix func(int N)
{
	struct matrix matrix_mem;
	std::fstream in("matrix1.txt");
	float matrixtiles[N][N];
	for (int i = 0; i < N; ++i) 
	{
		for (int j = 0; j < N; ++j) 
		{
			in >> matrixtiles[i][j]; 
			matrix_mem.arr1[i][j] = matrixtiles[i][j] ;
		}
	}
	return matrix_mem;
}

int main() {
	std::vector<std::pair<double, double>> xy_pts;
	int* ptrvec;
	ptrvec = vec();
	cout << endl;
	cout << "Vector x is: " << endl;
	for (int i = 0; i < N; ++i)
	{
		cout <<ptrvec[i]<< ' ' << endl;	
	}	
	
	
	cout << endl;
	cout << "Matrix A is: " << endl;
	
	struct matrix a;
	a = func(N); // address of arr1
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			cout << a.arr1[i][j]<< ' ';	
		}
		cout << endl;
	}	
	
	
	float b[N][N];
	float B[N];
	for (int i = 0; i < N; ++i)
	{
		B[i] = 0;
	}
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			b[i][j] = 0;	
		}		
	}	
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			b[i][j] += a.arr1[i][j] * ptrvec[j];
			//cout << b[i][j] << ' ';	
		}
	}	

	cout << endl;
	cout << "b = A*x : " << endl;
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) 
		{	
			B[i] += b[i][j] ;
		}
		cout << B[i] << endl;
		xy_pts.emplace_back(i, B[i]); 
	}	
	Gnuplot gp;        

    	gp << "set xrange [0:12]\n";
    	gp << "f(x) = a + b*x + c*x*x\n";
    	gp << "fit f(x) '-' via a,b,c\n";
    	gp.send1d(xy_pts);
    	gp << "plot '-' with points title 'input', f(x) with lines title 'fit'\n";
    	gp.send1d(xy_pts);

	return 0;
}