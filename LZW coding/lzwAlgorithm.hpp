#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <iostream>
#ifndef lzwAlgorithm_HPP
#define lzwAlgorithm_HPP

//////////////////LZW compress algorithm

//s = empty string;
//while (there is still data to be read)
//{
//	ch = read a character;
//	if (dictionary contains s + ch)
//	{
//		s = s + ch;
//	}
//	else
//	{
//		encode s to output file;
//		add s + ch to dictionary;
//		s = ch;
//	}
//}
//encode s to output file;

std::vector<int>  compress(std::istream &is, std::ostream &os) {

	std::vector<int> uncompressed;

	//build dictionary  with ascii
	std::map<std::vector<char>, int> dictionary;

	for (int c = 0; c <256; ++c)
	{
		const int dictionary_size = dictionary.size();
		dictionary[{static_cast<char> (c)}] = dictionary_size;
	}

	std::map<std::vector<char>, int>::iterator it = dictionary.begin();
	//lzw compression algorithm
	std::vector<char> currentstring;
	char charinfile;
	while (is.get(charinfile)){
		currentstring.push_back(charinfile);		//std::string wc=w+c;
		if (dictionary.count(currentstring) == 0){
			const int dictionary_size = dictionary.size();
			// add wc to the dictionary.
			dictionary[currentstring] = dictionary_size;
			currentstring.pop_back();
			os.write(reinterpret_cast<const char *> (&dictionary.at(currentstring)), sizeof (int));
			uncompressed.push_back(dictionary[currentstring]);
			currentstring = { charinfile };
		}
	}

	// output the code for w.
	if (!currentstring.empty()){
		os.write(reinterpret_cast<const char *> (&dictionary.at(currentstring)), sizeof (int));
		uncompressed.push_back(dictionary[currentstring]);
	}
	return uncompressed;
}


void print(std::pair<std::vector<char>, int> p) { std::cout << p.second << std::endl; }

//////////////////LZW decompress algorithm

//
//read a character k;
//output k;
//w = k;
//while (read a character k)
///* k could be a character or a code. */
//{
//	if k exists in the dictionary
//		entry = dictionary entry for k;
//	output entry;
//	add w + entry[0] to dictionary;
//	w = entry;
//	else
//		output entry = w + firstCharacterOf(w);
//	add entry to dictionary;
//	w = entry;
//}


template<typename Container>
std::string decompress(Container const&vector) {
	// Build the dictionary.
	int dictSize = 255;
	std::map<int, std::string> dictionary;
	for (int i = 0; i < 256; i++)
		dictionary[i] = std::string(1, i);

	std::string w;
	std::string output;
	std::string entry;
	//while (read a character k)
	for (auto it = std::begin(vector); it != std::end(vector); ++it) {
		//k quals first element in compressed string
		int k =*it;

		//	if k exists in the dictionary
		if (dictionary.count(k))
			entry = dictionary[k];
		//	else output entry = w + firstCharacterOf(w);
		else if (k == dictSize)
			entry = w + w[0];
		else
			throw "bad compressed k";
		output += entry;

		// Add w+entry[0] to the dictionary.
		dictionary[dictSize++] = w + entry[0];

		w = entry;
	}
	return output;
}

#endif lzwCompress_HPP



