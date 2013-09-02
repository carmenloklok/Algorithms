#include <stdio.h>

typedef struct node {
	int data;
	struct node *next_pointer;
} node;

void print_list(node *h)
{
	while ((h = h->next_pointer) != 0)
		printf("%d", h->data);
	printf("\n");
}

void init_list(node *h, int ds[], int c)
{
	h->data = 0;
	h->next_pointer = 0;

	int i;
	for (i = 0; i < c; i++) {
		node *tmp = malloc(sizeof(node));
		h->next_pointer = tmp;
		tmp->data = ds[i];
		tmp->next_pointer = 0;
		h = tmp;
	}
}

int has_loop(node *h)
{
	node * fast = h;
	node * slow = h;
	while (1){
		slow = slow->next_pointer;
		if (slow == 0)
			return 0;
		fast = fast->next_pointer;
		if (fast == 0)
			return 0;
		fast = fast->next_pointer;
		if (fast == 0)
			return 0;
		if (slow == fast)
			return 1;
	}
}

int make_loop(node *h, int f, int t)
{
	int c = 0;
	int i;
	if (h->next_pointer == 0)
		return 0;
	node * from = h->next_pointer;
	node * to = h->next_pointer;
	for (i = 0; i < f; i++) {
		from = from->next_pointer;	
		if (from == 0) 
			return 0;
	}

	for (i = 0; i < t; i++) {
		to = to->next_pointer;	
		if (to == 0) 
			return 0;
	}

	from->next_pointer = to;
	return 1;
}

void reverse22(node *h)
{
	while (h != 0 && h->next_pointer != 0 && h->next_pointer->next_pointer != 0) {
		node *left = h->next_pointer;
		node *right = h->next_pointer->next_pointer;
		left->next_pointer = right->next_pointer;
		right->next_pointer = left;
		h->next_pointer = right;
		h = left;
	}
}

void reverse(node *h)
{
	node *left = 0;
	node *right = h->next_pointer;
	while (right) {
		node *tmp = right->next_pointer;
		right->next_pointer = left;
		left = right;
		right = tmp;
	}
	h->next_pointer = left;
}

int main()
{
	int datas[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	node *head = malloc(sizeof(node));
	init_list(head, datas, 12);
	print_list(head);
	//make_loop(head, 2, 0);
	//print_list(head);
	if (has_loop(head)) {
		printf("has loop\n");
	} else {
		printf("has not loop\n");
	}
	reverse22(head);
	//reverse(head);
	print_list(head);
}
