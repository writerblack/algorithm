//Problem description:
//Suppose you will recruit a group of volunteers for a coming event. 
//It is estimated that this event will take N days to complete, and the i(th) day needs at least Ai volunteers. 
//The number of kinds of volunteers is M. 
//The volunteers of i(th) kind can volunteer from the Si day to the Fi day and the recruit fee is Ci. 
//In order to do his job well, you hope to recruit enough volunteers with least money. Please give an optimal plan.

//input:
//The first line presents two integers: N, M. 
//The second line contains N nonnegative integers presenting the numbers of volunteers each day needs. 
//Each of the other lines contain three integers: Si, Fi, Ci
//note: You can recruit each kind of volunteers as many as possible.

//output:
//Just a number meaning the total money of your optimal plan.

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
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

int main()
{
    cin >> n >> m;
    int s, f, c;
    for (int i = 1; i <= n; i++)
    {
        cin >> A[i][0];
        A[i][0] *= (-1);
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> s >> f >> c;
        A[0][i] = c * (-1);

        for (int j = 1; j <= n; j++)
        {
            if (j >= s && j <= f)
                A[j][i] = -1;
            else
                A[j][i] = 0;
        }
    }
    simplex();
    cout << A[0][0] * (-1) << endl;
    return 0;
}