#include <iostream>
using namespace std;

// 执行拓扑排序的函数
void topologicalSort(int n, int adjMatrix[][100]) {
    int inDegree[100] = {0}; // 用来存储每个顶点的入度

    // 计算所有顶点的入度
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // 如果存在从顶点j到顶点i的边，则顶点i的入度加1
            if (adjMatrix[j][i] == 1) {
                inDegree[i]++;
            }
        }
    }

    // 对每个顶点执行操作
    for (int count = 0; count < n; ++count) {
        int v = -1;
        // 寻找入度为0的顶点
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] == 0) {
                v = i; // 找到入度为0的顶点
                break;
            }
        }

        // 如果没有找到入度为0的顶点，表示图中存在环
        if (v == -1) {
            cout << "Cycle detected" << endl;
            return;
        }

        // 输出顶点并将其标记为已访问（将入度设置为-1）
        cout << v << " ";
        inDegree[v] = -1;

        // 更新与顶点v相邻的顶点的入度
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[v][j] == 1) {
                inDegree[j]--;
            }
        }
    }
    cout << endl;
}

int main() {
    int t, n; // t为测试数据个数，n为顶点个数
    cin >> t; // 读取测试数据个数
    while (t--) {
        cin >> n; // 读取顶点个数
        int adjMatrix[100][100]; // 邻接矩阵
        // 读取邻接矩阵
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> adjMatrix[i][j];
            }
        }
        // 对当前的邻接矩阵执行拓扑排序
        topologicalSort(n, adjMatrix);
    }
    return 0;
}
