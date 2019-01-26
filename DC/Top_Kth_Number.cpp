//Problem description:
//在一个无序数组A中找到第k大的元素
//Find the kth largest element in an unsorted array A .
//Note that it is the kth largest element in the sorted order, not the kth distinct element. 
//The range of length of A is N(1≤N≤5,000,000) and the element (integer) in A is no bigger than 10,000,00000. 

//input:
//Line 1: the length of the unsorted array A and the index k.
//Line 2: the all elements in array A and split by spaces

//output:
//Line 1: A single integer that is the kth largest element in an unsorted array A.

#include <iostream>
#include <vector>
#include <cstdio>
#include<ctime>
#include<cstdlib>
#include <algorithm>
using namespace std;

int selectMedian(vector<int>& array){
	srand((int)time(0));
	int n = array.size();
	int index = rand() % n;
	return array[index];

}

int quickSelect(vector<int>& array, int k){
	int medianNum=selectMedian(array);
	vector<int> left;
	vector<int> right;
	for (auto &num:array){
		if (num < medianNum)left.push_back(num);
		else right.push_back(num);
	}
	if (left.size() == k - 1)return medianNum;
	else if (left.size()>k - 1)return quickSelect(left, k);
	else return quickSelect(right, k - left.size());
}
int main(){
	int n,k;
	scanf("%d %d",&n,&k);
	vector<int> array;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d",&x);	
		array.push_back(x);
	}
	int result = quickSelect(array, n+1-k);
	printf("%d\n",result);
	return 0;
}