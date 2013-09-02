#define NULL 0
#define TRUE 1
#define FALSE 0
#define MAX_INT (~0 ^ (1 << (sizeof(int) * 8 - 1)))
#define VERTEX_COUNT 6

/*
 * Min pripority queue.
 */
typedef struct queue_node
{
	int data;
	int priority;
	struct queue_node *prev;
} queue_node;

int enqueue(queue_node *head, queue_node *tail, int data, int priority)
{
	if (!head || !tail)
		return FALSE;

	if (!head->prev && tail->prev || head->prev && !tail->prev)
		return FALSE;

	queue_node *new_node = malloc(sizeof(queue_node));
	new_node->data = data;
	new_node->priority = priority;
	new_node->prev = NULL;

	if (!head->prev && !tail->prev)
	{
		head->prev = new_node;
		tail->prev = new_node;
	}
	else
	{
		tail->prev->prev = new_node;
		tail->prev = new_node;
	}

	return TRUE;
}

/*
 * Navie extrct min element.
 */
queue_node* dequeue(queue_node *head, queue_node *tail)
{
	if (!head || !tail)
		return FALSE;
	if (!head->prev && !tail->prev || !head->prev && tail->prev || head->prev && !tail->prev)
		return FALSE;

	queue_node *temp = head;
	queue_node *selected = head;
	queue_node *before_selected;

	while (temp->prev != NULL)
	{
		if (temp->prev->priority < selected->priority)
		{
			before_selected = temp;
			selected = temp->prev;
		}
		temp = temp->prev;
	}

	if (selected == tail->prev)
	{
		before_selected->prev = selected->prev;
		tail->prev = before_selected;
	}
	else
	{
		before_selected->prev = selected->prev;
	}

	if (!head->prev)
		tail->prev = NULL;
	return selected;
}

int main()
{
	int edges[VERTEX_COUNT][VERTEX_COUNT] = { 0, 7, 9, 0, 0, 14,
					          7, 0, 10, 15, 0, 0,
					          9, 10, 0, 11, 0, 2,
					          0, 15, 11, 0, 6, 0,
					          0, 0, 0, 6, 0, 9,
					          14, 0, 2, 0, 9, 0 };
	int length[VERTEX_COUNT];
	int outed[VERTEX_COUNT];

	memset(outed, 0, sizeof(outed));
	for (int i = 0; i < VERTEX_COUNT; ++i)
		length[i] = MAX_INT;

	queue_node *head = malloc(sizeof(queue_node));
	head->data = 0;
	head->priority = MAX_INT;
	head->prev = NULL;
	queue_node *tail = malloc(sizeof(queue_node));
	tail->data = 0;
	tail->priority = MAX_INT;
	tail->prev = NULL;

	int start = 0;
	length[start] = 0;
	enqueue(head, tail, start, length[start]);
	
	while (head->prev && tail->prev)
	{
		queue_node *out = dequeue(head, tail);
		for (int i = 0; i < VERTEX_COUNT; ++i)
		{
			if (edges[out->data][i] && !outed[i])
			{
				if (length[out->data] + edges[out->data][i] < length[i])
				{
					length[i] = length[out->data] + edges[out->data][i];
				}
				enqueue(head, tail, i, length[i]);
			}
		}
		outed[out->data] = TRUE;
		free(out);
	}

	for (int i = 0; i < VERTEX_COUNT; i++)
		printf("%d -> %d : length %d\n", start + 1, i + 1, length[i]);
}
