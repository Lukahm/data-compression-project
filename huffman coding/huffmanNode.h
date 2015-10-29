#ifndef huffmanNode_H
#define huffmanNode_H
#include <string>
#include<iostream>


struct huffmanNode{
	char symbol;
	int frequency;
	huffmanNode *left, *right;
	huffmanNode();
	huffmanNode(char, int);	
	~huffmanNode();
	bool isLeaf();
};


#endif