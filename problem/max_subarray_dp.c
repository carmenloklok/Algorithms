#define COUNT 17
int main()
{
	int data[] = { -999999, 13, -3, -25, 20, -3, -16,
		       -23, 18, 20, -7, 12, -5, -22,
		       15, -4, 7 };

	int result[COUNT];
	memset(result, 0, COUNT);
	for (int i = 1; i < COUNT; ++i)
	{
		int max = result[i - 1];
		for (int j = 1; j <= i; ++j)
		{
			int sum = 0;
			for (int k = j; k <= i; ++k)
				sum += data[k];
			if (sum > max)
				max = sum;
		}
		result[i] = max;
	}

	for (int i = 1; i < COUNT; ++i)
		printf("%d: %d\n", i, result[i]);
}
