#include <iostream>
#include <chrono>
#include <algorithm> // Required for std::reverse
#include <string>

using namespace std;
using namespace std::chrono;

// Function to convert binary to decimal
long long binaryToDecimal(string binaryNum) {
	long long decimalNum = 0;
	long long power = 1; // Represents 2^0, 2^1, 2^2, etc.

	// Iterate from right to left (least significant bit to most significant bit)
	for (int i = binaryNum.length() - 1; i >= 0; i--) 
	{
		if (binaryNum[i] == '1') 
		{
			decimalNum += power;
		}
        power *= 2;
	}
	return decimalNum;
}

// Function to convert decimal to hexadecimal
string decimalToHexadecimal(long long decimalNum) {
	string hexNum = "";
	char hexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	if (decimalNum == 0) 
	{
        	return "0";
	}

	while (decimalNum > 0) 
	{
		int remainder = decimalNum % 16;
		hexNum = hexChars[remainder] + hexNum; // Prepend to build the hex string
		decimalNum /= 16;
    }
    return hexNum;
}

int main() {
	// Get starting timepoint
	auto start = high_resolution_clock::now();

	string binaryInput;

	cout << "Enter a binary number: ";
	cin >> binaryInput;

	// Convert binary to decimal
	long long decimalResult = binaryToDecimal(binaryInput);

	// Convert decimal to hexadecimal
	string hexadecimalResult = decimalToHexadecimal(decimalResult);
	cout << "Hexadecimal equivalent: " << hexadecimalResult << endl;


	// Get ending timepoint
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

	cout << "Time taken by function: " << duration.count() << " nanoseconds" << endl;

	return 0;
}