//for rand
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "AVLTree.h"
using namespace std;

//callback function
void printNodeItem(int &item)
{
	cout << item << " ";
}

//global var 
clock_t totalAVL;
clock_t totalBST;

void compare(BinarySearchTree sampleBST, AVLTree sampleAVL, int itemToSearch)
{
	/*new time*/
	clock_t t;

	/*start time for BST search */
	t = clock();

	std::cout << "Calculating...\n";
	sampleBST.getEntry(itemToSearch);
	
	/*end time for BST search  */
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to find %d .\n", t, ((float)t) / CLOCKS_PER_SEC, itemToSearch);
	totalAVL += t;
	
	/*reset time for AVL search */
	t = clock();
	
	std::cout << "Calculating...\n";
	sampleAVL.getEntry(itemToSearch);
	
	/*end time for AVL search  */
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to find %d.\n", t, ((float)t) / CLOCKS_PER_SEC, itemToSearch);
	totalBST += t;
}

int main()
{
	AVLTree sampleAVL;
	BinarySearchTree sampleBST;
	
	sampleAVL.inorderTraverse(printNodeItem);
	
	int iter = 0;
	//max number that BST can handle when inserting linearly is 4000 ~ 60000
	const int end = 1000000;
	int randomNumber = 0;
	//assert(iter < end);
	
	vector<int> randomElements;

	for (iter; iter < end; iter++)
	{
		/*generate random number and add to AVLTree and BSTTree*/
		//randomNumber = rand() % end +1;
		randomNumber = iter;
		sampleAVL.add(randomNumber);
		sampleBST.add(randomNumber);
		randomElements.push_back(randomNumber);
		
	}
	cout << "end" << endl;
	//compare
	ompare(sampleBST, sampleAVL, randomElements.at(randomElements.size()-1));


}