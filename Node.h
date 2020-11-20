#pragma once
using namespace std;

#include "NodeInterface.h"
#include <iostream>

class Node: public NodeInterface {

public:
	Node();
	~Node();

	int getData() const;

	Node * getLeftChild() const;

	Node * getRightChild() const;

	int getHeight();
	void setData(int value);
	void setRightChild(Node* node);
	void setLeftChild(Node* node);
	void setParent(Node* node);

	Node * getParent() const;

	bool hasChild();
	bool hasLeftChild();
	bool hasRightChild();
	bool hasLandRChildren();
	void setHeight(int heightVal);

protected:
	int data;
	Node* rightChild;
	Node* leftChild;
	Node* parent;
	int height;
};
