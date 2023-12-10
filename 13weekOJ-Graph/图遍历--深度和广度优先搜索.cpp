#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 进行深度优先搜索
// v是首个节点
void DFS(int v, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<int>& result) {
    visited[v] = true; // 标记当前节点为已访问
    result.push_back(v); // 将当前节点添加到结果列表中, 一见到就可以加入到结果里面了, 这就是深度优先

    // 遍历与当前节点相邻的所有节点, 一路走到底, 在邻接矩阵中, 子节点正是一行中值为1的哪些节点.
    // 这里这样递归, 不需要用到stack, 就可以实现. 因为每次找不到子节点它就退出了, 相当于栈中的出栈过程
    for (int i = 0; i < adjMatrix[v].size(); i++) {
        // 如果存在一条边，并且相邻节点未被访问，则递归调用DFS
        if (adjMatrix[v][i] == 1 && !visited[i]) {
            DFS(i, adjMatrix, visited, result);
        }
    }
}

// 这个BFS没有用到递归.
void BFS(int start, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<int>& result) {
    queue<int> q; // 创建一个队列用于存储待访问的节点
    q.push(start); // 将起始节点加入队列
    visited[start] = true; // 标记起始节点为已访问

    while (!q.empty()) {
        int v = q.front(); // 获取队列前端的节点
        q.pop(); // 将该节点从队列中移除
        result.push_back(v); // 将该节点添加到结果列表中

        // 遍历与节点v相邻的所有节点, 因为v被出队列了, 那么就应该把v的子节点加到队列里面去
        for (int i = 0; i < adjMatrix[v].size(); i++) {
            // 如果存在一条边，并且相邻节点未被访问
            if (adjMatrix[v][i] == 1 && !visited[i]) {
                q.push(i); // 将相邻节点加入队列
                visited[i] = true; // 标记该节点为已访问
            }
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) { // 对于每个测试案例执行循环
        int n; cin >> n;
        // 邻接矩阵
        vector<vector<int>> adjMatrix(n, vector<int>(n));
        // 标记节点是否被访问过
        vector<bool> visited(n, false);
        // 存储DFS的结果
        vector<int> result;

        // 读取邻接矩阵, 葱数组换成vector, 好管理
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> adjMatrix[i][j];
            }
        }

        // 对于每个节点，如果它未被访问，则从该节点开始执行BFS, 为什么要这么做呢, 因为有可能图里有几个连通分量
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                BFS(i, adjMatrix, visited, result);
            }
        }

        // 打印DFS的结果
        for (int v : result) {
            cout << v << " ";
        }
        cout << endl;
    }
    return 0;
}
