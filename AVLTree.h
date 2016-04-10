#ifndef AVLTree_H_
#define AVLTree_H_
#include "BinarySearchTree.h" 

#include <vector>
#include <iostream> //for NULL bad_alloc and vector

using std::vector;
using std::bad_alloc;

//AVL of integer objects
class AVLTree : public BinarySearchTree
{

	public:
		bool add(const ItemType& newData);
		bool remove(const ItemType& data); 
	
	private:
		void balancePath(Node* &node);
		
		//rotation methods
		void leftRotate(Node* &nodeA, Node* &parentOfA);
		void rightRotate(Node* &nodeA, Node* &parentOfA);
		
		//helper methods
		void updateHeight(Node *node);
		int balanceFactor(Node* subtreePtr);
		/*Returns a path from the root leading to specified element*/
		public: std::vector<Node*>* getPath(int item) const;
		Node* createNewNodeWithItem(int item);
};

#endif