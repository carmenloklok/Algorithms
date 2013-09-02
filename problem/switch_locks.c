/*
 * suppose there 100 locks locked.
 * 1st   time: switch state of locks which's index is times of 1.
 * nth   time: ............................................ of n.
 *  .
 *  .
 *  .
 * 100th time: ............................................ of 100.
 */
int main()
{
	int lock_count = 100;
	int unlocked_count = 0;

	for (int i = 1; i <= lock_count; ++i)
	{
		int temp = 0;
		for (int j = 1; j <= i; ++j)
		{
			if (i % j == 0)
				temp++;
		}

		if (temp % 2 != 0)
			unlocked_count++;
	}

	printf("%d\n", unlocked_count);
}
