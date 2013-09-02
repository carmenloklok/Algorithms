typedef struct heap_node {
	int value;
	struct heap_node *parent;
	struct heap_node *left_node;
	struct heap_node *right_node;
} heap_node;

typedef struct queue_node {
	struct queue_node *prev;
	struct heap_node *item;
} queue_node;

/*
 * queue stuff
 */

void enqueue(queue_node *head, queue_node *tail, heap_node *item)
{
	if (!head->prev) {
		queue_node *first = malloc(sizeof(queue_node));
		first->prev = 0;
		first->item = item;
		head->prev = first;
		tail->prev = first;
		return;
	}
	queue_node *append_node = malloc(sizeof(queue_node));
	append_node->prev = 0;
	append_node->item = item;
	tail->prev->prev = append_node;
	tail->prev = append_node;
}

queue_node *dequeue(queue_node *head, queue_node *tail)
{
	queue_node *next_last = head->prev->prev;
	queue_node *last = head->prev;
	head->prev = next_last;
	if (!head->prev)
		tail->prev = 0;
	return last;
}

int queue_empty(queue_node *head)
{
	if (head->prev)
		return 0;
	return 1;
}

int queue_size(queue_node *head)
{
	int c = 0;
	while (head->prev) {
		c++;
		head = head->prev;
	}
}

/*
 * heap stuff
 */

void swap(heap_node *a, heap_node *b)
{
	printf("exchange %d and %d\n", a->value, b->value);
	int tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

void heap_recursion(heap_node *item)
{
	if (!item->left_node && !item->right_node)
		return;

	int left_value = -99999;
	int right_value = -99999;

	if (item->left_node)
		left_value = item->left_node->value;
	if (item->right_node)
		right_value = item->right_node->value;

	if (item->value < left_value && item->value < right_value) {
		if (left_value >= right_value) {
			swap(item->left_node, item);

			heap_recursion(item->left_node);
		} else {
			swap(item->right_node, item);

			heap_recursion(item->right_node);
		}
	} else if (item->value < left_value && item->value >= right_value) {
		swap(item->left_node, item);

		heap_recursion(item->left_node);
	} else if (item->value < right_value && item->value >= left_value) {
		swap(item->right_node, item);

		heap_recursion(item->right_node);
	}
}

void heap_tail_recursion(heap_node *item)
{
	while (item->parent && item->parent->value < item->value) {
		swap(item, item->parent);
		item = item->parent;
	}
}

void heap_add(heap_node *root, heap_node *new_node)
{
	queue_node *head = malloc(sizeof(queue_node));
	head->item = 0;
	head->prev = 0;
	queue_node *tail = malloc(sizeof(queue_node));
	tail->item = 0;
	tail->prev = 0;

	enqueue(head, tail, root);

	while (!queue_empty(head)) {
		queue_node *out = dequeue(head, tail);
		if (!out->item->left_node) {
			out->item->left_node = new_node;
			new_node->parent = out->item;
			heap_tail_recursion(new_node);
			return;
		} else if (!out->item->right_node) {
			out->item->right_node = new_node;
			new_node->parent = out->item;
			heap_tail_recursion(new_node);
			return;
		}
		enqueue(head, tail, out->item->left_node);
		enqueue(head, tail, out->item->right_node);
		free(out);
	}
}

void heap_init(heap_node *root, int datas[], int count)
{
	root->parent = 0;
	root->left_node = 0;
	root->right_node = 0;
	root->value = datas[0];
	int i;
	for (i = 1; i < count; i++) {
		heap_node *new_node = malloc(sizeof(heap_node));
		new_node->left_node = 0;
		new_node->right_node = 0;
		new_node->parent = 0;
		new_node->value = datas[i];
		heap_add(root, new_node);
	}
}

void heap_print(heap_node *root)
{
	queue_node *head = malloc(sizeof(queue_node));
	head->item = 0;
	head->prev = 0;
	queue_node *tail = malloc(sizeof(queue_node));
	tail->item = 0;
	tail->prev = 0;

	enqueue(head, tail, root);

	while (!queue_empty(head)) {
		queue_node *out = dequeue(head, tail);
		printf("%d ", out->item->value);
		if (out->item->left_node)
			enqueue(head, tail, out->item->left_node);
		if (out->item->right_node)
			enqueue(head, tail, out->item->right_node);
		free(out);
	}
	printf("\n");
}


int heap_pop(heap_node *root)
{
	queue_node *head = malloc(sizeof(queue_node));
	head->prev = 0;
	head->item = 0;
	queue_node *tail = malloc(sizeof(queue_node));
	tail->prev = 0;
	tail->item = 0;

	enqueue(head, tail, root);

	queue_node *out;

	while (!queue_empty(head)) {
		out = dequeue(head, tail);

		if (out->item->left_node)
			enqueue(head, tail, out->item->left_node);

		if (out->item->right_node)
			enqueue(head, tail, out->item->right_node);

		if (!queue_empty(head))
			free(out);
	}

	swap(root, out->item);

	if (out->item->parent) {
		if (out->item->parent->left_node == out->item)
			out->item->parent->left_node = 0;
		else
			out->item->parent->right_node = 0;
	}

	heap_recursion(root);

	int result = out->item->value;

	free(out);

	return result;
}

int main()
{
	int i;
	int datas[] = {6, 5, 3, 1, 8, 7, 2, 4};
	const int count = 8;

	//1. make a max heap
	heap_node *root = malloc(sizeof(heap_node));
	heap_init(root, datas, count);
	heap_print(root);

	//2. pop max in heap one by one, insert to array from tail.
	for (i = count - 1; i >= 0; i--)
		datas[i] = heap_pop(root);

	//3. print the result
	for (i = 0; i < count; i++)
		printf("%d ", datas[i]);
	printf("\n");
}
