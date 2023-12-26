#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <algorithm>
using namespace std;

struct assistArray {
    vector<int> from;
    vector<int> value;
    assistArray(int n, const int start) {
        from = vector<int>(n, start);
        value = vector<int>(n, INT_MAX);
        value[0] = 0; // start from 0
    }
//    int findMinIndex() {
//        auto Min = std::min_element(value.begin(), value.end());
//        return (Min-value.begin());
//    }
    int minAvailableValue(int& result) {
        /*
         * @brief: 返回最小索引, 更新权重和
         * */
        int min = INT_MAX;
        for (auto x: value) {
            if (x == 0) continue;
            if (x < min) {
                min = x;
            }
        }
//        cout << "min: " << min << endl;
        auto index = std::find(value.begin(), value.end(), min);
        min < 0 ? result += 0 : result += min;
        return (index-value.begin());
    }
};

int primFindSumWeight(vector<vector<int>>& Matrix, const int n, assistArray& assistant) {
    int result(0), count(1), node(0);
    while (count<n) {
//        cout << "now value group: " << endl;
//        for (auto y: assistant.value) {
//            cout << y << ' ';
//        }
//        cout << endl;
        for (int i = 0; i < n; ++i) {
            if (assistant.value[i] > Matrix[node][i] && assistant.value[i]!=0) {
                assistant.value[i] = Matrix[node][i];
                assistant.from[i] = node;
            }
        }
        node = assistant.minAvailableValue(result); // get index
        assistant.value[node] = 0; // visited
//        cout << "node:" << node << endl;
        ++count;
    }
    return result;
}

int main() {
    int n, ed;

    while (cin>>n) {
        vector<vector<int>> Matrix(n, vector<int>(n, INT_MAX));
        assistArray assistant(n, 0);
        // 读取村庄间的距离信息
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> Matrix[i][j];
            }
        }
        // 读取已经建造的道路信息

        cin >> ed;
        for (int i = 0; i < ed; i++) {
            int a, b;
            cin >> a >> b;
            --a; --b; // 将村庄编号转换为从0开始的索引
            Matrix[a][b] = Matrix[b][a] = -1; // 设置已建造道路的权重为1
        }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            cout << Matrix[i][j] << ' ';
//        }
//        cout << endl;
//    }
        cout << primFindSumWeight(Matrix, n, assistant) << endl;
    }

    return 0;
}