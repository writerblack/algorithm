//Problem description:
//乘船问题，每条船有最大载重，且最多带两个人，给了需要乘船的人的体重，求需要的最小船只数
//Some people want to cross a river by boat. 
//Each person has a weight, and each boat can carry a maximum weight of limit. 
//Each boat carries at most 2 people at the same time, provided the sum of the weight of those people is at most limit. 
//Return the minimum number of boats to carry every given person. 
//Note that it is guaranteed each person can be carried by a boat.

//input:
//The input will be 3 lines. 
//The first line is a single integer n (1 <= n <= 50000), which means the number of people. 
//The second line is a single integer l (1 <= l <= 30000), represents the weight limit. 
//And the last line contains n integers p_1, p_2, …, p_n (1 <= p_i <= l), separated by spaces, that represent people’s weights.

//output:
//The output will consist of one line containing one integer, which represents the minimum number of boats.

#include<cstdio>
#include<algorithm>

using namespace std;

int main(){
  int n,limit;
  scanf("%d %d",&n,&limit);
  int d[n];
  for(int i=0;i<n;i++){
    int num;
    scanf("%d",&num);
    d[i]=num;
  }
  sort(d,d+n);
  int left=0,right=n-1;
  int count=0;
  while(right>left){
    if(d[left]+d[right]<=limit){
      left++;
      right--;
      count++;
    }
    else{
      right--;
      count++;
    }
  }
  if(left==right)count++;
  printf("%d",count);
}