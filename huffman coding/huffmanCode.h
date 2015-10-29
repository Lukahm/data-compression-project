#ifndef huffmanCode_H
#define huffmanCode_H
#include<queue>
#include <string>
#include <map>
#include "huffmanNode.h"
using namespace std;

class huffmanCode{
private:
	string data;
	string encodedData;
	string decodedData;
	map<char, int> frequencyTable;
	map<char, string> huffmanTable;
	void makeFrequencyTable();
	void makeHuffmanTree();
	void huffmanEncoding(huffmanNode *head, string str);
	void encodingString();
public:

	huffmanCode(string);
	string getEncodedData()	{ return encodedData; };
	string getDecodedData() { return decodedData; };
	void printFrequencyTable();
	void printHuffmanTable();
	string str(std::string data);
	void getEntropy();
	string huffmanDecoding(huffmanNode* root, string encodedStr);

};

class compareFunctor{
public:
	bool operator()(huffmanNode *lhs, huffmanNode *rhs)
	{
		return lhs->frequency > rhs->frequency;
	}
};

void printCodes(huffmanNode *head, string str);


#endif