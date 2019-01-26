//Problem description:
//在一个数组里面找到最长递增的子序列，这个序列不要求连续。
//given the numeric sequence, must find the length of its longest increasing subsequence.

//input:
//The first line of input is T, which means there are T groups test cases. 
//For each test case, the first line contains the length of sequence N 
//the second line contains the elements of sequence - N integers in the range from 0 to 1000000 each, separated by spaces(1 <= N <= 100000).

//output:
//Output file must contain T integers - each integer represents he length of the longest increasing subsequence of the given sequence.

#include<cstdio>
#include<algorithm>
#include<stdlib.h>
#include<vector>

using namespace std;

int cmp(const void *a,const void *b){
  return (*(int*)a-*(int*)b);
}

int solve(int *nums,int n){
	if(n==0)return 0;
        vector<int> res;
        res.push_back(nums[0]);
        for(int i=1;i<n;i++){
            auto it=lower_bound(res.begin(),res.end(),nums[i]);
            if(it==res.end()){
                res.push_back(nums[i]);
            }
            else if(*it>nums[i])
            {
                *it = nums[i];
            }   
        }
        return res.size();
}

int main(){
	int T;
	scanf("%d",&T);
	int res[T];
	for (int i = 0; i < T; i++){
		int N;
		scanf("%d", &N);
		int nums[N];
		for (int j = 0; j < N; j++){
			scanf("%d", &nums[j]);
		}
		res[i]=solve(nums,N);
	}
	for(int i=0;i<T;i++){
	  printf("%d",res[i]);
	  printf("\n");
	}
	return 0;
}