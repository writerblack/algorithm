//Problem description:
//求解网络最大流的Dinic板子
//Given a directed graph with N vertices and M edges. 
//The i-th edge is from vertex Ui to vertex Vi with capacity Ci. 
//Find the maximum flow from source S to sink T.

//input:
//Input is given from Standard Input in the following format:
// N M S T
// U1 V1 C1
// ......
// Un Vn Cn

//output:
//Print maximum flow from source S to sink T.

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <bitset>
using namespace std;
const int Maxn = 10000 + 10;
//const long long INF = 0x7fffffff;
const long long INF = 0x7fffffffffffffff;
struct edge
{
    int from, to;
    long long cap, flow;
};
struct Dinic
{
    int n, m, s, t;
    vector<edge> edges;
    vector<int> f[Maxn];
    bool vis[Maxn];
    int d[Maxn];
    int cur[Maxn];
    void AddEdge(int from, int to, long long cap)
    {
        edges.push_back((edge){from, to, cap, 0});
        edges.push_back((edge){to, from, 0, 0});
        m = edges.size();
        f[from].push_back(m - 2);
        f[to].push_back(m - 1);
    }
    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            for (int i = 0; i < f[x].size(); i++)
            {
                edge &e = edges[f[x][i]];
                //cout<<"to="<<e.to<<"from="<<e.from<<' '<<e.flow<<' '<<e.cap<<' '<<vis[e.to]<<endl;
                if (!vis[e.to] && e.flow < e.cap) //只考虑残留网络中的弧
                {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1; //层次图
                    q.push(e.to);
                }
            }
        }
        return vis[t]; //能否到汇点，不能就结束
    }
    long long Min(long long a, long long b)
    {
        return a > b ? b : a;
    }
    long long DFS(int x, long long a) //x为当前节点，a为当前最小残量
    {
        if (x == t || a == 0)
            return a;
        long long flow = 0, r;
        for (int &i = cur[x]; i < f[x].size(); i++)
        {
            edge &e = edges[f[x][i]];
            if (d[x] + 1 == d[e.to] && (r = DFS(e.to, Min(a, e.cap - e.flow))) > 0)
            {
                e.flow += r;
                edges[f[x][i] ^ 1].flow -= r;
                flow += r; //累加流量
                a -= r;
                if (a == 0)
                    break;
            }
        }
        return flow;
    }
    long long MaxFlow(int s, int t)
    {
        this->s = s;
        this->t = t;
        long long flow = 0;
        while (BFS())
        {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
} G;
int main()
{
    int V, E, S, T;
    int Si, Ei;
    long long Ci;
    scanf("%d", &G.n);
    scanf("%d%d%d", &E, &S, &T);
    while (E--)
    {
        scanf("%d%d%lld", &Si, &Ei, &Ci);
        if (!(Si | Ei | Ci))
            break;
        G.AddEdge(Si, Ei, Ci);
    }
    long long ans = G.MaxFlow(S, T);
    printf("%lld\n", ans);
    return 0;
}