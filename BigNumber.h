#include <stdint.h>
#include <inttypes.h>
#include <string>

#ifndef BIGNUMBER_H_
#define BIGNUMBER_H_

class BigNumber {
private:
	bool sign;
	unsigned int size;
	std::string data;
public:
	BigNumber();
	BigNumber(unsigned int);
	BigNumber(std::string);
	BigNumber(bool, unsigned int, std::string);

	BigNumber operator+(BigNumber);
	BigNumber operator-(BigNumber);
	BigNumber operator*(BigNumber);
	BigNumber operator/(BigNumber);
	BigNumber operator%(BigNumber);

	void Print();
	virtual ~BigNumber();
};

#endif /* BIGNUMBER_H_ */
