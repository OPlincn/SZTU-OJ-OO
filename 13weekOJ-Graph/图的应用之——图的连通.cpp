#include <iostream>
using namespace std;

// DFS函数，用于进行深度优先搜索
void DFS(int v, int n, bool adjMatrix[][100], bool visited[]) {
    visited[v] = true; // 标记当前节点为已访问

    // 遍历与当前节点相邻的所有节点
    for (int i = 0; i < n; i++) {
        // 如果存在一条边，并且相邻节点未被访问，则递归调用DFS
        if (adjMatrix[v][i] && !visited[i]) {
            DFS(i, n, adjMatrix, visited);
        }
    }
}

// 函数用于检查图是否连通
bool isConnected(int n, bool adjMatrix[][100]) {
    for (int start = 0; start < n; start++) {
        bool visited[100] = {false}; // 对于每个顶点，创建一个新的访问记录数组

        // 从当前顶点开始DFS
        DFS(start, n, adjMatrix, visited);

        // 检查是否所有顶点都被访问过
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                return false; // 如果有未访问的顶点，返回false
            }
        }
    }
    return true; // 如果从每个顶点出发都能访问到所有其他顶点，返回true
}

int main() {
    int k, n;
    cin >> k; // 读取测试案例的数量
    while (k--) {
        cin >> n; // 读取每个测试案例中的节点数量
        bool adjMatrix[100][100]; // 创建邻接矩阵

        // 读取邻接矩阵
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> adjMatrix[i][j];
            }
        }

        // 检查图是否连通
        if (isConnected(n, adjMatrix)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
