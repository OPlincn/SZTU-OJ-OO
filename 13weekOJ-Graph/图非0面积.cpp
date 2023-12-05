#include <iostream>
#include <vector>
using namespace std;

void DFS(vector<vector<int>>& grid, int i, int j, int m, int n) {
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != 0) return;

    grid[i][j] = -1; // 标记已访问的“0”点

    DFS(grid, i + 1, j, m, n); // 向下
    DFS(grid, i - 1, j, m, n); // 向上
    DFS(grid, i, j + 1, m, n); // 向右
    DFS(grid, i, j - 1, m, n); // 向左
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int m, n;
        cin >> m >> n;
        vector<vector<int>> grid(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        // 标记所有边界上的“0”点
        for (int i = 0; i < m; i++) {
            DFS(grid, i, 0, m, n);
            DFS(grid, i, n - 1, m, n);
        }
        for (int j = 0; j < n; j++) {
            DFS(grid, 0, j, m, n);
            DFS(grid, m - 1, j, m, n);
        }

        int area = 0;
        // 计算面积
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    area++;
                }
            }
        }

        cout << area << endl;
    }
    return 0;
}
