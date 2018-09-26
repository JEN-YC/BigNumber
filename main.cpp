#include <iostream>
#include "BigNumber.h"
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string s1, s2;
	string hexValue = "0123456789abcdefABCDEF";
	bool validate = false;
	//We will validate user input here, check if the number is hexadecimal.
	while(!validate){
		cout << "Pleas input two hexadecimal number (Don't start with 0x) " << endl;
		cout << "First Number:" << endl;
		getline(cin,s1);
		cout << "Second Number:" << endl;
		getline(cin,s2);
		int check1, check2;
		check1 = s1.find_first_not_of(hexValue);
		check2 = s2.find_first_not_of(hexValue);
		if(check1 == string::npos && check2 ==string::npos)
			validate = true;
		else
			cout << "Your input is not hexadecimal, try again." << endl;
	}
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	cout << "a = " << s1 << endl;
	cout << "b = " << s2 << endl << endl;
	BigNumber a(false, s1.length(), s1);
	BigNumber b(false, s2.length(), s2);
	BigNumber ans;
	string input;
	while (1) {
		cout<< "\nYou can type (e.g. a+b,a/b...), and i will give you the answer. (N/n to leave)"<< endl;
		getline(cin,input);
		if(input == "N" || input == "n") {
			cout<<"Bye~"<<endl;
			break;
		}
		if(input.length() != 3){
			cout<<"Input is wrong, please try again."<<endl;
			continue;
		}

		transform(input.begin(), input.end(), input.begin(), ::tolower);
		char symbol = input[1];
		if (input[0] == 'a' && input[2] == 'b') {
			switch (symbol) {
			case '+':
				ans = a + b;
				break;
			case '-':
				ans = a - b;
				break;
			case '*':
				ans = a * b;
				break;
			case '/':
				ans = a / b;
				break;
			case '%':
				ans = a % b;
				break;
			default:
				cout << "Input is wrong, please try again!" << endl;
				continue;
			}
		} else if (input[0] == 'b' && input[2] == 'a') {
			switch (symbol) {
			case '+':
				ans = b + a;
				break;
			case '-':
				ans = b - a;
				break;
			case '*':
				ans = b * a;
				break;
			case '/':
				ans = b / a;
				break;
			case '%':
				ans = b % a;
				break;
			default:
				cout << "Input is wrong, please try again!" << endl;
				continue;
			}
		} else{
			cout << "Input is wrong, please try again!" << endl;
			continue;
		}
		cout << input << " = ";
		ans.Print();
	}
	return 0;
}
