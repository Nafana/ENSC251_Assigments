// ListNode - structure that holds an INT datatype, and a reference to another ListNode.
struct ListNode
{
	int data;
	ListNode* nextNode = NULL;
};

// Adds a Node to the end of the list
struct ListNode* list_cons(int data_item, struct ListNode* tail);
struct ListNode* list_make_cell(int data_item, struct ListNode* tail);

// Gets the first data item in the list
int list_car(struct ListNode* lst);
int list_get_data_item(struct ListNode* lst);

// Gets the next cell in the list
struct ListNode* list_get_next_cell(struct ListNode* lst);
struct ListNode* list_cdr(struct ListNode* lst);

// Gets the last item of a list
int list_get_nth_item(struct ListNode* lst);

// Sets the last item of a list
void list_set_nth_item(struct ListNode* lst, int);

// Gets the length of the list
int list_length(struct ListNode* lst);