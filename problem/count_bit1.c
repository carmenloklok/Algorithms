/*
 * count the number of bit 1 in a file.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open(argv[1], 0, O_RDONLY);
	int buf = 0;
	int ones = 0;
	while (read(fd, &buf, sizeof(int)) != 0)
	{
		for (int i = 0; i < sizeof(int); ++i)
		{
			int tmp = 1 << i;
			if (tmp == tmp & buf)
				ones++;
		}
		buf = 0;
	}
	printf("bit 1s %d\n", ones);
}
