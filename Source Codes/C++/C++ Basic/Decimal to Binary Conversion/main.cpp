#include <iostream>
#include <chrono>
#include <string>
#include <bitset>

using namespace std;
using namespace std::chrono;

int main()
{

	// Get starting timepoint
	auto start = high_resolution_clock::now();

	int decimalNumber = 51;

	// Create a bitset with a specified number of bits (e.g., 8 for char, 32 for int)
	// and initialize it with the decimal number.
	string binaryString = bitset<32>(decimalNumber).to_string(); 

	// Get ending timepoint
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

	cout << "Binary representation of " << decimalNumber << ": " << binaryString << endl ;
	cout << "Time taken by function: " << duration.count() << " nanoseconds" << endl;

    return 0;
}