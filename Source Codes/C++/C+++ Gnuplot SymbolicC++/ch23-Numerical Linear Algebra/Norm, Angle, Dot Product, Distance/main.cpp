// 
// Compile it with:
//   g++ -o main main.cpp -lboost_iostreams

#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

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

int* vec2() {
	static int v[N];
	std::fstream in("vector2.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			v[i] =vectortiles[i];	
	}	
	return v;
}

int main() {
	std::vector<std::pair<double, double>> xy_pts;
	int* ptrvec;
	int* ptrvec2;
	ptrvec = vec();
	ptrvec2 = vec2();
	cout << endl;
	cout << "Vector x is: " << endl;
	for (int i = 0; i < N; ++i)
	{
		cout <<ptrvec[i]<< ' ' << endl;	
	}	

	cout << endl;
	cout << "Vector v is: " << endl;
	for (int i = 0; i < N; ++i)
	{
		cout <<ptrvec2[i]<< ' ' << endl;	
	}	
	
	cout << endl;
	
	float dot= 0;
	float distance= 0;
	float normx= 0;
	float normv= 0;

	for (int i = 0; i < N; ++i)
	{
		dot += ptrvec[i] * ptrvec2[i];
		distance += (ptrvec2[i] - ptrvec[i]) * (ptrvec2[i] - ptrvec[i]);
		normx += ptrvec[i] * ptrvec[i];
		normv += ptrvec2[i] * ptrvec2[i];
	}	
	
	float angleformula = dot/(sqrt(normx) * sqrt(normv));

	cout << endl;
	cout << "x . v = " << dot << endl;
	cout << "d(x, v) = " << sqrt(distance) << endl;
	cout << "|| x || = " << sqrt(normx) << endl;
	cout << "|| v || = " << sqrt(normv) << endl;
	
	cout << "θ = " << acos(angleformula*DEGTORAD) * RADTODEG <<endl;
	
	return 0;
}