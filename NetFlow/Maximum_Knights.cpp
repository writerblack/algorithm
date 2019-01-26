//Problem description:
//Given a N∗N chessboard. There are M obstacles in the chessboard and the position of i-th obstacle is (Xi,Yi). 
//You are asked to find the maximum number of knights which can be placed in the chessboard at the same time, satisfied that,
//No two knights can attack each other.
//Knights can't be placed in obstacle.
//There can be at most one knight in a grid.
//(A Knight in chess can attack 8 positions, as shown in following figure)

//input:
//Input is given from Standard Input in the following format:
// N M
// X1 Y1

//output:
//Print the maximum number of knights.

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 210;

struct data
{
    int to, next;
} e[maxn * maxn * 4];
int mat[maxn * maxn], n, m, mark[maxn][maxn], tot, head[maxn * maxn], cnt, ans, map[maxn * maxn];
void ins(int u, int v)
{
    cnt++;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
int xx[8] = {-1, -2, -1, -2, 2, 2, 1, 1}, yy[8] = {2, 1, -2, -1, -1, 1, -2, 2};
bool used[maxn * maxn];
bool dfs(int x)
{
    for (int i = head[x]; i; i = e[i].next)
        if (!used[e[i].to])
        {
            used[e[i].to] = 1;
            if (!mat[e[i].to] || dfs(mat[e[i].to]))
            {
                mat[e[i].to] = x;
                return true;
            }
        }
    return false;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mark[i][j] = ++tot;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        mark[x][y] = 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = (i % 2 == 0 ? 2 : 1); j <= n; j += 2)
        {
            if (mark[i][j])
                for (int k = 0; k < 8; k++)
                {
                    int nx = i + xx[k], ny = j + yy[k];
                    if (nx < 1 || nx > n || ny < 1 || ny > n || !mark[nx][ny])
                        continue;
                    ins(mark[i][j], mark[nx][ny]);
                }
        }
    cnt = tot;
    tot = 0;
    for (int i = 1; i <= n; i++)
        for (int j = (i % 2 == 0 ? 2 : 1); j <= n; j += 2)
            if (mark[i][j])
            {
                memset(used, 0, n * n);
                if (dfs(mark[i][j]))
                    ans++;
            }
    printf("%d", cnt - ans - m);
    return 0;
}