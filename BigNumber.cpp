#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <map>
#include <string>
#include "BigNumber.h"

#include "tool.h"
using namespace std;
/*
 *	BigNumber class implementation
 * 	There are four constructors
 * 		BigNumber() , BigNumber(unsigned int)
 * 		BigNumber(string) , BigNumber(bool,int,string)
 *	But in main function only use BigNumber(bool,int,string) constructor.
 	Then we have
 * 	BigNumber operators (+-*%/)
 * 	Print function to print the BigNumber value
 *
 * */
BigNumber::BigNumber() {
	this->data = "0";
	this->sign = false;
	this->size = 0;
}

BigNumber::BigNumber(unsigned int input) {
	this->data = int2hex(input);
	this->size = data.length();
	this->sign = false;
}

BigNumber::BigNumber(string input) {
	this->data = input;
	this->size = input.length();
	this->sign = false;
}
BigNumber::BigNumber(bool sign, unsigned int size, string input) {
	this->data = input;
	this->size = size;
	this->sign = sign;

}

BigNumber BigNumber::operator +(BigNumber right) {
	string result;
	bool iscarry = false;
	string s1 = this->data;
	string s2 = right.data;

	int s1_size = this->size;
	int s2_size = right.size;
	//longer(bigger) one on the left side
	if (s1_size < s2_size) {
		s1.swap(s2);
		swap(s1_size, s2_size);
	}
	// Addition calculation
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
		//store the value in hexadecimal
		result.insert(result.begin(), hexValue[temp]);
	}
	// Final check the carry value, if true then add '1' on the front.
	if (iscarry) {
		result.insert(result.begin(), hexValue[1]);
	}
	return BigNumber(false, result.length(), result);

}

BigNumber BigNumber::operator -(BigNumber right) {
	string result;
	bool sign = false; //default is false(+)
	bool borrow = false;
	string s1 = this->data;
	string s2 = right.data;
	int s1_size = this->size;
	int s2_size = right.size;
	// compare s1 and s2, bigger one on the left side
	if (!compare(s1, s2)) {
		sign = true; // if s1<s2 then sign is true(-)
		s1.swap(s2);
		swap(s1_size, s2_size);
	}
	// supplement 0 on the right one until length equal to left one
	while (s1_size > s2_size) {
		s2.insert(s2.begin(), '0');
		s2_size = s2.length();
	}
	// Subtraction calculation
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
		//store the value in hexadecimal
		result.insert(result.begin(), hexValue[temp]);
	}
	// remove 0 from the beginning of the string
	while (result[0] == '0' && result.length() > 1)
		result.erase(0, 1);
	return BigNumber(sign, result.length(), result);
}

BigNumber BigNumber::operator *(BigNumber right) {
	bool sign = false;
	// if two BigNumber have different sign ==> sign will be true(-)
	if (this->sign != right.sign)
		sign = true;

	string s1 = this->data;
	string s2 = right.data;
	int s1_size = this->size;
	int s2_size = right.size;
	// construct a string to store value
	string result(s1_size + s2_size + 1, '0');

	//multiplication calculation
	for (int i = s1_size; i > 0; --i) {
		int carry = 0;
		int n1 = hex2int(s1[i - 1]);
		//if multiplier is 0, the value will be 0
		if (n1 == 0)
			continue;
		for (int j = s2_size; j > 0; --j) {
			int n2 = hex2int(s2[j - 1]);
			int sum = n1 * n2 + hex2int(result[i + j]) + carry; // sum need to add previous value which is in equal index and carry value
			carry = sum / 16; // calculate the carry value
			result[i + j] = hexValue[sum % 16]; // store the remain value in result
		}
		if (carry > 0)
			result[i] = hexValue[hex2int(result[i]) + carry];
	}
	// remove 0 from the beginning of the string
	while (result.at(0) == '0' && result.length() > 1)
		result.erase(0, 1);
	return BigNumber(sign, result.length(), result);

}

BigNumber BigNumber::operator /(BigNumber right) {
	bool sign = false;
	// if two BigNumber have different sign ==> sign will be true(-)
	if (this->sign != right.sign)
		sign = true;
	string result; //store quotient
	string s1 = this->data;
	string s2 = right.data;
	// divisor can't not be 0
	if (s2 == "0") {
		cout << "You can't divide by 0." << endl;
		exit(1);
	}
	// if s1<s2 ,then return 0
	if (!compare(s1, s2))
		return (BigNumber(sign, 1, "0"));
	int s1_size = this->size;
	int index = 0; // record which index is using now
	string temp; // use temp to store current divisor

	// long division calculation
	while (index < s1_size) {

		temp += s1[index++];
		// temp need bigger than s2, if not, then supplement 0 to result and add next index value to temp.
		while (!compare(temp, s2) && index < s1_size) {
			result += hexValue[0];
			temp += s1[index++];
		}
		// If last round temp equal to product (temp is start with 0 now), we need to remove the beginning 0 from temp.
		while (temp.at(0) == '0')
			temp.erase(0, 1);
		int multiplier = 8; // I use 8 as first multiplier, because it is half of 16.
		string product = multi(s2, multiplier); // And calculate s2*multiplier store in product. 
		
		//We want to get a product value between temp and temp-s2.
		//So we will do following calculation.
		
		// if temp>=product
		if (compare(temp, product)) {
			// add s2 to product until > temp.
			while (compare(temp, product)) {
				product = add(product, s2);
				++multiplier;
			}
			//Then subtract s2 ,because we need to keep  0 <= (temp-product) < s2
			--multiplier;
			product = sub(product, s2);
		}
		// if temp<product
		else {
			// subtract s2 from product until product <= temp
			while (!compare(temp, product)) {
				--multiplier;
				product = sub(product, s2);
			}
		}
		temp = sub(temp, product); // subtract product from temp, and remain value store in temp will be used for next round.
		result += hexValue[multiplier]; // the multiplier value is quotient
	}

	// remove 0 from the beginning of the string
	while (result.at(0) == '0' && result.length() > 1)
		result.erase(0, 1);
	return BigNumber(sign, result.length(), result);

}

BigNumber BigNumber::operator %(BigNumber right) {
	/* The algorithm used in module(%) is equal to division
	 * Remainder will be the last temp value*/
	string s1 = this->data;
	string s2 = right.data;
	string remainder;
	if (s2 == "0") {
		cout << "You can't mod 0." << endl;
		exit(1);
	}
	if (!compare(s1, s2))
		return (BigNumber(sign, s1.length(), s1));
	int s1_size = this->size;
	int index = 0;
	string temp;

	while (index < s1_size) {
		temp += s1[index++];
		while (!compare(temp, s2) && index < s1_size)
			temp += s1[index++];
		while (temp.at(0) == '0')
			temp.erase(0, 1);
		int multiplier = 8;
		string product = multi(s2, multiplier);
		if (compare(temp, product)) {
			while (compare(temp, product)) {
				++multiplier;
				product = add(product, s2);
			}
			--multiplier;
			product = sub(product, s2);
		} else {
			while (!compare(temp, product)) {
				--multiplier;
				product = sub(product, s2);
			}
		}
		temp = sub(temp, product);
	}
	remainder = temp;
	return BigNumber(false, remainder.length(), remainder);
}

void BigNumber::Print() {
	// if sign is true then add '-' in the front.
	if (this->sign)
		cout << "-" << this->data << endl;
	else
		cout << this->data << endl;
}
BigNumber::~BigNumber() {
	// TODO Auto-generated destructor stub
}

