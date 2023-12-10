#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

bool isFind = false;
// 进行深度优先搜索
// v是首个节点
void DFS(int v, vector<vector<double>>& adjMatrix, vector<bool>& visited, vector<bool>& recStack, double result) {
    visited[v] = true; // 标记当前节点为已访问
    recStack[v] = true; //标记当前节点为在递归调用栈中

    // 遍历与当前节点相邻的所有节点, 在邻接矩阵中, 方法就是遍历一行
    for (int i = 0; i < adjMatrix[v].size(); i++) {
        // 如果相邻节点已经在递归调用栈中，那么我们找到了一个环,
        // 因为你想一下, 这个节点在遍历子节点的时候, 既然能找到起点, 那不就是一个环吗?
        if (adjMatrix[v][i] > 0 && recStack[i]) {
//            cout << "Graph contains cycle, and the sum is: " << result*adjMatrix[v][i] << endl;
            if (result*adjMatrix[v][i] > 1.0) isFind = true;
        }

            // 如果存在一条边，并且相邻节点未被访问，则递归调用DFS
        else if (adjMatrix[v][i] > 0 && !visited[i]) {
            DFS(i, adjMatrix, visited, recStack, result*adjMatrix[v][i]);
        }
    }
    // 这上面跑完到这里, 说明下面没有什么子节点没访问过了, 要出栈了, 再找到它那也不是环了
    recStack[v] = false; //移除当前节点出栈
}



void printMatrix(vector<vector<double>>& matrix, int& n) {
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
        int n, much; cin >> n >> much;
        // 邻接矩阵
        vector<vector<double>> adjMatrix(n, vector<double>(n));
        // 标记节点是否被访问过
        vector<bool> visited(n, false);
        // 存储环的的结果
        double result = 1;
        // 储存所有的字母, 并创建字符映射到数字
        map<string, int> myMap;
        for (int i = 0; i < n; ++i) {
            string x; cin >> x;
            myMap[x] = i;
        }
        // 读取邻接矩阵
        while (much--) {
            string x, y;
            double v;
            cin >> x >> v >> y;
            adjMatrix[myMap[x]][myMap[y]] = v;
//            adjMatrix[myMap[y]][myMap[x]] = v;
        }

// 在主函数中初始化另外一个数组用于存储递归调用栈
        vector<bool> recStack(n, false);
// 对于每个节点，如果它未被访问，则从该节点开始执行DFS
        for(int i = 0; i < n; i++) {
            if (!visited[i]) {
                DFS(i, adjMatrix, visited, recStack, result);
            }
        }
        cout << (isFind ? "YES" : "NO" ) << endl;
        isFind = false;

    }
    return 0;
}
