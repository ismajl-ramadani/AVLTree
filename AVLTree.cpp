#include "AVLTree.h"
#include <assert.h>

//implementation 
std::vector<Node*>* AVLTree::getPath(int item) const
{
	Node *currNode = this->root;
	if(!currNode)
		return NULL;
		
//	#warning do not forget to delete vector to which pathElements points in order to release allocated memory
	std::vector<Node*> *pathElements = new std::vector<Node*>;
	while(currNode->item != item && currNode != NULL)
	{
		//
		pathElements->push_back(currNode);
		
		if(currNode->item > item){
			currNode = currNode->left;
		}else if(currNode->item < item){
			currNode = currNode->right;
		}	
	}
	//push node that item belongs to
	pathElements->push_back(currNode);
	
	return pathElements;
}

Node* AVLTree::createNewNodeWithItem(int item)
{
	Node* newNode = BinarySearchTree::createNewNodeWithItem(item);
	newNode->height = 1;
	return newNode;
}
int max(int first, int second)
{
	return (first > second) ? first : second ;
}
int AVLTree::balanceFactor(Node* subtreePtr)
{
	//bf = h(r) - h(l)
	int balanceF = subtreePtr->right->getHeight() - subtreePtr->left->getHeight();
	if (balanceF < -1){
		return -2;
	}
	else if (balanceF > 1){
		return 2;
	}
	else
		return balanceF;
}
void AVLTree::updateHeight(Node *node)
{
	#ifdef _DEBUG_
	assert(node!=NULL);
	#endif
	node->height = 1 + max(node->left->getHeight(), node->right->getHeight());
}

//rotation
void AVLTree::leftRotate(Node* &nodeA, Node* &parentOfA)
{
	Node* A = nodeA;
	Node* B = nodeA->right;

	if (nodeA == this->root){
		//B is the new root
		this->root = B;
	}
	else{
		if (nodeA == parentOfA->left){
			parentOfA->left = B;
		}
		else {
			parentOfA->right = B;
		}
	}
	A->right = B->left;
	B->left = A;

	updateHeight(A);
	updateHeight(B);
}
void AVLTree::rightRotate(Node* &nodeA, Node* &parentOfA)
{
	Node* A = nodeA;
	Node* B = nodeA->left;
	
	if (nodeA == this->root){
		//B is the new root
		this->root = B;
	}
	else{
		if (nodeA == parentOfA->left){
			parentOfA->left = B;
		}
		else {
			parentOfA->right = B;
		}
	}
	A->left = B->right;
	B->right = A;

	updateHeight(A);
	updateHeight(B);
}
void AVLTree::balancePath(Node* &node)
{
	//1.Get the path from the node that contains e to the root 
	vector<Node*>* pathFromNodeEToRoot = getPath(node->item);
	Node* parentOfA;
	//2. For each node in the path leading to the root
	
	for (int i=pathFromNodeEToRoot->size()-1; i >= 0; i--)
	{
		//3. Update height of each node up to root 
		updateHeight(pathFromNodeEToRoot->at(i));
		//4. Get parentOfA
		if(i >= 1){
			parentOfA = pathFromNodeEToRoot->at(i-1);
		}else{
			//if node is root, parent is NULL
			parentOfA = NULL;
		}
		//4. Calculate balanceFactor of each node, and if AVL property is violated
		//rebalance the tree, else do nothing
		//cout << node->item << " " << endl;
		
		switch(balanceFactor(pathFromNodeEToRoot->at(i))){
			case -2:
				if (balanceFactor(pathFromNodeEToRoot->at(i)->left) > 0){
					//LR imbalance
					this->leftRotate(pathFromNodeEToRoot->at(i)->left, pathFromNodeEToRoot->at(i));
				}
				//
				this->rightRotate(pathFromNodeEToRoot->at(i), parentOfA);
			break;
			case 2:
				if (balanceFactor(pathFromNodeEToRoot->at(i)->right) < 0){
					//RL imbalance
					this->rightRotate(pathFromNodeEToRoot->at(i)->right, pathFromNodeEToRoot->at(i));
				}
				this->leftRotate(pathFromNodeEToRoot->at(i), parentOfA);
			break;
		}
	}
}
bool AVLTree::add(const ItemType& newData)
{
	//1. Create new node and return to newNode 
	Node *newNode = NULL;
	try{
		newNode = AVLTree::createNewNodeWithItem(newData);
	}
	catch (bad_alloc e){
		//cout << e.what();
	}
	//2. Call inorderInsert method and pass root of the tree along with new node 
	insertInOrder(root, newNode);
	
	//3. Restore AVL property if is violated 
	balancePath(newNode);

	numberOfNodes++;
	return false;
}
bool AVLTree::remove(const ItemType& data)
{
	//BinarySearchTree::remove(data);
	if(root == NULL)
		return false;// Element is not in the tree

	// Locate the node to be deleted and also locate its parent node
	Node* currNode = root;
	Node* parentNode = NULL;
	
	while(currNode != NULL){
		
		if(data > currNode->item){
			parentNode = currNode;
			currNode= currNode->right;
		}else if (data < currNode->item){
			parentNode = currNode;
			currNode = currNode->left;
		}else{
			break; //Element is in the tree pointed by currNode
		}
	}
	
	if(currNode == NULL)
		return false;//element is not founded
		
	// Case 1: current has no left children
	if(currNode->left == NULL){
		// Connect the parent with the right child of the current node
		if(parentNode == NULL)
			root = currNode->right;
		else {
			if(data < parentNode->item )
				parentNode->left = currNode->right;
			else
				parentNode->right = currNode->right;

			balancePath(parentNode);	
		}
	}
	else 
	{
		// Case 2: The current node has a left child
		// Locate the rightmost node in the left subtree of
		// the current node and also its parent
		Node *parentOfRightMost = currNode;
		Node *rightMost = currNode->left;
		
		while(rightMost != NULL){
			parentOfRightMost = rightMost;
			rightMost = rightMost->right;
		}
		
		currNode->item = rightMost->item;
		
		//delete rightMost
		if(parentOfRightMost->right == rightMost)
			parentOfRightMost->right = rightMost->left;
		else
			// Special case: parentOfRightMost is current
			parentOfRightMost->left = rightMost->left; 

		// Balance the tree if necessary
		balancePath(parentOfRightMost); 
	}
	return true;	
}