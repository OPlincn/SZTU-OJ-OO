#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//const int MAX_N = 1000;
const int MAX_WEIGHT = 100000;

// 使用Prim算法构建最小生成树
int prim(int n, vector<vector<int>>& graph) {
    vector<bool> inMST(n, false); // 标记每个顶点是否已经加入最小生成树
    vector<int> key(n, MAX_WEIGHT); // 存储每个顶点到最小生成树的最小权重
    key[0] = 0; // 从顶点0开始构建最小生成树

    int totalWeight = 0; // 记录最小生成树的总权重
    for (int count = 0; count < n - 1; count++) {
        int minWeight = MAX_WEIGHT, u;

        // 找到当前未加入最小生成树且key值最小的顶点
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && key[v] < minWeight) {
                minWeight = key[v];
                u = v;
            }
        }

        // 将找到的顶点加入最小生成树
        inMST[u] = true;
        totalWeight += minWeight;
        // 更新与该顶点相邻的顶点的最小权重
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && graph[u][v] < key[v]) { // graph[u][v] &&
                key[v] = graph[u][v];
            }
        }
    }

    return totalWeight;
}

int main() {
    int n, q;
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));

    // 读取村庄间的距离信息
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            cout << graph[i][j] << ' ';
//        }
//        cout << endl;
//    }

    // 读取已经建造的道路信息
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b; // 将村庄编号转换为从0开始的索引
        graph[a][b] = graph[b][a] = 1; // 设置已建造道路的权重为1
    }

    // 调用Prim算法并输出所需建造的道路的最小总长度
    cout << prim(n, graph) << endl;

    return 0;
}
