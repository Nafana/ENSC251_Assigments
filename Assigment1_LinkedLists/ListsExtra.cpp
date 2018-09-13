#include "Lists.h"
#include "ListsExtra.h"

// Swaps the two items in the list based on index
void lists_swap_items(ListNode* lst, int index_1, int index_2) {
    if (lst == nullptr || index_1 < 0 || index_1 < 0 || index_1 == index_2) return;
    int temp = 0;
    ListNode* firstPtr = lists_get_ptr_to_index(lst, index_1);
    ListNode* secondPrt = lists_get_ptr_to_index(lst, index_2);
    temp = firstPtr->data;
    firstPtr->data = secondPrt->data;
    secondPrt->data = temp;
}

// Gets the pointer to the index of the list
struct ListNode* lists_get_ptr_to_index(ListNode* lst, int index) {
    if (lst == nullptr) { return nullptr; }
    int counter = -1;
    ListNode* currentNode = lst;
    while(currentNode->nextNode != nullptr) {
        counter++;
        if (counter == index) { return currentNode; }
        currentNode = currentNode->nextNode;
    }
    return currentNode;
}