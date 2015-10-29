#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include "lzwAlgorithm.hpp"

int main() {

	//read original file 
	std::ifstream inputfile("lzwInput.txt", std::ios_base::binary);
	std::ofstream outputfile("lzwOutput.txt", std::ios_base::binary);

	//initialze vector for store compressed data
	std::vector<int> compressed;

	//compress original data
	compressed = compress(inputfile, outputfile);

	//print compressed data
	for (auto it = std::begin(compressed); it != std::end(compressed); ++it){
		std::cout << '[' << *it << ']' << ' ';
	}
	std::cout << std::endl;
	
	//initialze string for store decompressed data
	std::string decompressed = decompress(compressed);
	std::cout << decompressed << std::endl;
	system("pause");
	return 0;
}