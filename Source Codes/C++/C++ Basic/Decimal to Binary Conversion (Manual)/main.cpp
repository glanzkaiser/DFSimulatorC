#include <iostream>
#include <string>
#include <algorithm> // For std::reverse
#include <chrono>

using namespace std;
using namespace std::chrono;

// Manual Conversion using Division and Modulo:
// This method involves repeatedly dividing the decimal number by 2 and recording the remainders, which represent the binary digits.

string decimalToBinary(int n) {
	if (n == 0) 
	{
		return "0";
	}
	std::string binaryString = "";
	while (n > 0) 
	{
	        binaryString += (n % 2 == 0 ? '0' : '1');
	        n /= 2;
	}
	std::reverse(binaryString.begin(), binaryString.end()); // Reverse to get correct order
	return binaryString;
}

// Using Bitwise Operations:
// This method involves checking each bit position using bitwise AND and right-shifting.
// The loop iterates from the most significant bit (e.g., 31 for a 32-bit integer) down to 0.
// n >> i shifts the bits of n to the right by i positions, bringing the i-th bit to the least significant position.
// k & 1 performs a bitwise AND with 1 to check if the least significant bit is set (1) or not (0).
// Leading zeros are removed to get a concise binary representation.
string decimalToBinaryBitwise(int n) {
	if (n == 0) 
	{
		return "0";
	}
	std::string binaryString = "";
	// Assuming 32-bit integer, iterate from most significant bit
	for (int i = 31; i >= 0; --i) { 
	int k = n >> i; // Right-shift to bring the i-th bit to the LSB position
		if (k & 1) 
		{ // Check if the LSB is 1
		    binaryString += '1';
		} 
		else 
		{
		    binaryString += '0';
		}
	}
	// Remove leading zeros if necessary
	size_t firstOne = binaryString.find('1');
	if (firstOne == std::string::npos) 
	{ // All zeros
		return "0";
	}
	return binaryString.substr(firstOne);
}

int main() {
	// Get starting timepoint
	auto start = high_resolution_clock::now();

	int decimalNumber = 23;
	cout << "1st Method: Binary representation of " << decimalNumber << ": " << decimalToBinary(decimalNumber) << endl;

	cout << "2nd Method: Binary representation of " << decimalNumber << ": " << decimalToBinaryBitwise(decimalNumber) << endl;

	// Get ending timepoint
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);
	cout << "Time taken by function: " << duration.count() << " nanoseconds" << endl;
	return 0;
}