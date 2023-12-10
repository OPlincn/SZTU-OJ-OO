#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// 进行深度优先搜索
// v是首个节点
void DFS(int v, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<int>& result) {
    visited[v] = true; // 标记当前节点为已访问
    result.push_back(v); // 将当前节点添加到结果列表中, 不需要那个出栈步骤了, 递归代替

    // 遍历与当前节点相邻的所有节点, 一路走到好
    for (int i = 0; i < adjMatrix[v].size(); i++) {
        // 如果存在一条边，并且相邻节点未被访问，则递归调用DFS
        if (adjMatrix[v][i] == 1 && !visited[i]) {
            DFS(i, adjMatrix, visited, result);
        }
    }
}

void printMatrix(vector<vector<int>>& matrix, int& n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}



int main() {
    int t;
    cin >> t;
    while (t--) {
        // 多少个节点
        int n; cin >> n;
        // 邻接矩阵
        vector<vector<int>> adjMatrix(n, vector<int>(n));
        // 标记节点是否被访问过
        vector<bool> visited(n, false);
        // 存储DFS的结果
        vector<int> result;
        // 储存所有的字母, 并创建字符映射到数字
        map<string, int> myMap;
        for (int i = 0; i < n; ++i) {
            string x; cin >> x;
            myMap[x] = i;
        }

        int much; cin >> much; // 多少个关系, 读取一下
        // 读取邻接矩阵
        while (much--) {
            string x, y;
            cin >> x >> y;
            adjMatrix[myMap[x]][myMap[y]] = 1;
            adjMatrix[myMap[y]][myMap[x]] = 1;
        }

        // 对于每个节点，如果它未被访问，则从该节点开始执行DFS
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                DFS(i, adjMatrix, visited, result);
                ++count;
            }
        }

       // 打印节点值:
        for (const auto &pair : myMap)
        {
             cout << pair.first << ' ';
        }
        cout << endl;
        printMatrix(adjMatrix, n);
        cout << count << endl;
        if (t) cout << endl;
    }
    return 0;
}
