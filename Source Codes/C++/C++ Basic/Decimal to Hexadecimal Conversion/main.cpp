#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
	// Get starting timepoint
	auto start = high_resolution_clock::now();

	int decimal_value = 75;
	cout << "Decimal: " << decimal_value << endl;
	cout << "Hexadecimal: " << std::hex << decimal_value << endl;

	// Get ending timepoint
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

	cout << "Time taken by function: " << duration.count() << " nanoseconds" << endl;

	return 0;
}