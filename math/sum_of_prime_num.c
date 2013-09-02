#include <time.h>
#include <math.h>

int is_prime(long long test){
	int i = 2;
	long long cut = sqrt(test);
	int is = 0;
	for(; i < cut ; i++)
	{
		if(test % i == 0)
		{
			is = -1;
			break;
		}
	}
	return is;
}

int main(int argc , char * argv){
	int num = 216309699;
	long long sum = 2;
	long long i = 3;
	clock_t before = clock();
	for(;i <= num ; i++)
	{
		printf("counting%lld\n" , i);
		if(is_prime(i) == 0)
		{
			sum += i;
		}
	}
	printf("used time:%f\n", (double) (clock() - before) / (double) CLOCKS_PER_SEC );
	printf("sum of prime is:%lld\n",sum);
}
