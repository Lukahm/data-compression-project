#include "huffmanNode.h"
#include <memory>
using namespace std;

// Node constructor
huffmanNode::huffmanNode(){
	symbol = ' ';
	frequency = 0;
	left = right = nullptr;
}

//alternative constructor
huffmanNode::huffmanNode(char Char, int Frequency){

	symbol = Char;
	frequency = Frequency;
	left = right = nullptr;

}


//Node destructor
huffmanNode::~huffmanNode(){
	if (left != nullptr) delete left;
	if (right != nullptr) delete right;
}

//fuction for judging if reach leaf
bool huffmanNode::isLeaf() 
{
	return !left && !right;
}



