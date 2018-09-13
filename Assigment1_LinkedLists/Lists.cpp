#include <iostream>

#include "Lists.h"

using namespace std;

// Gets the first data item in the list
int list_car(struct ListNode* lst) {
	if (lst == NULL) { throw std::invalid_argument("Cannot get next ListNode of NULL."); }
	return lst->data;
}

int list_get_data_item(struct ListNode* lst) {
	return list_car(lst);
}

// Gets the last item of a list
int list_get_nth_item(struct ListNode* lst) {
	if (lst == NULL)
		return NULL;
	ListNode* currentNode = lst;
	while (currentNode->nextNode != NULL) {
		currentNode = currentNode->nextNode;
	}
	return currentNode->data;
}

// Sets the Nth item of a list
void list_set_nth_item(struct ListNode* lst, int data_item) {
	if (lst == NULL)
		return;
	ListNode* currentNode = lst;
	while (currentNode->nextNode != NULL) {
		currentNode = currentNode->nextNode;
	}
	currentNode->data = data_item;
}

// Adds a data item to the end of the list
struct ListNode* list_cons(int data_item, struct ListNode* tail) {
	if (tail == NULL)
		return NULL;
	ListNode* addedNode = new ListNode;
	addedNode->data = data_item;
	tail->nextNode = addedNode;
	return addedNode;	
}

struct ListNode* list_make_cell(int data_item, struct ListNode* tail) {
	return list_cons(data_item, tail);
}

// Gets the next cell in the list
struct ListNode* list_cdr(struct ListNode* lst) {
	if (lst == NULL) { throw std::invalid_argument("Cannot get next ListNode of NULL."); }
	return lst->nextNode;
}

struct ListNode* list_get_next_cell(struct ListNode* lst) {
	return list_cdr(lst);
}

// Gets the length of the list
int list_length(struct ListNode* lst) {
	if (lst == NULL)
		return 0;
	int length = 1;
	ListNode* currentNode = lst;
	while(currentNode->nextNode != NULL) {
		currentNode = currentNode->nextNode;
		length++;
	}
	return length;
}