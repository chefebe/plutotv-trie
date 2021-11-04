// PlutoTVRadixTrie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// gcc trei.cpp -o trei

#include <stdio.h>
#include <cstring>

const int NUM_DIGITS = 10;

struct node {
	char val[NUM_DIGITS + 1] = "";  // phone number
	node* nodeArray = NULL;         // dynamically allocated array (ie. STL vector)
	int numNodes = 0;               // number of items in array
};

// Dynamically grow or shrink nodeArray
void addToArray(node *parentNode, const char *numStr) {
	node *biggerNodeArray = new node[parentNode->numNodes + 1];  // one more than current
	if (parentNode->numNodes > 0) {
		memcpy(biggerNodeArray, parentNode->nodeArray, sizeof(node) * parentNode->numNodes);
		delete[] parentNode->nodeArray;
	}
	// define new node in array
	strcpy(biggerNodeArray[parentNode->numNodes].val, numStr);
	parentNode->nodeArray = biggerNodeArray;
	parentNode->numNodes += 1;
}

void deleteFromArray(node *parentNode, const char *numStr) {
	node *smallerNodeArray = NULL;
	int newNumNodes = 0;
	if (parentNode->numNodes > 1) {
		smallerNodeArray = new node[parentNode->numNodes - 1];
		for (int i = 0; i < parentNode->numNodes; i++) {
			if (strcmp(parentNode->nodeArray[i].val, numStr) != 0) {
				memcpy(&(smallerNodeArray[newNumNodes++]), &(parentNode->nodeArray[i]), sizeof(node));
			}
		}
	}
	if (parentNode->numNodes > 0) {
		delete[] parentNode->nodeArray;
	}
	parentNode->nodeArray = smallerNodeArray;
	parentNode->numNodes = newNumNodes;
}

bool getNum(const char* numStr) {
	return true;
}

bool setNum(node *currentNode, const char* numStr, bool used) {

	if (!currentNode) {
		printf("currentNode is NULL. Exiting setNum.\n");
		return true;
	}
	bool found = false;

	if (strlen(currentNode->val) == 0) {
		strcpy(currentNode->val, numStr);
		return true;
	}

	// check if numStr matches left side
	if (strncmp(currentNode->val, numStr, strlen(currentNode->val)) == 0) {
		// this node is a parent of numStr
		// check the children
		for (int i = 0; i < currentNode->numNodes; i++) {
			node *childNode = &(currentNode->nodeArray[i]);
			const char* numStrSub = numStr + strlen(currentNode->val);
			if (strcmp(childNode->val, numStrSub) == 0) {
				if (used) {
					return true;
				} else {
					// exist in child. remove child.
					deleteFromArray(currentNode, numStr);
					return true;
				}
			}
			if (setNum(&(currentNode->nodeArray[i]), numStr + strlen(currentNode->val), used)) {
				return true;
			}
		}
		return false;  // failed to add
	}
		else {
			// add number here
	//		currentNode->nodeArray = addToArray(currentNode->nodeArray, numStr);
			return true;
		}
	
	return false;
}

void printNodes(node *pNode, int level=0) {
	printf("%*s%s\n", level, "", pNode->val);
	for (int i = 0; i < pNode->numNodes; i++) {
		printNodes(&(pNode->nodeArray[i]), level + 1);
	}
}

void testDynamicArrays() {
	node pNode;
	addToArray(&pNode, "1111111111");
	printNodes(&pNode);
	addToArray(&pNode, "2222222222");
	printNodes(&pNode);
	addToArray(&pNode, "3333333333");
	printNodes(&pNode);
	addToArray(&pNode, "4444444444");
	printNodes(&pNode);
	deleteFromArray(&pNode, "3333333333");
	printNodes(&pNode);
	addToArray(&pNode, "5555555555");
	printNodes(&pNode);
	deleteFromArray(&pNode, "2222222222");
	printNodes(&pNode);
	deleteFromArray(&pNode, "1111111111");
	printNodes(&pNode);
	deleteFromArray(&pNode, "4444444444");
	printNodes(&pNode);
	deleteFromArray(&pNode, "1234123412");
	printNodes(&pNode);


}

int main()
{
	printf("Go PlutoTV\n");
	
	testDynamicArrays();
	return 0;

	node parentNode;
	//parentNode.nodes = new node[10];

	setNum(&parentNode, "8012235432", true);
	setNum(&parentNode, "1234567890", true);
	setNum(&parentNode, "1234567892", false);

	printNodes(&parentNode);

	if (parentNode.numNodes > 0) {
		delete[] parentNode.nodeArray;
		parentNode.nodeArray = NULL;
	}
	return 0;
}

