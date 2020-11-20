#include "AVL.h"

//got file1 working!!! it isn't removing right now...ugggghhhhhh I hate the remove function lol

AVL::AVL() {
	root = NULL;
}
AVL::~AVL() {
	clear();
}

Node * AVL::getRootNode() const {
	return root;
}


/*
* Attempts to add the given int to the AVL tree
* Rebalances the tree if data is successfully added
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool AVL::add(int data) {
	Node *ptr = new Node();
	ptr->setData(data);
	bool isAdded = false;
	if (searchValue(data) != NULL) {
		delete ptr;
		return false; //value is already in tree
	} else if (size == 0) {
		root = ptr;
		root->setParent(NULL);
		size++;
		isAdded = true;
		return isAdded;
	} else {
		isAdded = addToTree(root, ptr);
		if (!isBalanced(ptr)) {
			balanceTree(ptr);
		}
		return isAdded;
	}

	cout << "missing case in add()" << endl;
	exit(0);
	return isAdded;
}

bool AVL::addToTree(Node*& node, Node*& newNode) {
	if (newNode->getData() < node->getData()) {
		//move left
		if (!node->hasLeftChild()){
			node->setLeftChild(newNode);
			newNode->setParent(node);
			size++;
			balanceTree(newNode);
			return true;
		} else {
			Node* leftNode = node->getLeftChild();
			return addToTree(leftNode, newNode);
		}
	} else if (newNode->getData() > node->getData()) {
		//move right
		if (!node->hasRightChild()) {
			node->setRightChild(newNode);
			newNode->setParent(node);
			size++;
			balanceTree(newNode);
			return true;
		} else {
			Node* rightNode = node->getRightChild();
			return addToTree(rightNode, newNode);
		}
	} else {
		cout << "In addToTree, another case should not exist." << endl;
		exit(0);
	}
}

void AVL::balanceTree(Node*& node) {
	//cout << "balancing tree" << endl;
	while (node != root) {
		balanceNode(node);
		node = node->getParent();
	}
	//cout << "balancing the root "<< endl;
	balanceNode(root);
	return;

}

void AVL::balanceNode(Node*& node) {
	//cout << "in BalanceNode" << endl;
	if (!isBalanced(node)) {
		// << "node " << node->getData() << " is not balanced " << endl;
		int balance = getBalance(node);
		//cout << "balance is " << balance << endl;
		if (balance == -2) {
			Node* nodeLeftChild = node->getLeftChild();
			int balanceLeft = getBalance(nodeLeftChild);
			if (balanceLeft < 1) {
				//LL tree, rotate right around node
				rotateRight(node);
			} else if (balanceLeft == 1) {
				//LR tree, rotate left around n-> left and then right around n
				Node* rotateNodeLeftChild = node->getLeftChild();
				rotateLeft(rotateNodeLeftChild);
				rotateRight(node);
			} else {
				//cout<< "balanceLeft = " << balanceLeft << endl;
				exit(0);
			}
		} else if (balance == 2) {
			Node* nodeRightChild = node->getRightChild();
			int balanceRight = getBalance(nodeRightChild);
			if (balanceRight > -1) {
				//RR tree, rotate left around node
				rotateLeft(node);
			} else if (balanceRight == -1) {
				//RL tree, rotate right around n->right, and then left around n
				Node* rotateNodeRightChild = node->getRightChild();
				rotateRight(rotateNodeRightChild);
				rotateLeft(node);
			} else {
				//cout<< "balanceRight = " << balanceRight << endl;
				exit(0);
			}
		} else {
			cout << "missing case for root in balanceTree" << endl;
			exit(0);
		}
	} else {
		return;
	}
}

void AVL::rotateLeft(Node*& node) {
	//cout <<"rotating left" << endl;
	Node* temp = node;
	Node* nodeParent;
	if (node != root) {
		bool right = isRightChild(node);
		nodeParent = node->getParent();
		node = node->getRightChild();
		temp->setRightChild(node->getLeftChild());
		if (node->hasLeftChild()) {
			node->getLeftChild()->setParent(temp);
		}
		node->setLeftChild(temp);
		node->setParent(nodeParent);
		if (right) {
			nodeParent->setRightChild(node);
		} else {
			nodeParent->setLeftChild(node);
		}
		temp->setParent(node);
	} else {
		node = node->getRightChild();
		temp->setRightChild(node->getLeftChild());
		if (node->hasLeftChild()) {
			node->getLeftChild()->setParent(temp);
		}
		node->setLeftChild(temp);
		temp->setParent(node);
		root = node;
	}

}

void AVL::rotateRight(Node*& node) {
	//cout << "rotating right" << endl;
	Node* temp = node;
	Node* nodeParent;
	if (node != root) {
		bool right = (isRightChild(node));
		nodeParent = node->getParent();
		node = node->getLeftChild();
		temp->setLeftChild(node->getRightChild());
		if (node->hasRightChild()) {
			node->getRightChild()->setParent(temp);
		}
		node->setRightChild(temp);
		temp->setParent(node);
		if (right) {
			nodeParent->setRightChild(node);
		} else {
			nodeParent->setLeftChild(node);
		}
		node->setParent(nodeParent);
	} else {
		node = node->getLeftChild();
		temp->setLeftChild(node->getRightChild());
		if (node->hasRightChild()) {
			node->getRightChild()->setParent(temp);
		}
		node->setRightChild(temp);
		temp->setParent(node);
		root = node;
	}

}
/*
* Attempts to remove the given int from the AVL tree
* Rebalances the tree if data is successfully removed
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool AVL::remove(int data) {
	//MAKE SURE TO SET PARENTS HERE OR THE PROGRAM WILL BREAK
	//anytime a child is set, the reciprocal parent needs to be set. check for this later;
	Node* removeNode = searchValue(data);
	if (removeNode == NULL) {
		return false;
	}
	Node* removeNodeParent = removeNode->getParent();
	Node* removeNodeLeftChild = removeNode->getLeftChild();
	Node* removeNodeRightChild = removeNode->getRightChild();
	if (removeNode == root){
		if (size == 1) {
			//root is only element
			root = NULL;
			delete removeNode;
			size--;
			return true;
		} else if (root->hasLandRChildren()) {
			//root has left and right children; will need to do a switcharoo.
			Node* newRoot = findNewLocalRoot(removeNodeLeftChild);
			Node* newRootParent;
			newRootParent = newRoot->getParent();
			//cout << "newRootParent = " << newRootParent->getData() << endl;
			//cout << "newRoot->getParent()->data = " << newRoot->getParent()->getData() << endl;
			if (newRootParent == root) {
				//root's left child is the new root
				newRoot->setRightChild(removeNodeRightChild);
				removeNodeRightChild->setParent(newRoot);
				root = newRoot;
				root->setParent(NULL);
				delete removeNode;
				size--;
				balanceTree(root);
				return true;
			} else {
				//the current root/removeNode is not the immediate parent of the new root
				if (!newRoot->hasChild()) {
					//new root does not have a child;
					newRootParent->setRightChild(NULL);

				} else if (newRoot->hasLeftChild()) {
					//cout << "stupid cout message" << endl;
					//new root has a left child, will need to be assigned to new root's parent.
					Node* newRootLeftChild = newRoot->getLeftChild();
					newRootParent->setRightChild(newRootLeftChild);
					newRootLeftChild->setParent(newRootParent);
				} else {
					//cout << "broken code block here" << endl;
					exit(0);
				}
				newRoot->setLeftChild(removeNodeLeftChild);
				//cout << "newRoot leftchild is " << newRoot->getLeftChild()->getData() << endl;
				newRoot->setRightChild(removeNodeRightChild);
				removeNodeLeftChild->setParent(newRoot);
				removeNodeRightChild->setParent(newRoot);
				root = newRoot;
				root->setParent(NULL);
				delete removeNode;
				size--;
				balanceTree(newRootParent);
				return true;
			}
		} else if (root->hasChild()) {
			//has single child
			if (root->hasRightChild()){
				//root has one child and it is right child
				removeNodeRightChild->setParent(NULL);
				root = removeNodeRightChild;

			} else {
				//root has one child and it is left child
				removeNodeLeftChild->setParent(NULL);
				root = removeNodeLeftChild;
			}
			delete removeNode;
			size--;
			balanceTree(root);
			return true;
		} else {
			cout << "Missing root case in remove()" << endl;
			exit(0);
		}
	} else if (!removeNode->hasChild()) {
		//is a leaf case
		if (isRightChild(removeNode)) {
			//is right child case
			removeNodeParent->setRightChild(NULL);
		} else {
			//is left child case
			removeNodeParent->setLeftChild(NULL);
		}
		delete removeNode;
		size--;
		balanceTree(removeNodeParent);
		return true;
	} else if (removeNode->hasLandRChildren()) {
		//generic switcharoo, no worries about root here
		//removeNode = oldLocalRoot
		Node* newLocalRoot = findNewLocalRoot(removeNodeLeftChild);
		Node* NLRParent = newLocalRoot->getParent();
		Node* NLRLeftChild = newLocalRoot->getLeftChild();
		//Node* NLRRightChild = newLocalRoot->getRightChild();

		if (NLRParent == removeNode) {
			//removeNode's left child will be the new local root.
			if (isRightChild(removeNode)) {
				removeNodeParent->setRightChild(newLocalRoot);
			} else {
				removeNodeParent->setLeftChild(newLocalRoot);
			}
			if (removeNode->hasRightChild()) {
				newLocalRoot->setRightChild(removeNodeRightChild);
				removeNodeRightChild->setParent(newLocalRoot);
			}
		} else {
			//there is a gap
			if (isRightChild(removeNode)) {
				removeNodeParent->setRightChild(newLocalRoot);
			} else {
				removeNodeParent->setLeftChild(newLocalRoot);
			}
			if (newLocalRoot->hasLeftChild()) {
				NLRParent->setRightChild(NLRLeftChild);
				NLRLeftChild->setParent(NLRParent);
			} else if (!newLocalRoot->hasChild()) {
				NLRParent->setRightChild(NULL);
			}
			if (removeNode->hasRightChild()) {
				newLocalRoot->setRightChild(removeNodeRightChild);
				removeNodeRightChild->setParent(newLocalRoot);
			}
			newLocalRoot->setLeftChild(removeNodeLeftChild);
			removeNodeLeftChild->setParent(newLocalRoot);

		}

		newLocalRoot->setParent(removeNodeParent);
		//int deleteData = removeNode->getData();
		delete removeNode;
		size--;
		balanceTree(newLocalRoot);
		//cout << "Made it to the end of remove() for " << deleteData << endl;
		return true;

	} else if ((removeNode->hasChild()) && (!removeNode->hasLandRChildren())){
		//only one child cases
		if (removeNode->hasRightChild()) {
			//removeNode has only right child
			if (isRightChild(removeNode)){
				removeNodeParent->setRightChild(removeNodeRightChild);
				removeNodeRightChild->setParent(removeNodeParent);
			} else {
				removeNodeParent->setLeftChild(removeNodeRightChild);
				removeNodeRightChild->setParent(removeNodeParent);
			}
		} else {
			//removeNode has only left child
			if (isRightChild(removeNode)){
				removeNodeParent->setRightChild(removeNodeLeftChild);
				removeNodeLeftChild->setParent(removeNodeParent);
			} else {
				removeNodeParent->setLeftChild(removeNodeLeftChild);
				removeNodeLeftChild->setParent(removeNodeParent);
			}
		}
		delete removeNode;
		size--;
		balanceTree(removeNodeParent);
		return true;
	} else {
		cout << "You are missing a case in remove(). " << endl;
		exit(0);
	}
	cout <<"If you've somehow made it all the way out here in remove(), something is royally forked up. this only exists to get that stupid warning to stop showing." << endl;
	exit(0);
	return false;
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear() {
	while (root!=NULL) {
		bool isRemoved = remove(root->getData());
	}
}

Node*& AVL::searchValue(int value) {
	return findValue(root, value);
}

Node*& AVL::findValue(Node*& node, int value) {
	if (node == NULL) {
		return node;
	} else if (value < node->getData()) {
		Node* leftNode = node->getLeftChild();
		return findValue(leftNode, value);
	} else if (value > node->getData()) {
		Node* rightNode = node->getRightChild();
		return findValue(rightNode, value);
	} else if (value == node->getData()) {
		return node;
	} else {
		cout << "What the hell. you should not be here. your findValue() function is broken." << endl;
		exit(0);
	}
}


bool AVL::isRightChild(Node*& childNode) {
	Node* parentNode = childNode->getParent();
	if (parentNode->getRightChild() == childNode) {
		return true;
	} else {
		return false;
	}
}

int AVL::getSize() {
	return size;
}

int AVL::getHeight(Node*& node) {
	int height = 1;
	height = recursiveGetHeight(node, height);
	node->setHeight(height);
	//cout << "height of " << node->getData() << " is " << height << endl;
	return node->getHeight();
}

int AVL::recursiveGetHeight(Node*& node, int heightVal) {
	if (node->hasChild()) {
		heightVal++;
		if (node->hasLandRChildren()) {
			Node* nodeLeftChild = node->getLeftChild();
			Node* nodeRightChild = node->getRightChild();
			int left = recursiveGetHeight(nodeLeftChild, heightVal);
			int right = recursiveGetHeight(nodeRightChild, heightVal);
			if (right > left) {
				return right;
			} else if (right < left) {
				return left;
			} else if (right == left) {
				return right;
			} else {
				cout << "missing case in recursiveGetHeight" << endl;
				exit(0);
			}
		} else if (node->hasLeftChild()) {
			Node* nodeLeftChild = node->getLeftChild();
			return recursiveGetHeight(nodeLeftChild, heightVal);
		} else if (node->hasRightChild()) {
			Node* nodeRightChild = node->getRightChild();
			return recursiveGetHeight(nodeRightChild, heightVal);
		} else {
			cout << "broken getheight for has child" << endl;
		}

	} else {
		return heightVal;
	}
	cout << "if you made it down here something is broken in recursiveGetHeight" << endl;
	exit(0);
	return -1;
}

int AVL::getBalance(Node*& node) {
	//cout << "in getBalance" << endl;
	int balanceVal = 0;
	Node* nodeLeftChild = node->getLeftChild();
	Node* nodeRightChild = node->getRightChild();
	if (!node->hasChild()) {
		balanceVal = 0;
		return balanceVal;
	} else if (node->hasLandRChildren()) {
		balanceVal = (getHeight(nodeRightChild) - getHeight(nodeLeftChild));
	} else if (node->hasRightChild()) {
		balanceVal = getHeight(nodeRightChild);
	} else if (node->hasLeftChild()) {
		balanceVal = getHeight(nodeLeftChild) * -1;
	}

	//cout << "balance value of " << node->getData() << " is " << balanceVal << endl;;
	return balanceVal;
}

bool AVL::isBalanced(Node*& node) {
	if (fabs(getBalance(node)) > 1) {
		return false;
	} else {
		return true;
	}
}

Node*& AVL::findNewLocalRoot(Node*& localRoot) {
	if (!localRoot->hasRightChild()) {
		return localRoot;
	} else {
		Node* rightChild = localRoot->getRightChild();
		return findNewLocalRoot(rightChild);
	}
}
