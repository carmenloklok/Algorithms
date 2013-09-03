#define NULL 0

typedef struct node
{
	int data;
	struct node *parent;
	struct node *left;
	struct node *right;
} node;

void add_node(node *root, int data)
{
	if (root->data > data)
	{
		if (root->left == NULL)
		{
			node *new_node = malloc(sizeof(node));
			new_node->parent = root;
			new_node->data = data;
			new_node->left = NULL;
			new_node->right = NULL;

			root->left = new_node;
		}
		else
		{
			add_node(root->left, data);
		}
	}
	else
	{
		if (root->right == NULL)
		{
			node *new_node = malloc(sizeof(node));
			new_node->parent = root;
			new_node->data = data;
			new_node->left = NULL;
			new_node->right = NULL;

			root->right = new_node;
		}
		else
		{
			add_node(root->right, data);
		}
	}
}

node *search_node(node *root, int data)
{
	if (!root)
		return NULL;
	if (root->data == data)
		return root;
	else if (root->data > data)
		return search_node(root->left, data);
	else
		return search_node(root->right, data);
}

int delete_node(node *root, int data)
{
	node *delete = search_node(root, data);
	if (delete != NULL)
	{
		if (delete->left == NULL && delete->right == NULL)
		{
			if (delete == root)
			{
				free(root);
			}
			else if (delete->parent->left == delete)
			{
				delete->parent->left = NULL;
				free(delete);
			}
			else
			{
				delete->parent->right = NULL;
				free(delete);
			}
		}
		else if (delete->left == NULL && delete->right != NULL)
		{
			if (delete == root)
			{
				root->data = delete->right->data;
				root->left = delete->right->left;
				root->right = delete->right->right;
				free(delete->right);
			}
			else if (delete->parent->left == delete)
			{
				delete->parent->left = delete->right;
				free(delete);
			}
			else
			{
				delete->parent->right = delete->right;
				free(delete);
			}
		}
		else if(delete->left != NULL && delete->right == NULL)
		{
			if (delete == root)
			{
				root->data = delete->right->data;
				root->left = delete->right->left;
				root->right = delete->right->right;
				free(delete->left);
			}
			else if (delete->parent->left == delete)
			{
				delete->parent->left = delete->left;
				free(delete);
			}
			else
			{
				delete->parent->right = delete->left;
				free(delete);
			}
		}
		else 
		{
			node *save = delete;
			delete = delete->left;
			if (!delete->right)
			{
				save->data = delete->data;
				save->left = NULL;
			}
			else
			{
				while (delete->right)
					delete = delete->right;
				save->data = delete->data;
				delete->parent->right = NULL;
			}
			free(delete);
		}
		return 1;
	}
	return 0;
}

void in_order_traversal(node *root)
{
	if (!root)
		return;
	if (root->left)
		in_order_traversal(root->left);
	printf("%d-", root->data);
	if (root->right)
		in_order_traversal(root->right);
}

void pre_order_traversal(node *root)
{
	if (!root)
		return;
	printf("%d-", root->data);
	if (root->left)
		pre_order_traversal(root->left);
	if (root->right)
		pre_order_traversal(root->right);
}

void post_order_traversal(node *root)
{
	if (!root)
		return;
	if (root->left)
		post_order_traversal(root->left);
	if (root->right)
		post_order_traversal(root->right);
	printf("%d-", root->data);
}

int main()
{
	int nodes[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
	int count = 9;

	node *root = malloc(sizeof(node));
	root->parent = NULL;
	root->data = 8;
	root->left = NULL;
	root->right = NULL;

	for (int i = 1; i < count; ++i)
		add_node(root, nodes[i]);

	node *result = search_node(root, 8);
	if (result != NULL)
		printf("%d\n", result->data);
	else
		printf("not found\n");

	in_order_traversal(root);
	printf("null\n");
	pre_order_traversal(root);
	printf("null\n");
	post_order_traversal(root);
	printf("null\n");

	delete_node(root, 8);

	result = search_node(root, 8);
	if (result != NULL)
		printf("%d\n", result->data);
	else
		printf("not found\n");
}
