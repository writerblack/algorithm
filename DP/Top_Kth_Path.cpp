//Problem description:
//在一个网格里面，从左上走到右下，找到topk条score最大的路径。
//A robot is located at the top-left corner of a m×n grid. 
//The robot can only move either down or right at any point in time. 
//The robot is trying to reach the bottom-right corner of the grid. 
//There is a non-negative integer in each small grid which means the score that the robot get when it passes this grid. 
//Now you need to calculate the top k total scores when the robot reach the destination.
//Note: The top k total scores may contain same total score got from different paths.

//input:
//The first line of input are m and n,which denote the size of the grid. The second line of input is the k.
//The next m lines are the score matrix. (1≤m,n,k≤100,and 0≤score≤100)

//output:
//There is only one line in the Output,which is a descending sequence consist of the top k total scores.

#include <bits/stdc++.h>
using namespace std;
int matrix[105][105],res[2][105][205],assist[105][105];int cmp(int x,int y){
return x>y;}
int main() {    
int m,n,k;
scanf("%d%d%d",&m,&n,&k);
    for(int i=1; i<=m; i++) {
        for(int j=1; j<=n; j++) {
            scanf("%d",&matrix[i][j]);
        }
}
    memset(assist,0,sizeof(assist));
    res[1][1][0]=matrix[1][1];
    assist[1][1]=1;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(i==1&&j==1) continue ;
            if(i!=1){
                for(int x=0;x<assist[i-1][j];x++){
                    res[i&1][j][assist[i][j]++]=matrix[i][j]+res[(i-1)&1][j][x];
                }
            }
            if(j!=1){
                for(int x=0;x<assist[i][j-1];x++){
                    res[i&1][j][assist[i][j]++]=matrix[i][j]+res[i&1][j-1][x];
                }
            }
            sort(res[i&1][j],res[i&1][j]+assist[i][j],cmp);
            assist[i][j]=min(assist[i][j],k);
        }
    }
    printf("%d",res[m&1][n][0]);
    for(int i=1;i<k; i++) {
        printf(" %d",res[m&1][n][i]);
    }
}