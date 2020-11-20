#pragma once

#include "Node.h"
#include "AVLInterface.h"
#include <cmath>

using namespace std;

class AVL: public AVLInterface {
public:
	AVL();
	~AVL();

	Node * getRootNode() const;

	bool add(int data);

	bool remove(int data);

	void clear();

	Node*& searchValue(int value);

	Node*& findValue(Node*& node, int value);

	bool isRightChild(Node*& childNode);

	int getSize();
	int getHeight(Node*& node);
	int recursiveGetHeight(Node*& node, int heightVal);
	int getBalance(Node*& node);
	bool isBalanced(Node*& node);
	bool addToTree(Node*& node, Node*& newNode);
	void balanceTree(Node*& node);
	void rotateLeft(Node*& node);
	void rotateRight(Node*& node);
	void balanceNode(Node*& node);
	Node*& findNewLocalRoot(Node*& localRoot);

protected:
	Node* root;
	int size;
};
