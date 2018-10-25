#include <stdlib.h>

// External variables for statistics
extern int skewCount;
extern int splitCount;

// AANode struct, has a stored value and a level
struct AANode {
    int value = 0;
    int level = 1;

    AANode *leftNode = nullptr;
    AANode *rightNode = nullptr;
};


/*
    Splits the tree at the given node
        Input: AAnode pointer for the node we should split at.
        Returns: The AANode that was just elevated
*/
struct AANode* splitTree(AANode *treeNode);

/* Skews the tree at a certain position
    This method is called when we have a single left horizontal link,
    and we need to split the tree.
*/
struct AANode* skewTree(AANode *treeNode);

/* Inserts the item into the AA tree
    Always process the skewTree and then a splitTree function
*/
struct AANode* insertItem(AANode *rootNode, int insertValue);

// Preforms an in order traversal to print all elements in order
void printSortedAATree(AANode *traverseNode);

// Fills the AATree with the specified number of elements
void fillAATree(AANode* headNode, const int treeSize);