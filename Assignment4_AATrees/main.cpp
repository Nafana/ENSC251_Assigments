#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "aatrees.h"
#include "heaps.h"

// Calculates the difference between two clock times
double calcClockDifference(clock_t initialClock, clock_t finalClock);

// Global Variable declarations for data structure statistics
int splitCount = 0;
int skewCount = 0;
int swapCount = 0;

int main() {

    double insert_time = 0;

    const int AATREE_SIZE = 10000;
    const int HEAP_ELEMENTS = 10000;

    clock_t initTime;
    clock_t finalTime;

    /*
        AATREE SORT AND STATISTICS COUNT BEGINS
    */
    AANode *mainNode = new AANode;

    initTime = clock();
    for(int i =0; i < AATREE_SIZE; i++) {
        mainNode = insertItem(mainNode, rand());
    }
    finalTime = clock();
    insert_time = calcClockDifference(initTime, finalTime);

    printSortedAATree(mainNode);

    std::cout << std::endl << "AATREE - STATS" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "depth: " << mainNode->level << std::endl;
    std::cout << "splits: " << splitCount << std::endl;
    std::cout << "skews: " << skewCount << std::endl;
    std::cout << "insert_time: " << insert_time << " seconds" << std::endl;
    std::cout << "----------------" << std::endl;

    delete mainNode;
    mainNode = nullptr;

    /*
        HEAP SORT AND STATISTICS COUNT BEGINS
    */
    int *binary_heap = new int[HEAP_ELEMENTS];

    initTime = clock();
    fillRandomHeap(binary_heap, HEAP_ELEMENTS);
    sortHeap(binary_heap, HEAP_ELEMENTS);
    finalTime = clock();
    insert_time = calcClockDifference(initTime, finalTime);

    std::cout << std::endl << "BINARY HEAP - STATS" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "swaps: " << swapCount << std::endl;
    std::cout << "insert_time: " << insert_time << std::endl;
    std::cout << "----------------" << std::endl;

    delete[] binary_heap;

    return 0;
}

// Calculates the difference between two clock times
double calcClockDifference(clock_t initialClock, clock_t finalClock) {
    return double(finalClock - initialClock) / CLOCKS_PER_SEC;
}