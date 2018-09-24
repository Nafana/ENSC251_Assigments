#include "Lists.h"
#include "ListsExtra.h"

// Swaps the two items in the list based on index
void lists_swap_items(list* lst, int index_1, int index_2) {
    if (lst == nullptr || index_1 < 0 || index_1 < 0 || index_1 == index_2) return;
    int temp = 0;
    list* firstPtr = lists_get_ptr_to_index(lst, index_1);
    list* secondPrt = lists_get_ptr_to_index(lst, index_2);
    temp = firstPtr->data;
    firstPtr->data = secondPrt->data;
    secondPrt->data = temp;
}

// Gets the pointer to the index of the list
struct list* lists_get_ptr_to_index(list* lst, int index) {
    if (lst == nullptr) { return nullptr; }
    int counter = -1;
    list* currentNode = lst;
    while(currentNode->nextNode != nullptr) {
        counter++;
        if (counter == index) { return currentNode; }
        currentNode = currentNode->nextNode;
    }
    return currentNode;
}