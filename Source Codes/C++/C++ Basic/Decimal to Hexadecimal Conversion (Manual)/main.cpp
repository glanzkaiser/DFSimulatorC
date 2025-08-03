#include <iostream>
#include <chrono>
#include <algorithm> // Required for std::reverse

using namespace std;
using namespace std::chrono;

int main() {
	// Get starting timepoint
	auto start = high_resolution_clock::now();

	int decimalNum;
	cout << "Enter a decimal number: ";
	cin >> decimalNum;

	if (decimalNum == 0) 
	{
	cout << "Hexadecimal equivalent: 0" << endl;
	// A special case for decimalNum == 0 is handled, as its hexadecimal equivalent is simply "0".
        return 0;
	}

	string hexResult = "";
	int tempNum = decimalNum;

	// Conversion Loop:
	// A while loop continues as long as tempNum (a copy of decimalNum) is greater than 0.
	// Remainder Calculation: remainder = tempNum % 16 calculates the remainder when tempNum is divided by 16. This remainder is the next hexadecimal digit.
	// Character Conversion:
	// If remainder is less than 10, it's a digit from 0-9, so '0' is added to convert it to its ASCII character.
	// If remainder is 10 or greater, it corresponds to A-F. remainder + 'A' - 10 converts these values (10-15) to their respective hexadecimal character representations ('A'-'F'). 
	// Append to String: The hexDigit is appended to hexResult.
	// Divide for Next Iteration: tempNum /= 16 updates tempNum for the next iteration of the loop. 

	while (tempNum > 0) 
	{
	int remainder = tempNum % 16;
	char hexDigit;

		if (remainder < 10) 
		{
			hexDigit = remainder + '0'; // Convert 0-9 to their character representation
		} 
		else 
		{
			hexDigit = remainder + 'A' - 10; // Convert 10-15 (A-F) to their character representation
		}
	hexResult += hexDigit;
	tempNum /= 16;
	}

	reverse(hexResult.begin(), hexResult.end()); // Reverse the string as digits are collected in reverse order (least significant digit first)

	cout << "Hexadecimal equivalent of " << decimalNum << " is: " << hexResult << endl;

	// Get ending timepoint
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

	cout << "Time taken by function: " << duration.count() << " nanoseconds" << endl;

	return 0;
}