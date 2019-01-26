//Problem description:
//在一条路上的不同位置有猴子和香蕉，每走一步需要一分钟，给猴子分配香蕉，使得走的时间最短而且不会把一根香蕉分给不同的猴子。
//There are N Monkeys and N bananas are placed in a straight line. 
//Each monkey want to have a banana, if two monkeys want to own the same banana, there will be a fight! 
//A monkey can stay at his position, move one step right from x to x + 1, or move one step left from x to x -1. 
//Any of these moves consumes 1 second. 
//Assign monkeys to banana so that not monkey fight each other and the time when the last monkey gets a banana is minimized.

//input:
//The input contain two arrays of int. The first array is the positions of monkeys. 
//The second array is the positions of bananas.

//output:
//The output is a int, which is the time(in seconds) it takes when all bananas are assigned to monkeys.

#include<cstdio>
#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;

int main(){
  vector<int> monkeys;
  vector<int> banana;
  int n=0,tmp;
  while(~scanf("%d",&tmp)){
    monkeys.push_back(tmp);
    n++;
  }
  while(banana.size()<n/2){
    banana.push_back(*monkeys.rbegin());
    monkeys.pop_back();
  }
  n=n/2;
  sort(monkeys.begin(),monkeys.end());
  sort(banana.begin(),banana.end());
  int count=0;
  for(int i=0;i<n;i++){
    count=max(count,abs(monkeys[i]-banana[i]));
  }
  printf("%d",count);
}