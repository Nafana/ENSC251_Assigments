#include <cstdlib> 
#include <iostream>
#include <ctime>
#include "Lists.h"
#include "ListsExtra.h"

using namespace std;

void list_sort_bubble(ListNode* lst);
void create_list_of_length(ListNode* lst, int length);
void print_list(ListNode* lst);
void delete_dynamic_list(ListNode* lst);

int main() {

    ListNode* myList = new ListNode;
    create_list_of_length(myList, 10);
    print_list(myList);
    clock_t begin = clock();
    list_sort_bubble(myList);
    clock_t end = clock();
    print_list(myList);
    cout << "Finished in " << double(end-begin) / CLOCKS_PER_SEC << " seconds.";
    delete_dynamic_list(myList);

    return 0;
}

// Dynamically allocates a list of length N
void create_list_of_length(ListNode* lst, int length) {
    ListNode* currentNode = lst;
    for(int i = 0; i<length; i++) {
        currentNode->nextNode = new ListNode;
        currentNode->nextNode->data = rand();
        currentNode = currentNode->nextNode;
    }
}

// Frees memory from a dynamic list
void delete_dynamic_list(ListNode* lst) {
    ListNode* currentNode;
    int length = list_length(lst);
    for(int i = length - 1; i >= 0; i--) {
        currentNode = lists_get_ptr_to_index(lst, i);
        currentNode->nextNode = nullptr;
        delete currentNode;
    }
}

// Prints the list to console
void print_list(ListNode* lst) {
    ListNode* currentNode = lst;
    cout<< "---LIST---" << endl;
    while(currentNode != nullptr) {
        cout << currentNode->data << ", " << endl;
        currentNode = currentNode->nextNode;
    }
    cout << "----------" << endl << endl;
}

// Sorts the list using the Bubble Sort Algorithm
void list_sort_bubble(ListNode* lst) {
    int temp = 0;
    bool swappedItemsThisRun = true;
    ListNode* currentNode = lst;
    while(swappedItemsThisRun) {
        swappedItemsThisRun = false;
        while(currentNode->nextNode != nullptr) {
            if (currentNode->data > currentNode->nextNode->data) {
                temp = currentNode->data;
                currentNode->data = currentNode->nextNode->data;
                currentNode->nextNode->data = temp;
                swappedItemsThisRun = true;
            }
            currentNode = currentNode->nextNode;
        }
        currentNode = lst;
    }
}