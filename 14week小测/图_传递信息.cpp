#include <iostream>
#include <vector>
using namespace std;

// 计算从小明到最后一个玩家的消息传递方案数
int messagePassing(int n, vector<pair<int, int>>& relations, int k) {
    // dp[i][j] 表示经过i轮传递后到达玩家j的方案数
    vector<vector<int>> dp(k+1, vector<int>(n, 0));
    /*
     第一维的大小为 k+1，代表传递消息的轮数，从0到k。这里包括第0轮（开始时的状态）和第k轮（最终状态）。
    第二维的大小为 n，代表玩家的数量，从0到n-1。
     dp[i][j] 存储的是经过 i 轮消息传递后，到达玩家 j 的所有可能方案数。
    在初始化时，所有值都设为0，表示没有任何方案。唯一的例外是 dp[0][0]，它被初始化为1，因为在游戏开始时，只有小明（玩家0）有一条消息。
     */
    dp[0][0] = 1; // 初始化，开始时只有小明有消息

    // 遍历每一轮传递, 最少为1轮, 所以k从1开始
    for (int i = 1; i <= k; i++) {
        // 遍历所有的消息传递关系
        for (auto& relation : relations) {
            int src = relation.first;  // 消息的起始玩家
            int dest = relation.second; // 消息的目标玩家
            // 累加所有能传递到dest的方案数
            dp[i][dest] += dp[i-1][src];
        }
    }

    // 返回k轮后到达最后一个玩家的方案数
    return dp[k][n-1];
}

int main() {
    /**
 @brief 图的节点表示玩家：图中的每个节点代表一个玩家。在给定的问题中，玩家被编号为0到n-1，其中小明是编号0。
    图的边表示消息传递路径：图中的边代表玩家之间的消息传递路径。这些边是有向的，表示消息可以从一个玩家传递到另一个玩家，但不一定能反向传递。
    构建邻接列表：给定的relations数组可以被视为图的边的列表。对于每个边对 (a, b)，表示存在一条从玩家a到玩家b的有向边。
    这些边可以被用来构建图的邻接列表，表示每个玩家可以直接传递消息给哪些玩家。应用动态规划解决图遍历问题
 **/
    int t;
    cin >> t; // 读入测试样例数量
    while (t--) {
        int n, len, k;
        cin >> n >> len; // 读入玩家数和关系数
        vector<pair<int, int>> relations;
        for (int i = 0; i < len; i++) {
            int a, b;
            cin >> a >> b; // 读入每个关系
            relations.push_back({a, b});
        }
        cin >> k; // 读入传递轮数
        // 输出每个测试样例的结果
        cout << messagePassing(n, relations, k) << endl;
    }
    return 0;
}

