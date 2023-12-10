#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

// 边的结构定义
struct Edge {
    int src, dest, weight;
    // 边的比较，用于排序
    bool operator<(const Edge& e) const {
        return weight < e.weight;
    }
};

// 并查集类，用于Kruskal算法中检测环
class UnionFind {
    vector<int> parent, rank;
public:
    // 构造函数，初始化并查集
    UnionFind(int size) : parent(size), rank(size, 0) {
        for (int i = 0; i < size; i++) parent[i] = i;
    }

    // 查找根节点（带路径压缩）
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    // 合并两个集合
    void unionSets(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return;
        if (rank[xr] < rank[yr]) swap(xr, yr);
        parent[yr] = xr;
        if (rank[xr] == rank[yr]) rank[xr]++;
    }
};

// Prim算法实现
int primMST(int n, vector<vector<pair<int, int>>>& graph, int start, vector<Edge>& mstEdges) {
    vector<bool> inMST(n, false);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    int totalWeight = 0;

    // 将起点放入优先队列
    inMST[start] = true;
    for (auto& edge : graph[start]) {
        pq.push({edge.second, {start, edge.first}});
    }

    // Prim算法主循环
    while (!pq.empty()) {
        auto edge = pq.top();
        pq.pop();
        int weight = edge.first;
        int u = edge.second.first, v = edge.second.second;

        if (inMST[v]) continue; // 跳过已经在MST中的顶点

        inMST[v] = true; // 标记为已访问
        totalWeight += weight; // 累加权重
        mstEdges.push_back({u, v, weight}); // 加入MST边集

        // 将相邻边加入优先队列
        for (auto& nextEdge : graph[v]) {
            if (!inMST[nextEdge.first]) {
                pq.push({nextEdge.second, {v, nextEdge.first}});
            }
        }
    }

    return totalWeight;
}

// Kruskal算法实现
int kruskalMST(int n, vector<Edge>& edges, vector<Edge>& mstEdges) {
    sort(edges.begin(), edges.end()); // 对边按权重排序
    UnionFind uf(n);
    int totalWeight = 0;

    // 遍历每条边
    for (auto& edge : edges) {
        int u = edge.src, v = edge.dest, weight = edge.weight;
        // 检测是否形成环
        if (uf.find(u) != uf.find(v)) {
            uf.unionSets(u, v); // 合并集合
            totalWeight += weight; // 累加权重
            mstEdges.push_back(edge); // 加入MST边集
        }
    }

    return totalWeight;
}

// 输出最小生成树的边, 不升序
void printMST(const vector<Edge>& mstEdges, map<int, string>& vertexMap) {
    for (auto& edge : mstEdges) {
        cout << vertexMap[edge.src] << " " << vertexMap[edge.dest] << " " << edge.weight << endl;
    }
}

// 输出最小生成树的边（保证升序输出）
void printMST2(const vector<Edge>& mstEdges, map<int, string>& vertexMap) {
    for (auto& edge : mstEdges) {
        int u = edge.src, v = edge.dest;
        if (u > v) swap(u, v); // 确保顶点按升序输出
        cout << vertexMap[u] << " " << vertexMap[v] << " " << edge.weight << endl;
    }
}

int main() {
    int n, m;
    cin >> n;
    map<string, int> vertexMap;
    map<int, string> reverseMap;
    vector<vector<pair<int, int>>> graph(n);
    vector<Edge> edges;

    // 读入顶点
    string vertex;
    for (int i = 0; i < n; i++) {
        cin >> vertex;
        vertexMap[vertex] = i;
        reverseMap[i] = vertex;
    }

    // 读入边信息
    cin >> m;
    string u, v;
    int weight;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> weight;
        graph[vertexMap[u]].push_back({vertexMap[v], weight});
        graph[vertexMap[v]].push_back({vertexMap[u], weight});
        edges.push_back({vertexMap[u], vertexMap[v], weight});
    }

    // 读入起点
    string startVertex;
    cin >> startVertex;

    vector<Edge> primEdges, kruskalEdges;

    // 执行Prim算法并输出结果
    cout << primMST(n, graph, vertexMap[startVertex], primEdges) << endl;
    cout << "prim:" << endl;
    printMST(primEdges, reverseMap);

    // 执行Kruskal算法并输出结果
    cout << "kruskal:" << endl;
    kruskalMST(n, edges, kruskalEdges);
    printMST2(kruskalEdges, reverseMap);

    return 0;
}
