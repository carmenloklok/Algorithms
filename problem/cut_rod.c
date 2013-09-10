int main()
{
	int price[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int rod_length = 10;

	int rod_total[11];
	memset(rod_total, 0, sizeof(rod_total));

	for (int i = 1; i <= rod_length; ++i)
	{
		int max = -99999;
		for (int j = 1; j <= i; ++j)
		{
			if (price[j] + rod_total[i - j] > max)
				max = price[j] + rod_total[i - j];
		}
		rod_total[i] = max;
	}

	for (int i = 0; i < 11; ++i)
		printf("%d\n", rod_total[i]);
}
