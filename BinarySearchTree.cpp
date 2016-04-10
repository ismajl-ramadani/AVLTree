//
#include "BinarySearchTree.h"
#include <iostream>

//Method section for Node class
int Node::getHeight(){

	if(this)
		return this->height;

	return 0;
}

//Method section for BinarySearchTree class
BinarySearchTree::BinarySearchTree() : root(NULL), numberOfNodes(0)
{}
bool BinarySearchTree::isEmpty() const
{
	return this->root == NULL;
}
int BinarySearchTree::getNumberOfNodes() const
{
	return this->numberOfNodes;
}
ItemType BinarySearchTree::getRootData() const
{
	return root->item;
}
void BinarySearchTree::setRootData(const ItemType& newData)
{
	this->root->item = newData;
}

Node* BinarySearchTree::createNewNodeWithItem(int item)
{
	Node* newNode = new Node;
	try {
		newNode = new Node;
	}catch(std::bad_alloc e){
		std::cout << "Bad alloc!";
	}
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->item = item;
	return newNode;
}
bool BinarySearchTree::add(const ItemType& newData)
{
	//add
	Node *newNodePtr = createNewNodeWithItem(newData);
	insertInOrder(root, newNodePtr);
	numberOfNodes ++;
	return 1;

}

bool BinarySearchTree::remove(const ItemType& data)
{
	bool success = false;
	success = findNodeToRemove(root, data);

	return success;
}

bool BinarySearchTree::findNodeToRemove(Node* &subtrePtr, int data)
{
	//if located
	if (subtrePtr == NULL)
	{
		return false;
	}
	if (subtrePtr->item == data)
	{
		//
		std::cout << "node to delte: " << subtrePtr->item << " " << subtrePtr << std::endl;;
		removeNode(subtrePtr);
	}
	else if (data < subtrePtr->item)
	{
		findNodeToRemove(subtrePtr->left, data);
	}
	else
	{
		findNodeToRemove(subtrePtr->right, data);
	}
}

void BinarySearchTree::removeNode(Node* &nodeToRemove)
{
	Node* delPtr;
	/*three cases */
	/*is leaf when two pointers are null*/
	const bool isLeaf = !nodeToRemove->left && !nodeToRemove->right;

	/*node has one children when one of the two pointers is not null and the other is */
	const bool hasOneChild = (nodeToRemove->left && !nodeToRemove->right) ||
		(!nodeToRemove->left && nodeToRemove->right);

	/*node has two children when two of its pointers are not null*/
	const bool hasTwoChildren = nodeToRemove->left && nodeToRemove->right;

	if (isLeaf)
	{	//1. node is leaf
		delete nodeToRemove;
		nodeToRemove = NULL;
	}
	else if(hasOneChild)
	{
		//2. node has only one children
		delPtr = nodeToRemove;
		if (nodeToRemove->left)
		{
			nodeToRemove = nodeToRemove->left;
			delPtr->left = NULL;
		}
		else
		{
			nodeToRemove = nodeToRemove->right;
			delPtr->right = NULL;
		}
		delete delPtr;
		delPtr = NULL;
	}
	else if(hasTwoChildren){
	//3. node have two children
		//locate in order successor
		Node* inOrderSuccessor = locateInOrderSuccessor(nodeToRemove->right);
		nodeToRemove->item = inOrderSuccessor->item;
		removeNode(inOrderSuccessor);
	}

}
Node* BinarySearchTree::locateInOrderSuccessor(Node* node)
{
	if (node->left == NULL)
	{
		return node;
	}
	else
	{
		return locateInOrderSuccessor(node->left);
	}

}

void BinarySearchTree::insertInOrder(Node* &subtrePtr, Node *newNodePtr)
{
	if(subtrePtr == NULL)
	{
		//the insertion point is found
		subtrePtr = newNodePtr;

	}else if(subtrePtr->item < newNodePtr->item)
	{
		//search right sub-tree of subtrePtr
		insertInOrder(subtrePtr->right, newNodePtr);
	}else
	{
		insertInOrder(subtrePtr->left, newNodePtr);
	}
}

ItemType BinarySearchTree::getEntry(const ItemType& anEntry) const
{
	return searchForEntry(anEntry, this->root);
}
ItemType BinarySearchTree::searchForEntry(const ItemType& anEntry, Node* treePtr)const
{
	if (treePtr == NULL)
	{
		return -1;
	}
	if (anEntry == treePtr->item)
	{
		//item found
		return treePtr->item;
	}
	else if (anEntry > treePtr->item)
	{
		searchForEntry(anEntry, treePtr->right);
	}
	else {
		searchForEntry(anEntry, treePtr->left);
	}

}
//traverse section
void BinarySearchTree::preorderTraverse(void visit(ItemType&))const
{
	preTraverse(visit, this->root);
}
void BinarySearchTree::inorderTraverse(void visit(ItemType&)) const
{
	inTraverse(visit, this->root);
}
void BinarySearchTree::postorderTraverse(void visit(ItemType&))const
{
	postTraverse(visit, this->root);
}
void BinarySearchTree::preTraverse(void visit(ItemType&), Node* treePtr) const
{
	if(treePtr != NULL)
	{
		visit(treePtr->item);
		preTraverse(visit, treePtr->left);
		preTraverse(visit, treePtr->right);
	}
}
void BinarySearchTree::inTraverse(void visit(ItemType&), Node* treePtr) const
{
	if(treePtr != NULL)
	{
		inTraverse(visit, treePtr->left);
		visit(treePtr->item);
		inTraverse(visit, treePtr->right);
	}
}
void BinarySearchTree::postTraverse(void visit(ItemType&), Node* treePtr) const
{
	if(treePtr != NULL)
	{
		postTraverse(visit, treePtr->left);
		postTraverse(visit, treePtr->right);
		visit(treePtr->item);
	}
}
