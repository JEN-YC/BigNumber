#include <string>
#include <algorithm>
#include "tool.h"

using namespace std;

string hexValue = "0123456789abcdef";

//convert decimal to hex
string int2hex(unsigned int dec) {
	char output[1000];
	sprintf(output, "%X", dec);
	string after(output);
	transform(after.begin(), after.end(), after.begin(), ::tolower);
	return after;
}

//Compare two string , if  s1>= s2 return true ,or s1<s2 return false.
bool compare(string s1, string s2) {
	// compare s1 and s2, longer one on the left side
	if (s1.length() < s2.length()) {
		return false;
	}
	// If they have same length, then compare every index value.
	else if (s1.length() == s2.length()) {
		for (int i = 0; i < s1.length(); ++i) {
			if (hex2int(s1[i]) > hex2int(s2[i])) {
				return true;
			}
			else if (hex2int(s1[i]) == hex2int(s2[i])) {
				continue;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

//Two string subtract, and return the result
string sub(string s1, string s2) {
	int s1_size = s1.length();
	int s2_size = s2.length();
	bool borrow = false;
	string result;
	// supplement 0 on the s2 until length equal to s1
	while (s1_size > s2_size) {
		s2.insert(s2.begin(), '0');
		s2_size = s2.length();
	}
	for (int i = 1; i <= s1_size; ++i) {
		int temp = hex2int(s1[s1_size - i]) - hex2int(s2[s2_size - i]);
		// if last digit borrow, then value -1
		if (borrow)
			--temp;
		// if value < 0, borrow from next digit
		if (temp < 0) {
			borrow = true;
			temp += 16;
		} else
			borrow = false;
		result.insert(result.begin(), hexValue[temp]);
	}
	while (result[0] == '0' && result.length() > 1)
		result.erase(0, 1);
	return result;
}

//Two string add, and return the result
string add(string s1, string s2) {
	string result;
	bool iscarry = false;

	int s1_size = s1.length();
	int s2_size = s2.length();
	//longer(bigger) one on the left side
	if (s1_size < s2_size) {
		s1.swap(s2);
		swap(s1_size, s2_size);
	}
	for (int i = 1; i <= s1_size; ++i) {
		int temp;
		if (i <= s2_size)
			temp = hex2int(s1[s1_size - i]) + hex2int(s2[s2_size - i]);
		else
			temp = hex2int(s1[s1_size - i]);
		// if last digit carry, then value +1.
		if (iscarry) {
			++temp;
			iscarry = false;
		}
		// if the value exceeds 16, then carry.
		if (temp >= 16) {
			iscarry = true;
			temp %= 16;
		}
		result.insert(result.begin(), hexValue[temp]);
	}
	// Final check the carry value, if true then add '1' on the front.
	if (iscarry) {
		result.insert(result.begin(), hexValue[1]);
	}
	return result;
}

// string multiply a integer, and return the result
string multi(string s1, int i) {
	string s2;
	s2 += hexValue[i];
	int s1_size = s1.length();
	int s2_size = s2.length();
	// construct a string to store value
	string result(s1_size + s2_size + 1, '0');
	for (int i = s1_size; i > 0; --i) {
		int carry = 0;
		int n1 = hex2int(s1[i - 1]);
		if (n1 == 0)
			continue;
		for (int j = s2_size; j > 0; --j) {
			int n2 = hex2int(s2[j - 1]);
			int sum = n1 * n2 + hex2int(result[i + j]) + carry;
			carry = sum / 16; // calculate the carry value
			result[i + j] = hexValue[sum % 16]; // store the remain value in result
		}
		if (carry > 0)
			result[i] = hexValue[hex2int(result[i]) + carry];
	}
	while (result.at(0) == '0')
		result.erase(0, 1);
	return result;
}

//convert hex to decimal
int hex2int(char c) {
	switch (c) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'a':
		return 10;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	}
}
