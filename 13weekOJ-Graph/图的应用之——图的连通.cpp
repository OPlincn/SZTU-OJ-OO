#include <iostream>
#include <vector>
#include <queue>

using namespace std;



void DFS(int v, vector<vector<int>>& adjMatrix, vector<bool>& visited) {
    visited[v] = true;
    for (int i = 0; i < adjMatrix[v].size(); i++) {
        if (adjMatrix[v][i] == 1 && !visited[i]) {
            DFS(i, adjMatrix, visited);
        }
    }
}

int main() {
    int k;
    cin >> k;
    while (k--) {
        int n;
        cin >> n;
        vector<vector<int>> adjMatrix(n, vector<int>(n));
        vector<bool> visited(n, false);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> adjMatrix[i][j];
            }
        }

        DFS(0, adjMatrix, visited);

        bool isConnected = true;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                isConnected = false;
                break;
            }
        }

        if (isConnected) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}

