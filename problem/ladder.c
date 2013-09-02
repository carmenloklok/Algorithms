int get_ways(int ladder_length, int step)
{
	if (ladder_length == 0)
		return 1;
	int count = 0;
	for (int i = 1; i <= step; ++i)
	{
		if (ladder_length >= i)
			count += get_ways(ladder_length - i, step);
	}
	return count;
}

int main()
{
	int ladder_length = 10;
	int step = 3;/* each step can be 1-3*/
	printf("%d\n", get_ways(ladder_length, step));
}
