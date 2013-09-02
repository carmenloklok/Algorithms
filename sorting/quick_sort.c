#include <stdio.h>

void print(int datas[],int count)
{
	int i;
	for (i = 0; i < count; i++) {
		printf("%d ",datas[i]);
	}
	printf("\n");
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int subAry[], int pivot, int left, int right)
{
	int i;

	int new_pivot_index = left;

	swap(subAry + pivot, subAry + right);

	for (i = left; i < right; i++) {
		if (subAry[i] < subAry[right]) {
			swap(subAry + i, subAry + new_pivot_index);

			new_pivot_index++;
		}
	}

	swap(subAry + right, subAry + new_pivot_index);

	return new_pivot_index;
}

void quick_sort(int subAry[], int left, int right)
{
	if (left >= right)
		return;
	int pivot = left;

	pivot = partition(subAry, pivot, left, right);

	quick_sort(subAry, left, pivot - 1);

	quick_sort(subAry, pivot + 1, right);
}

int main()
{
	int datas[] = {3,6,2,10,56,23,564,3};
	int count = 8;

	print(datas, count);
	quick_sort(datas, 0, 7);
	print(datas, count);
}
