// list - structure that holds an INT datatype, and a reference to another list.
struct list
{
	int data;
	list* nextNode = nullptr;
};

// Adds a Node to the end of the list
struct list* list_cons(int data_item, struct list* tail);
struct list* list_make_cell(int data_item, struct list* tail);

// Gets the first data item in the list
int list_car(struct list* lst);
int list_get_data_item(struct list* lst);

// Gets the next cell in the list
struct list* list_get_next_cell(struct list* lst);
struct list* list_cdr(struct list* lst);

// Gets the item at an index
int list_get_nth_item(struct list* lst, int index);

// Sets the item at an index
void list_set_nth_item(struct list* lst, int index, int new_value);

// Gets the length of the list
int list_length(struct list* lst);
