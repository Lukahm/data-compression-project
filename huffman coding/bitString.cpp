#include "bitString.h"
#include <string>
#include <vector>
#include <bitset>

//bit string constructor
bitString::bitString(std::string const& input)
: data_{ dataProcess(input) }
{}

//get data
std::string bitString::data() 
{
	return data_;
}

//string function
std::string bitString::str() const
{
	auto str = data_;
	for (auto& ch : str) ch += 48;
	return str;
}

//make input char to binary
std::string bitString::charToBi(char ch) 
{
	auto bs = std::string(8, 0);
	for (int i = 7; i != -1; --i)
		bs[i] = (ch >> (7 - i)) & 0x1;
	return bs;
}

// make input binary to usigned int
unsigned bitString::biToUnsigned(std::string const& str)
{
	auto ret = unsigned  (0);
	for (int i = str.size() - 1; i != -1; --i)
		ret |= ((str[i] & 0x1) << (str.size() - 1 - i));
	return ret;
}


//split input string
std::vector < unsigned  > bitString::splitByBitLength(unsigned len)
{
	static const unsigned   max_len = 8 * sizeof(unsigned  );
	if (len > max_len)
		throw std::exception{ "too many bits" };

	auto ret = std::vector < unsigned > {};
	auto pos = unsigned(0);
	for (; data_.size() - pos > len; pos += len)
	ret.push_back(biToUnsigned(data_.substr(pos, len)));
	ret.push_back(biToUnsigned(data_.substr(pos)));

	return ret;
}


//make input data string to binary code
std::string bitString::dataProcess(std::string const& input)
	{
		auto data = std::string{};
		for (auto ch : input)
			data += charToBi(ch);
		return data;
	}


