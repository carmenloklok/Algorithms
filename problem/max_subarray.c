/*
*Divide and conquer
*
*
*/

int data[] = {
13 , -3 , -25 , 20 , -3 , -16 ,
-23 , 18 , 20 , -7 , 12 , -5 , 
-22 , 15 , -4 , 7
};

int * find_max_subarray_cross(int * d , int l , int h)
{
	int *result;
	result = (int *) malloc(3 * sizeof(int));
	int mid = l + (h - l) / 2;

	int i = l;
	int left_max = -10000;
	for(; i <= mid ; ++i){
		int t = i;
		int sum = 0;
		for(; t <= mid ; ++t){
			sum += d[t];
		}
		if(sum > left_max){
			result[0] = i;
			left_max = sum;
		}
	}

	i = mid + 1;
	int right_max = -10000;
	for(; i <= h ; ++i){
		int t = mid + 1;
		int sum = 0;
		for(; t <= i ; ++t){
			sum += d[t];
		}
		if(sum > right_max){
			result[1] = i;
			right_max = sum;
		}
	}
	
	result[2] = left_max + right_max;
	return result;
}

int * find_max_subarray(int * d , int l , int h)
{
	if(l == h){
		int *r = (int *) malloc(3 * sizeof(int));
		r[0] = l;
		r[1] = h;
		r[2] = d[l];
		return r;// base case, bottom
	}else{
		int mid = l + (h - l) / 2;
		int * left = find_max_subarray(d , l , mid);
		int * right = find_max_subarray(d , mid + 1 , h);
		int * cross = find_max_subarray_cross(d , l , h);
		if(left[2] >= right[2] && left[2] >=cross[2]){
			free(right);
			free(cross);
			return left;
		}else if (right[2] >= left[2] && right[2] >= cross[2]){
			free(left);
			free(cross);
			return right;
		}else {
			free(left);
			free(right);
			return cross;
		}
	}
}

int main()
{
	int * result = find_max_subarray(data , 0 , 15);
	printf("max subarray from %d to %d , total value:%d\n" , result[0] , result[1] , result[2]);
}
