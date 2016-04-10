# AVLTree
AVL Tree c++ implementation

/*-----------*/

Main AVLTree methods are implemented in AVLTree.cpp such as balancePath, deleteNode and some others,
the rest is inherited from BinarySearchTree class.

useAVL.cpp is a source code where AVLTree and BSTTree are used, tested and compared.
When AVL is compared to BST, there's no big differences in search, when elements are inserted in random order.
But, when elements are added linearly, you even aren't able to insert more than 60k(4k in visual c++) elements in BST, because
it causes stack overflow.

###### How to use

compile using gnu gcc

  g++ useAVL.cpp BinarySearchTree.cpp AVLTree.cpp -w -p


###### References:

- Data Abstraction & Problem Solving Frank M.Carrano
- Introduction to Java Programming, Comprehensive Version 9th Edition Y.Daniel Liang

###### Author
- Ismajl Ramadani
