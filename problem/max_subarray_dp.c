#define COUNT 16
int main()
{
	int data[] = { 0, 13, -3, -25, 20, -3, -16,
		       -23, 18, 20, -7, 12, -5, -22,
		       15, -4, 7 };

	int result[COUNT];
	memset(result, 0, COUNT);

	int sum = 0;
	int b = 0;
	for (int i = 1; i <= COUNT; i++)
	{
		if (b > 0)
			b += data[i];
		else
			b = data[i];
		if (b > sum)
			sum = b;
		result[i] = sum;
	}

	for (int i = 1; i <= COUNT; ++i)
		printf("%d: %d\n", i, result[i]);
}
