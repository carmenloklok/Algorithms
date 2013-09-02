/*
binary_search , must be positive
datas must be sorted
*/
int binary_search(int count , int *datas , int target){
	if(count < 0 || datas == 0){
		return -1;
	}
	int begin = 0 , end = count -1;
	while(1){
		if(end < begin)
			return -1;
		if(begin == end){
			if(datas[begin] == target){
				return begin;
			}else{
				return -1;
			}
		}
		int middle_index = begin + (end - begin) / 2;
		int middle = datas[middle_index];
		if(middle == target){
			return middle_index;
		}else if(target < middle){
			end = middle_index - 1;
		}else{
			begin = middle_index + 1;
		}
	}
	return -1;
}

int main(int count , char *paras){
	int * cases;
	int target;
	int i =0;
	int c;
	printf("input number of test cases:");
	scanf("%d",&c);
	cases = (int *)malloc(c*sizeof(int));
	printf("input your test cases:");
	for(;i<c;i++)
	    scanf("%d",&cases[i]);
	printf("number you want to search:");
	scanf("%d",&target);
	//sort
	//binary_search
	int result = binary_search(c , cases , target);
	printf("result:%d\n",result);
}
