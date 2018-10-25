// External variables for statistics
extern int swapCount;

// Builds the max heap, assumes unsorted binary tree
void build_max_heap(int *binaryHeap, int &heapLength);

/*
    Recursive method that checks to make sure the heap maintains its form.
        If the heap is out of order, we heapify it by reccursively iterating through
        lower branches until we are certain we have a correctly structured heap.
*/
void sift_heap(int *binaryHeap, int &heapLength, int nodeIndex);

// Swaps two items at given indecies
void swapItems(int *binaryHeap, int firstItem, int secondItem);

// Prints the heap to the screen in an array like format
void printHeap(int *binaryHeap, const int &heapLength);

/* Prints the sorted map by first building a max heap, and then swapping the first
   and last item. Then the last value of our heap is removed (in this case taken out of focus)
   and we sort the remaining items by the same process.
*/
void sortHeap(int *binaryHeap, const int &heapLength);

// Fills the heap with random numbers
void fillRandomHeap(int *binaryHeap, const int &heapLength);