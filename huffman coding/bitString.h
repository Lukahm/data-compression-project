#ifndef bitString_H
#define bitString_H

#include <string>
#include <vector>
#include <bitset>

class bitString{
public:
	
	bitString(std::string const& input);
	std::string charToBi(char ch);
	unsigned biToUnsigned(std::string const& str);
	std::vector < unsigned> splitByBitLength(unsigned  len);
	std::string str() const;
	std::string data();

private:
	std::string data_;
	std::string dataProcess(std::string const& input);
};


#endif