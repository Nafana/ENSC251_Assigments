#include <iostream>
#include "aatrees.h"

/*
    Splits the tree at the given node
        Input: AAnode pointer for the node we should split at.
        Returns: The AANode that was just elevated
*/
struct AANode *splitTree(AANode *treeNode) {
    if (treeNode == nullptr){
        return nullptr;
    } else if (treeNode->rightNode == nullptr || treeNode->rightNode->rightNode == nullptr) {
        return treeNode;
    } else if (treeNode->level == treeNode->rightNode->rightNode->level) {   
        splitCount++; // Comment this line to remove Split Count stats
        AANode* elevatedNode = treeNode->rightNode;
        AANode* swapNode = elevatedNode->leftNode;
        elevatedNode->level += 1;
        elevatedNode->leftNode = treeNode;
        treeNode->rightNode = swapNode;
        return elevatedNode;
    }
    return treeNode;
}

/* Skews the tree at a certain position
    This method is called when we have a single left horizontal link,
    and we need to split the tree.
*/
struct AANode *skewTree(AANode *treeNode) {
    if(treeNode == nullptr){
        return nullptr;
    } else if (treeNode->leftNode == nullptr) {
        return treeNode;
    } else if (treeNode->level == treeNode->leftNode->level) {
        skewCount++; // Comment this line to remove Skew Count stats
        AANode* skewNode = treeNode->leftNode;
        AANode* swapNode = treeNode->leftNode->rightNode;
        treeNode->leftNode = swapNode;
        skewNode->rightNode = treeNode;
        return skewNode;
    }    
    return treeNode;
}

/* Inserts the item into the AA tree
    Always process the skewTree and then a splitTree function
*/
struct AANode *insertItem(AANode *rootNode, int insertValue) {
    AANode* insertNode;
    if (rootNode == nullptr) {
        insertNode = new AANode;
        insertNode->value = insertValue;
        return insertNode;
    } else if (insertValue < rootNode->value) {
        rootNode->leftNode = insertItem(rootNode->leftNode, insertValue);
    } else if (insertValue >= rootNode->value) {
        rootNode->rightNode = insertItem(rootNode->rightNode, insertValue);
    }
    insertNode = rootNode;
    insertNode = skewTree(insertNode);
    insertNode = splitTree(insertNode);
    return insertNode;
}

// Preforms an in order traversal to print all elements in order
void printSortedAATree(AANode *traverseNode) {
    if (traverseNode == nullptr)
        return;
    printSortedAATree(traverseNode->leftNode);
    std::cout << traverseNode->value << " " << std::endl;
    printSortedAATree(traverseNode->rightNode);
}


// Fills the AATree with the specified number of elements
void fillAATree(AANode* headNode, const int treeSize) {
    for(int i =0; i < treeSize; i++) {
        headNode = insertItem(headNode, rand());
    }
}