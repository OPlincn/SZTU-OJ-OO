#include <iostream>
#include <vector>
using namespace std;

// 弗洛伊德-沃舍尔算法，用于计算有向图的可达闭包矩阵
void floydWarshall(vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size(); // 获取顶点的数量

    // 三层循环遍历所有顶点对
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // 如果顶点i到顶点k有路径，并且顶点k到顶点j有路径
                // 则更新顶点i到顶点j的路径为存在（即设置为1）
                adjMatrix[i][j] = adjMatrix[i][j] || (adjMatrix[i][k] && adjMatrix[k][j]);
            }
        }
    }
}

int main() {
    int n; // 顶点的数量
    cin >> n; // 从标准输入读取顶点的数量
    vector<vector<int>> adjMatrix(n, vector<int>(n)); // 创建邻接矩阵

    // 从标准输入读取邻接矩阵的初始值
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adjMatrix[i][j];
        }
    }

    // 计算可达闭包矩阵
    floydWarshall(adjMatrix);

    // 输出可达闭包矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
