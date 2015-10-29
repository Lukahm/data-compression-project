#include "huffmanNode.h"
#include "huffmanCode.h"
#include "bitString.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <time.h>

using namespace std;


int main()
{
	
	//read original file into string
	std::ifstream inputFile("example.txt");
	if (inputFile.bad())
		throw std::logic_error("bad file");
	std::string fileString((std::istreambuf_iterator<char>(inputFile)),std::istreambuf_iterator<char>());

	//initialize bit string
	bitString string(fileString);

	//get user iput bit length
	int bitLength;
	cout << "Please enter an bit length(between 1 to 31): ";
	cin >> bitLength;	
	if (bitLength>=32)
		throw std::logic_error("invalid bit length");

	//timer initializaiton 
	clock_t tStart = clock();

	//split the bit string according to user demand
	std::vector<unsigned > vec= string.splitByBitLength(bitLength);

	//user defined bit string
	std::string huffmanString(vec.begin(), vec.end());

	//huffman coding for user defined huffman string
	huffmanCode* test1 = new huffmanCode(huffmanString);

	//get normal 8bit for huffman decoding
	//huffmanCode* test2 = new huffmanCode(fileString);

	//dispaly character frequency and huffman table
	test1->printFrequencyTable();
	test1->printHuffmanTable();
	
	//get encoded data
	std::string encodeData = test1->getEncodedData();
	cout << "Encoded string: " << encodeData << endl << endl;
	
	//get decoded data
	std::string decodeData = test1->getDecodedData();
	cout << "Decoded string: " << decodeData << endl << endl;
	
	//std::string decodeData2 = test2->getDecodedData();
	//cout << "Decoded string: " << decodeData2 << endl << endl;

	//entropy calculation
	test1->getEntropy();	
	delete test1;
	//delete test2;
	//compression ratio calcualtion
	double compressionRatio = (double)(string.data()).size() / (double)encodeData.size();
	cout <<" The compression ratio is " << compressionRatio << endl << endl;	

	//time cost for compression
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	
	system("pause");
	return 0;
}

