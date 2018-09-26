#include <string>
#ifndef CONVERTOR_H_
#define CONVERTOR_H_

extern std::string hexValue;
std::string int2hex(unsigned int);
bool compare(std::string, std::string);
std::string sub(std::string, std::string);
std::string add(std::string, std::string);
std::string multi(std::string, int);
int hex2int(char);

#endif /* CONVERTOR_H_ */
