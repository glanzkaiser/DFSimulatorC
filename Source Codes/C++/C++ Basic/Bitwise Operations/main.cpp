#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{

	// Get starting timepoint
	auto start = high_resolution_clock::now();

	int a = 5;  // Binary: 0101
	int b = 3;  // Binary: 0011
	int c_and = a & b; // c_and = 1 (Binary: 0001)
    	int c_or = a | b; // c_or = 7 (Binary: 0111)
	int c_xor = a ^ b; // c_xor = 7 (Binary: 0111)
	int a_not = ~a; //  Binary a : 00000101 (assuming 8-bit representation for simplicity), Binary ~ a: 11111010, two's complement representation
	int a_leftshift = a << 2; // From binary: 0101 to binary 010100
	int a_rightshift = a >> 2;  // From binary: 0101 to binary 01
	// Get ending timepoint
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<nanoseconds>(stop - start);

	cout << "a = " << a << "\nb = " << b << endl;
	cout << "a & b = " << c_and << endl;
	cout << "a ! b = " << c_or << endl;
	cout << "a ^ b = " << c_xor << endl;
	cout << "~a = " << a_not << endl;
	cout << "a << 2 = " << a_leftshift << endl;
	cout << "a >> 2 = " << a_rightshift << endl;
	cout << "Time taken by function: " << duration.count() << " nanoseconds" << endl;

    return 0;
}