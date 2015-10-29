
#include "huffmanNode.h"
#include "huffmanCode.h"
#include<queue>
#include <string>
#include <map>
#include <cassert>
using namespace std;

//constructor
huffmanCode::huffmanCode(string str){
	data = str;
	encodedData = "";
	makeFrequencyTable();
	makeHuffmanTree();
}

void huffmanCode::makeFrequencyTable(){
	//get the frequency count of each symbol
	for (char c : data)
		frequencyTable[c]++;
}


void huffmanCode::getEntropy(){

	int dataLength = data.length();
	double entropy = 0;
	//traverse frequency table to get information entropy
	for (std::pair<char, int> p : frequencyTable) {
		double freq = static_cast<double>(p.second) / dataLength;
		entropy += freq * log2(freq);
	}
	entropy *= -1;
	std::cout << "The information entropy is " << entropy << endl;

}


void huffmanCode::makeHuffmanTree()
{
	//use priority queue to build min heap
	priority_queue<huffmanNode*, vector<huffmanNode*>, compareFunctor> minHeap;
	huffmanNode *head = NULL, *lowest1 = NULL, *lowest2 = NULL;

	//put the character count into the huffman priority queue
	for (auto entry : frequencyTable){

		huffmanNode* n = new huffmanNode();
		n->symbol = entry.first;
		n->frequency = entry.second;
		n->left = n->right = nullptr;
		minHeap.push(n);
	}

	//pop off two lowest at a time
	while (minHeap.size()>1)
	{
		lowest1 = minHeap.top(); minHeap.pop();
		lowest2 = minHeap.top(); minHeap.pop();
		huffmanNode *temp = new huffmanNode();
		temp->frequency = lowest1->frequency + lowest2->frequency;
		temp->left = lowest1; temp->right = lowest2;
		minHeap.push(temp);
	}
	//final one left is the root of huffman tree
	head = minHeap.top(); minHeap.pop();
	//huffman ecoding process
	string code="";
	huffmanEncoding(head, code);
	//get encoding string
	encodingString();
	//huffman decoding process
	huffmanDecoding(head, encodedData);
	return;
}

//encoding
void huffmanCode::huffmanEncoding(huffmanNode *head, string str)
{
	if (head == NULL)return;
	if (head->left == NULL&&head->right == NULL)
	{
		huffmanTable.insert(pair<char, string>(head->symbol, str));
		return;
	}
	if (head->left)huffmanEncoding(head->left, str + "0");
	if (head->right)huffmanEncoding(head->right, str + "1");
	return;
}

//dispaly frequency table
void huffmanCode::printFrequencyTable(){
	cout << "Frequency Table:" << endl;
	map<char, int>::iterator it;
	for (it= frequencyTable.begin(); it != frequencyTable.end(); ++it)
	{
		cout << (it->first) << "\t" << it->second << endl;
	}
}


//dispaly huffman encoding table
void huffmanCode::printHuffmanTable(){
	cout << "Huffman Table:" << endl;
	map<char, string>::iterator it;
	for (it = huffmanTable.begin();it != huffmanTable.end(); ++it){
		cout << it->first << "\t" << it->second << endl;
	}
}

//make huffman encoding string
void huffmanCode::encodingString(){
	for (auto i = 0; i < data.size(); i++){
		encodedData.append(huffmanTable[data.at(i)]);
	}
}

//decoding
string huffmanCode::huffmanDecoding(huffmanNode* root, string encoded_str){

	huffmanNode* node = root;
	for (int i = 0; i != encoded_str.size(); ++i)
	{
		if (encoded_str[i] == '0') { // left child
			node = node->left;
		}
		else { // rigth child
			node = node->right;
		}
		if (node->isLeaf() == true)
		{
			decodedData += node->symbol;
			node = root;
		}
	}
	return decodedData;
}


//string function
std::string huffmanCode::str(std::string data) {
	auto str = data;
	for (auto& ch : str) ch += 48;
	return str;
}