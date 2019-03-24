//Problem description:
//Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 
//An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
// You may assume all four edges of the grid are all surrounded by water.

//input:一个矩阵

//output:小岛数量

class DFS_Solution {
public:
    int numIslands(vector<vector<char> > &grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        vector<vector<bool> > visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    numIslandsDFS(grid, visited, i, j);
                    ++res;
                }
            }
        }
        return res;
    }
    void numIslandsDFS(vector<vector<char> > &grid, vector<vector<bool> > &visited, int x, int y) {
        if (x < 0 || x >= grid.size()) return;
        if (y < 0 || y >= grid[0].size()) return;
        if (grid[x][y] != '1' || visited[x][y]) return;
        visited[x][y] = true;
        numIslandsDFS(grid, visited, x - 1, y);
        numIslandsDFS(grid, visited, x + 1, y);
        numIslandsDFS(grid, visited, x, y - 1);
        numIslandsDFS(grid, visited, x, y + 1);
    }
};

class BFS_Solution {
private:
        queue<int> que;
        int count=0;
        int x=0;
        int y=0;
        int xx=0;
        int yy=0;
public:
    int numIslands(vector<vector<char>>& grid) {
        int rows=grid.size();
        int cols=rows>0?grid[0].size():0;
        int dx[]={-1,0,1,0};
        int dy[]={0,1,0,-1};
        if(rows==0||cols==0){
            return 0;
        }
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                //cout<<rows<<cols<<endl;
                //外部两个for循环为从上到下从左到右寻找未访问的陆地，因为访问过的陆地都已经被置零
                if(grid[i][j]=='1'){
                    que.push(i);
                    que.push(j); 
                    grid[i][j]='0';
                    while(!que.empty()){
                        x=que.front();
                        que.pop();
                        y=que.front();
                        que.pop();
                        for(int k=0;k<4;k++){
                            xx=x+dx[k];
                            yy=y+dy[k];
                            if(xx<0||xx>=rows||yy<0||yy>=cols){
                                continue;
                            }
                            if(grid[xx][yy]=='1'){
                                grid[xx][yy]='0';
                                que.push(xx);
                                que.push(yy);
                            }
                        }
                    }
                    count++;
                    //队列为空的次数=岛屿的数量
                }
            }
        }
        return count;
    }
};