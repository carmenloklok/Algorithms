int is_finished(int vs[], int count)
{
	for (int i = 0; i < count; ++i)
	{
		if (!vs[i])
			return 0;
	}
	return 1;
}

#define VERTEX_COUNT 6
int main()
{
	int edges[VERTEX_COUNT][VERTEX_COUNT] = { 0,2,0,0,4,0,
					          2,0,3,0,8,0,
					          0,3,0,1,0,0,
					          0,0,1,0,5,9,
					          4,8,0,5,0,0,
					          0,0,0,9,0,0 };

	int vertexs[VERTEX_COUNT];
	int tree[VERTEX_COUNT][VERTEX_COUNT];
	memset(vertexs, 0, sizeof(vertexs));
	memset(tree, 0, sizeof(tree));
	vertexs[0] = 1;

	while (!is_finished(vertexs, VERTEX_COUNT))
	{
		int minimum_value = 9999;
		int chosen_i;
		int chosen_j;
		for (int i = 0; i < VERTEX_COUNT; i++)
		{
			for (int j = i + 1; j < VERTEX_COUNT; j++)
			{
				if (edges[i][j] && edges[i][j] < minimum_value && ((vertexs[i] && !vertexs[j]) || (vertexs[j] && !vertexs[i])))
				{
					minimum_value = edges[i][j];
					chosen_i = i;
					chosen_j = j;
				}
			}
		}

		tree[chosen_i][chosen_j] = 1;
		tree[chosen_j][chosen_i] = 1;

		edges[chosen_i][chosen_j] = 0;
		edges[chosen_j][chosen_i] = 0;

		vertexs[chosen_i] = 1;
		vertexs[chosen_j] = 1;
	}

	for (int i = 0; i < VERTEX_COUNT; ++i)
		for (int j = i + 1; j < VERTEX_COUNT; ++j)
			if (tree[i][j])
				printf("%d and %d connected\n", i + 1, j + 1);
}
