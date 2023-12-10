#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii; // first: 距离，second: 结点编号
const int maxn = 110;
int g[maxn][maxn];  // 邻接矩阵
int last[maxn];     // 记录最短路径的前一个结点
int dis[maxn];      // 记录起点到各结点的最短距离
int n;              // 顶点数量
int start;          // 起点

// Dijkstra算法实现
void Dijkstra(int start) {
    priority_queue<pii, vector<pii>, greater<pii> > q;
    fill(dis, dis + n, INT_MAX); //TODO 初始化所有距离为无穷大
    dis[start] = 0;              //TODO 起点到自身的距离为0
    q.push({0, start});          //TODO 起点放入优先队列
    fill(last, last + n, -1);    //TODO 初始化路径记录

    while (!q.empty()) {
        pii now = q.top();
        q.pop();
        int u = now.second;
        if (now.first != dis[u]) continue; // 跳过过期的记录

        for (int v = 0; v < n; v++) {
            if (g[u][v] && dis[u] + g[u][v] < dis[v]) { // 更新最短路径
                dis[v] = dis[u] + g[u][v];
                q.push({dis[v], v});
                last[v] = u; // 记录路径
            }
        }
    }
}

// 输出最短路径
void Output(int start, map<int, string>& mpNode) {
    for (int i = 0; i < n; i++) {
        if (i == start) continue; // 跳过起点
        cout << mpNode[start] << "-" << mpNode[i] << "-";
        if (dis[i] == INT_MAX) {
            cout << "-1"; // 无法到达
        } else {
            cout << dis[i] << "----[";
            vector<int> path;
            for (int cur = i; cur != -1; cur = last[cur]) {
                path.push_back(cur); // 逆序存储路径
            }
            std::reverse(path.begin(), path.end()); // 翻转得到正序路径
            for (size_t j = 0; j < path.size(); j++) {
                cout << mpNode[path[j]] << " ";
            }
            cout << "]";
        }
        cout << endl;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        map<int, string> mpNode;  // 结点编号到名称的映射
        map<string, int> mpId;    // 结点名称到编号的映射
        cin >> n;
        for (int i = 0; i < n; i++) {
            string name;
            cin >> name;
            mpNode[i] = name;
            mpId[name] = i;
        }

        // 读入邻接矩阵
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> g[i][j];

        // 读入起点名称并转换为编号
        string startName;
        cin >> startName;
        start = mpId[startName];

        // 执行Dijkstra算法
        Dijkstra(start);

        // 输出结果
        Output(start, mpNode);
    }
    return 0;
}
