#include <iostream>
#include <vector>
#include <climits>
#include <stack>

using namespace std;

// 找到未处理的距离最小的顶点
int minDistance(const vector<int> &dist, const vector<bool> &sptSet, int n) {
    int min = INT_MAX, min_index;

    // 遍历所有顶点
    for (int v = 0; v < n; v++)
        // 如果顶点未处理且距离小于当前最小值，则更新最小值和最小值索引
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// 打印从src到i的路径
void printPath(const vector<vector<int>> &path, int src, int i) {
    stack<int> paths;
    int current = i;
    // 从目标顶点开始回溯，直到源顶点
    while (current != -1) {
        paths.push(current);
        current = path[src][current];
    }

    // 打印路径
    cout << "[";
    while (!paths.empty()) {
        cout << paths.top() << " ";
        paths.pop();
    }
    cout << "]";
}

// 打印解决方案
void printSolution(const vector<int> &dist, const vector<vector<int>> &path, int src, int n) {
    // 遍历所有顶点
    for (int i = 0; i < n; i++) {
        // 跳过源顶点
        if (i != src) {
            // 打印从源顶点到i的距离和路径
            cout << src << "-" << i << "-" << dist[i] << "----";
            printPath(path, src, i);
            cout << endl;
        }
    }
}

// 实现迪杰斯特拉算法
void dijkstra(const vector<vector<int>> &graph, int src, int n) {
    vector<int> dist(n, INT_MAX); // 存储从源顶点到每个顶点的最短距离
    vector<bool> sptSet(n, false); // 标记顶点是否已处理
    vector<vector<int>> path(n, vector<int>(n, -1)); // 存储最短路径

    // 源顶点到自身的距离为0
    dist[src] = 0;

    // 遍历所有顶点
    for (int count = 0; count < n - 1; count++) {
        // 找到未处理的最小距离顶点
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = true; // 标记该顶点已处理

        // 更新所有相邻顶点的距离
        for (int v = 0; v < n; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                path[src][v] = u; // 更新路径
            }
    }

    // 打印最短路径和距离
    printSolution(dist, path, src, n);
}

// 主函数
int main() {
    int t, n, v0;
    cin >> t; // 测试数量

    while (t--) {
        cin >> n; // 顶点数量
        vector<vector<int>> graph(n, vector<int>(n)); // 邻接矩阵

        // 读取邻接矩阵
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> graph[i][j];

        cin >> v0; // 源顶点

        // 执行迪杰斯特拉算法
        dijkstra(graph, v0, n);
    }

    return 0;
}
