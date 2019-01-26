//Problem description:
//With human lives at stake, an air traffic controller has to schedule the airplanes that are landing at an airport in order to avoid airplane collision. 
//Each airplane i has a time window [si,ti] during which it can safely land. 
//You must compute the exact time of landing for each airplane that respects these time windows. 
//Furthermore, the airplane landings should be stretched out as much as possible so that the minimum time gap between successive landings is as large as possible.
//For example, if the time window of landing three airplanes are [10:00-11:00], [11:20-11:40], [12:00-12:20], 
//and they land at 10:00, 11:20, 12:20 respectively, then the smallest gap is 60 minutes, which occurs between the last two airplanes.
//Given 5 time windows, denoted as [s1,t1],[s2,t2],⋯,[s5,t5] satisfying 0<=s1<t1<s2<t2<⋯<s5<t5<=24. 
//You are required to give the exact landing time of each airplane, in which the smallest gap between successive landings is maximized. 

//input:
//10 numbers(type is float32) s1,t1,s2,t2,⋯,s5,t5, satisfying 0<=s1<t1<s2<t2<⋯<s5<t5<=24.

//output:
//5 numbers(type is float32) l1,l2,⋯,l5, with accuracy of two decimal digits.

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#define MAXN 1001
#define MAXM 1001
using namespace std;
// MAXN是变量数的上限，MAXM是约束条件数的上限
const double eps = 1e-9;
int dcmp(double x)
{
    if (x < -eps)
        return -1;
    else if (x > eps)
        return 1;
    else
        return 0;
}
void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
int m, n; // m个变量，n个约束条件
double A[MAXN][MAXM];
int base[MAXN + MAXM], unbase[MAXM + MAXN]; //基本变量与非基本变量
void pivot(int x, int y)                    //转动
{
    swap(base + x, unbase + y);
    double k = A[x][y];
    A[x][y] = 1.0; //前面系数直接变成1.0
    for (int i = 0; i <= m; i++)
        A[x][i] /= k;            //这一行都约掉k
    for (int i = 0; i <= n; i++) //替换
    {
        if (i != x && dcmp(k = A[i][y]) /* */)
        {
            A[i][0] += (i ? -1 : 1) * k * A[x][0];
            A[i][y] = 0;
            for (int j = 1; j <= m; j++)
                A[i][j] -= k * A[x][j];
        }
    }
}
int init_simplex()
{
    for (int i = 1; i <= m; i++)
        unbase[i] = i; //最开始的m个非基本变量
    for (int i = 1; i <= n; i++)
        base[i] = m + i; //额外的n个松弛变量
    for (int x = 0, y = 0;; x = y = 0)
    {
        for (int i = 1; i <= n; i++)
            if (dcmp(A[i][0]) < 0)
                x = i;
        if (!x)
            return 1;
        for (int i = 1; i <= m; i++)
            if (dcmp(A[x][i]) < 0)
                y = i;
        if (!y)
            return 0; //发现存在b(i) < 0而变量前系数 都大于等于0(注意是 全都
                      //大于等于0) 由于变量具有非负约束，此时整个约束系统无解。
        pivot(x, y);
    }
}
int simplex()
{
    if (!init_simplex())
        return 0;
    for (int x = 0, y = 0;; x = y = 0)
    {
        for (int i = 1; i <= m; i++)
            if (dcmp(A[0][i]) > 0) //找到一个目标函数里前面系数为正数的一个变量
            {                      
                y = i;             
                break;             
            }                      
        if (!y)
            return 1; //若找不到说明已经找到最优解，返回
        double inf = 1e15;
        for (int i = 1; i <= n; i++) //找到对y约束最紧的变量
        {
            double t = A[i][0] / A[i][y];
            if (dcmp(A[i][y]) > 0 && (!x || t < inf))
            {
                inf = t;
                x = i;
            }
        }
        if (!x)
            return -1; //无法约束y,此时整个目标函数发散
        pivot(x, y);
    }
}
int main() {
    n = 14;
    m = 6;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++)
            A[i][j] = 0;
    }

    A[0][6] = A[6][1] = A[7][2] = A[8][3] = A[9][4] = A[10][5] = 1;
    A[1][1] = A[2][2] = A[3][3] = A[4][4] = A[5][5] = -1;
    A[11][1] = A[12][2] = A[13][3] = A[14][4] = 1;
    A[11][2] = A[12][3] = A[13][4] = A[14][5] = -1;
    A[11][6] = A[12][6] = A[13][6] = A[14][6] = 1;
    cin >> A[1][0] >> A[6][0] >> A[2][0] >> A[7][0] >> A[3][0] >> A[8][0] >>
        A[4][0] >> A[9][0] >> A[5][0] >> A[10][0];
    for (int i = 1; i <= 5; i++)
        A[i][0] = A[i][0] * (-1);
    simplex();
    for (int i = 1; i <= 4; i++)
        printf("%.2lf ", A[i][0]);
    printf("%.2lf", A[5][0]);
    return 0;
}