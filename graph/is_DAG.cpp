//求有向图是否有环
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

class Easy_Solution {
    //求有向图（邻接矩阵表示）是否有环
    //参考的java代码放在最后
    bool isDAG=true;
    public bool canFinish(int numCourses, vector<vector<int>> prerequisites) {
        vector<vector<bool>> graph(numCourses, vector<bool>(numCourses, false));
        for(auto &prerequisite:prerequisites)graph[prerequisite[0]][prerequisite[1]]=true;
        vector<int> color(numCourses,0);
        for(int i=0;i<numCourses;i++){
            dfs(graph,i,color);
        }
        return isDAG;
    }
    public void dfs(vector<vector<bool>> &graph,int i,vector<int> &color){
        //结点i变为访问过的状态
        color[i] = 1;
        for(int j=0;j<graph.length;j++){
            //如果当前结点有指向的结点
            if(graph[i][j]){   
                //并且已经被访问过
                if(color[j] == 1){
                    isDAG = false;//有环
                    break;
                }else if(color[j] == -1){
                    //当前结点后边的结点都被访问过，直接跳至下一个结点
                    continue;
                }else{
                    dfs(graph,j,color);//否则递归访问
                }
            }
        }
        //遍历过所有相连的结点后，把本节点标记为-1
        color[i] = -1;
    }
}

struct GraphNode {
    int label;
    vector<GraphNode *> neighbors;
    GraphNode(int x) : label(x) {}
};

class Hard_Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>> &prerequisites) {
        vector<GraphNode *> Graph;
        vector<int> visit;
        vector<int> degree;  //顶点的入度
        for (int i = 0; i < numCourses; i++) {
            Graph.push_back(new GraphNode(i));
            visit.push_back(0);
            degree.push_back(0);
        }
        for (int i = 0; i < prerequisites.size(); i++) {
            GraphNode *begin = Graph[prerequisites[i].first];
            GraphNode *end = Graph[prerequisites[i].second];
            begin->neighbors.push_back(end);
            degree[end->label] += 1;
        }
        for (int i = 0; i < numCourses; i++) {
            //printf("Graph: %d degree: %d\n", Graph[i]->label, degree[i]);
            if (visit[Graph[i]->label] == 0 && degree[Graph[i]->label] == 0) {
                BFS_Graph(Graph[i], visit, degree);
            }
        }
        for (int i = 0; i < numCourses; i++) {
            //printf("Graph: %d degree: %d\n", Graph[i]->label, degree[i]);
            if (degree[Graph[i]->label] != 0) {
                return false;
            }
        }
        return true;
    }
private:
    void BFS_Graph(GraphNode *node, vector<int> &visit, vector<int> &degree) {  //从当前顶点宽搜，判断是否存在环；
        queue<GraphNode *> q;
        //printf("Node: %d\n", node->label);
        q.push(node);
        visit[node->label] = 1;
        while (!q.empty()) {
            for (int i = 0; i < q.front()->neighbors.size(); i++) {
                //printf("Graph: %d degree: %d\n", q.front()->neighbors[i]->label, degree[q.front()->neighbors[i]->label]);
                if (degree[q.front()->neighbors[i]->label] == 1) {
                    q.push(q.front()->neighbors[i]);
                }
                visit[q.front()->label] = 1;
                degree[q.front()->neighbors[i]->label] -= 1;
            }
            q.pop();
        }
    }
};

int main() {
    int numCourses = 4;
    //int numCourses = 10;
    vector<pair<int, int>> prerequisites;
    prerequisites.push_back(make_pair(0, 1));
    prerequisites.push_back(make_pair(0, 3));
    prerequisites.push_back(make_pair(1, 2));
    prerequisites.push_back(make_pair(2, 3));
    prerequisites.push_back(make_pair(3, 1));
    //prerequisites.push_back(make_pair(5, 8));
    //prerequisites.push_back(make_pair(3, 5));
    //prerequisites.push_back(make_pair(1, 9));
    //prerequisites.push_back(make_pair(4, 5));
    //prerequisites.push_back(make_pair(0, 2));
    //prerequisites.push_back(make_pair(7, 8));
    //prerequisites.push_back(make_pair(4, 9));
    Solution s;
    printf("%d\n", s.canFinish(numCourses, prerequisites));
    system("pause");
    return 0;
}

// class Solution {
//     boolean isDAG=true;
//     public boolean canFinish(int numCourses, int[][] prerequisites) {
//         boolean[][] graph=new boolean[numCourses][numCourses];
//         for(int[] prerequisite:prerequisites)graph[prerequisite[0]][prerequisite[1]]=true;
//         int[] color=new int[numCourses];
//         for(int i=0;i<numCourses;i++){
//             dfs(graph,i,color);
//         }
//         return isDAG;
//     }
//     public void dfs(boolean[][] graph,int i,int[] color){
//         //结点i变为访问过的状态
//         color[i] = 1;
//         for(int j=0;j<graph.length;j++){
//             //如果当前结点有指向的结点
//             if(graph[i][j]){   
//                 //并且已经被访问过
//                 if(color[j] == 1){
//                     isDAG = false;//有环
//                     break;
//                 }else if(color[j] == -1){
//                     //当前结点后边的结点都被访问过，直接跳至下一个结点
//                     continue;
//                 }else{
//                     dfs(graph,j,color);//否则递归访问
//                 }
//             }
//         }
//         //遍历过所有相连的结点后，把本节点标记为-1
//         color[i] = -1;
//     }
// }