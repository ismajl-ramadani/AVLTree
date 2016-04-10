//

#ifndef _BST_
#define _BST_

typedef int ItemType ;

struct Node
{
   ItemType item;        // Data portion
   Node *left;   // Index to left child
   Node *right;  // Index to right child
   int level;
   int height;

   int getHeight();
};
class BinarySearchTree
{

//#warning root node left public!
public:
	Node *root;
//private:
//	#warning use size_t instead
	unsigned int numberOfNodes;
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   //#warning Imeplementoje konstrutkroin default

  BinarySearchTree();
  //virtual ~BinarySearchTree();

   //------------------------------------------------------------
   // Public BinaryTreeInterface Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const;
   int getHeight() const;
   int getNumberOfNodes() const;
   ItemType getRootData() const ;
   void setRootData(const ItemType& newData);
   virtual bool add(const ItemType& newData); // Adds a node
   virtual bool remove(const ItemType& data); // Removes a node
   void clear();
   ItemType getEntry(const ItemType& anEntry) const ;
   bool contains(const ItemType& anEntry) const;

   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------
   void preorderTraverse(void visit(ItemType&)) const;
   void inorderTraverse(void visit(ItemType&)) const;
   void postorderTraverse(void visit(ItemType&)) const;

	//------------------------------------------------------------
	// Protected Utility Methods Section:

   void insertInOrder(Node* &subtrePtr, Node *newNodePtr);
   ItemType searchForEntry(const ItemType& anEntry, Node* treePtr) const;
   bool findNodeToRemove(Node* &subtrePtr, int data);
   void removeNode(Node*&);
   Node* locateInOrderSuccessor(Node* node);
   virtual  Node* createNewNodeWithItem(int item);

	// Recursive helper methods for the public methods.
	void preTraverse(void visit(ItemType&), Node* treePtr)const;
	void inTraverse(void visit(ItemType&), Node* treePtr)const;
	void postTraverse(void visit(ItemType&), Node* treePtr)const;

};
#endif
