#include <iostream>
#include "heaps.h"

// Fills the heap with random numbers
void fillRandomHeap(int *binaryHeap, const int &heapLength)
{
    for (int i = 0; i < heapLength; i++)
    {
        binaryHeap[i] = rand();
    }
}

// Prints the heap to the screen in an array like format
void printHeap(int *binaryHeap, const int &heapLength)
{
    for (int i = 0; i < heapLength; i++)
    {
        std::cout << binaryHeap[i] << std::endl;
    }
}

// Builds the max heap, assumes unsorted binary tree
void build_max_heap(int *binaryHeap, int &heapLength)
{
    for (int i = (heapLength / 2) - 1; i >= 0; i--)
    {
        sift_heap(binaryHeap, heapLength, i);
    }
}

/*
    Recursive method that checks to make sure the heap maintains its form.
        If the heap is out of order, we heapify it by reccursively iterating through
        lower branches until we are certain we have a correctly structured heap.
*/
void sift_heap(int *binaryHeap, int &heapLength, int nodeIndex)
{
    int leftNodeIndex = (nodeIndex * 2) + 1;
    int rightNodeIndex = (nodeIndex * 2) + 2;

    // Makes sure we aren't at the floor of the heap
    if (leftNodeIndex > heapLength || rightNodeIndex > heapLength)
        return;

    int temp = 0;
    int leftNodeVal = binaryHeap[leftNodeIndex];

    if (rightNodeIndex < heapLength)
    {
        int rightNodeVal = binaryHeap[rightNodeIndex];
        if (rightNodeVal > binaryHeap[nodeIndex] && leftNodeVal > binaryHeap[nodeIndex])
        {
            temp = leftNodeVal >= rightNodeVal ? leftNodeIndex : rightNodeIndex;
            swapItems(binaryHeap, nodeIndex, temp);
            sift_heap(binaryHeap, heapLength, temp);
        }
        else
        {
            if (rightNodeVal > binaryHeap[nodeIndex])
            {
                swapItems(binaryHeap, nodeIndex, rightNodeIndex);
                sift_heap(binaryHeap, heapLength, rightNodeIndex);
            }
            else if (leftNodeVal > binaryHeap[nodeIndex])
            {
                swapItems(binaryHeap, nodeIndex, leftNodeIndex);
                sift_heap(binaryHeap, heapLength, leftNodeIndex);
            }
        }
    }
    // We only have a single node at the left
    else
    {
        if (leftNodeVal > binaryHeap[nodeIndex])
        {
            swapItems(binaryHeap, nodeIndex, leftNodeIndex);
        }
    }
    return;
}

// Swaps two items at given indecies
void swapItems(int *binaryHeap, int firstItem, int secondItem)
{
    int temp = 0;
    temp = binaryHeap[firstItem];
    binaryHeap[firstItem] = binaryHeap[secondItem];
    binaryHeap[secondItem] = temp;
    swapCount++;
}

/* Prints the sorted map by first building a max heap, and then swapping the first
   and last item. Then the last value of our heap is removed (in this case taken out of focus)
   and we sort the remaining items by the same process.
*/
void sortHeap(int *binaryHeap, const int &heapLength)
{
    int heap_focus = heapLength;
    while (heap_focus > 0)
    {
        build_max_heap(binaryHeap, heap_focus);
        heap_focus--;
        swapItems(binaryHeap, 0, heap_focus);
    }
}