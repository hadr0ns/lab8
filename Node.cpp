#include "Node.h"

Node::Node() {
	leftChild = NULL;
	rightChild = NULL;
	height = 0;
}
Node::~Node() {}

int Node::getData() const {
	return data;
}

void Node::setData(int value) {
	data = value;
}

void Node::setRightChild(Node* node) {
	rightChild = node;
}

void Node::setLeftChild(Node* node) {
	leftChild = node;
}
void Node::setParent(Node* node) {
	parent = node;
}

Node * Node::getLeftChild() const {
	return leftChild;
}

Node * Node::getRightChild() const {
	return rightChild;
}

Node * Node:: getParent() const {
	return parent;
}

/*
* Returns the height of this node. The height is the number of nodes
* along the longest path from this node to a leaf.  While a conventional
* interface only gives information on the functionality of a class and does
* not comment on how a class should be implemented, this function has been
* provided to point you in the right direction for your solution.  For an
* example on height, see page 448 of the text book.
*
* @return the height of this tree with this node as the local root.
*/
int Node::getHeight() {
	return height;
}

void Node::setHeight(int heightVal) {
	height = heightVal;
}


bool Node::hasChild() {
	if (hasLeftChild() || hasRightChild()) {
		return true;
	} else {
		return false;
	}
}

bool Node::hasLeftChild() {
	if (leftChild != NULL) {
		return true;
	} else {
		return false;
	}
}

bool Node::hasRightChild() {
	if (rightChild != NULL) {
		return true;
	} else  {
		return false;
	}
}

bool Node:: hasLandRChildren() {
	if (hasLeftChild() && hasRightChild()) {
		return true;
	} else {
		return false;
	}
}
