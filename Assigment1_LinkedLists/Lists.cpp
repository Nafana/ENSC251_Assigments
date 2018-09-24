#include <iostream>

#include "Lists.h"

using namespace std;

// Gets the first data item in the list
int list_car(struct list* lst) {
	if (lst == nullptr) { throw std::invalid_argument("Cannot get next list of NULL."); }
	return lst->data;
}

int list_get_data_item(struct list* lst) {
	return list_car(lst);
}

// Gets the item at the index
int list_get_nth_item(struct list* lst, int index) {
	if (lst == nullptr || index < 0) { return lst->data; }
	int counter = -1;	
	list* currentNode = lst;
	while (currentNode != nullptr) {
		counter++;
		if (counter == index) {return currentNode->data; }
		currentNode = currentNode->nextNode;
	}
	return currentNode->data;
}

// Sets the item at the index
void list_set_nth_item(struct list* lst, int index, int new_value) {
	if (lst == nullptr || index < 0)
		return;
	list* currentNode = lst;
	int counter = 0;
	while (currentNode != nullptr) {
		if (counter == index) {currentNode->data = new_value; return; }
		currentNode = currentNode->nextNode;
		counter++;
	}
}

// Adds a data item to the end of the list
struct list* list_cons(int data_item, struct list* tail) {
	if (tail == nullptr)
		return NULL;
	list* addedNode = new list;
	addedNode->data = data_item;
	tail->nextNode = addedNode;
	return addedNode;	
}

struct list* list_make_cell(int data_item, struct list* tail) {
	return list_cons(data_item, tail);
}

// Gets the next cell in the list
struct list* list_cdr(struct list* lst) {
	if (lst == nullptr) { throw std::invalid_argument("Cannot get next list of NULL."); }
	return lst->nextNode;
}

struct list* list_get_next_cell(struct list* lst) {
	return list_cdr(lst);
}

// Gets the length of the list
int list_length(struct list* lst) {
	if (lst == nullptr)
		return 0;
	int length = 1;
	list* currentNode = lst;
	while(currentNode->nextNode != nullptr) {
		currentNode = currentNode->nextNode;
		length++;
	}
	return length;
}