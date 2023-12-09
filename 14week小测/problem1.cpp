#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_WEIGHT = 99999;

struct Edge {
    string adjvex;
    int weight;
};

class Graph {
private:
    int n;
    vector<string> nodes;
    vector<vector<int>> adjacencyMatrix;

public:
    Graph() {}

    void InitializeGraph() {
        cin >> n; // 顶点数
        nodes.resize(n);
        adjacencyMatrix.assign(n, vector<int>(n, MAX_WEIGHT));

        for (int i = 0; i < n; i++)
            cin >> nodes[i];

        int nEdges;
        cin >> nEdges; // 边数

        for (int i = 1; i <= nEdges; i++) {
            string ch1, ch2;
            int weight_;
            cin >> ch1 >> ch2 >> weight_;

            int loc1 = find(nodes.begin(), nodes.end(), ch1) - nodes.begin();
            int loc2 = find(nodes.begin(), nodes.end(), ch2) - nodes.begin();

            adjacencyMatrix[loc1][loc2] = adjacencyMatrix[loc2][loc1] = weight_;
        }

        string startNode;
        cin >> startNode; // Prim算法的起点名字
        int startNodePos = find(nodes.begin(), nodes.end(), startNode) - nodes.begin();

        Prim(startNodePos);
        Kruskal();
    }

    void Prim(int start) {
        vector<Edge> closeEdges(n);
        vector<bool> visited(n, false);
        visited[start] = true;
        int totalWeight = 0;

        for (int i = 0; i < n; i++) {
            closeEdges[i].adjvex = nodes[i];
            closeEdges[i].weight = adjacencyMatrix[start][i];
        }

        cout << "Prim:" << endl;
        for (int i = 1; i < n; i++) {
            int minWeight = MAX_WEIGHT;
            int nextNode = -1;

            for (int j = 0; j < n; j++) {
                if (!visited[j] && closeEdges[j].weight < minWeight) {
                    minWeight = closeEdges[j].weight;
                    nextNode = j;
                }
            }

            if (nextNode != -1) {
                visited[nextNode] = true;
                totalWeight += minWeight;
                cout << nodes[start] << " " << closeEdges[nextNode].adjvex << " " << minWeight << endl;

                for (int j = 0; j < n; j++) {
                    if (!visited[j] && adjacencyMatrix[nextNode][j] < closeEdges[j].weight) {
                        closeEdges[j].adjvex = nodes[nextNode];
                        closeEdges[j].weight = adjacencyMatrix[nextNode][j];
                    }
                }
            }
        }

        cout << totalWeight << endl;
    }

    void Kruskal() {
        cout << "Kruskal:" << endl;
        int nEdges = n - 1;
        vector<pair<int, pair<int, int>>> edges;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (adjacencyMatrix[i][j] != MAX_WEIGHT) {
                    edges.push_back({adjacencyMatrix[i][j], {i, j}});
                }
            }
        }

        sort(edges.begin(), edges.end());

        vector<int> unionSet(n);
        for (int i = 0; i < n; i++) {
            unionSet[i] = i;
        }

        for (int i = 0; i < edges.size() && nEdges > 0; i++) {
            int weight = edges[i].first;
            int u = edges[i].second.first;
            int v = edges[i].second.second;

            if (unionSet[u] != unionSet[v]) {
                cout << nodes[u] << " " << nodes[v] << " " << weight << endl;
                nEdges--;

                int oldSet = unionSet[v];
                int newSet = unionSet[u];
                for (int j = 0; j < n; j++) {
                    if (unionSet[j] == oldSet) {
                        unionSet[j] = newSet;
                    }
                }
            }
        }
    }
};

int main() {
    Graph graph;
    graph.InitializeGraph();
    return 0;
}
