#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <functional>

using namespace std;

const int MaxW = 9999999;  // 定义最大权值为9999999

// 赫夫曼树节点类
class HuffNode {
public:
    int weight;      // 节点权值
    int parent;      // 父节点索引
    int leftchild;   // 左子节点索引
    int rightchild;  // 右子节点索引
};

// 赫夫曼树类
class HuffMan {
private:
    void BuildTree();  // 构建赫夫曼树
    void InitializeTree(int n, const vector<int>& wt);  // 初始化赫夫曼树
    pair<int, int> SelectMin(int pos);  // 选择最小的两个节点

public:
    int len;  // 节点总数
    int lnum; // 叶子节点数量
    vector<HuffNode> huffTree; // 赫夫曼树
    vector<string> huffCode;   // 赫夫曼编码

    void MakeTree(int n, const vector<int>& wt); // 创建赫夫曼树
    void Coding();  // 进行赫夫曼编码
    void Destroy(); // 销毁赫夫曼树
};

// 初始化赫夫曼树
void HuffMan::InitializeTree(int n, const vector<int>& wt) {
    lnum = n;
    len = 2 * n - 1;
    huffTree.resize(len + 1);
    huffCode.resize(lnum + 1);

    for(int i = 1; i <= n; i++) {
        huffTree[i].weight = wt[i - 1];  // 初始化叶子节点权值
    }
    for(int i = 1; i <= len; i++) {
        // 初始化所有节点的父节点和子节点为0
        huffTree[i].parent = huffTree[i].leftchild = huffTree[i].rightchild = 0;
    }
}

// 选择权值最小的两个节点
pair<int, int> HuffMan::SelectMin(int pos) {
    // 使用优先队列存储权值和索引的对，按权值从小到大排序
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 遍历赫夫曼树数组中的前 pos 个元素
    for (int i = 1; i <= pos; i++) {
        // 如果当前节点没有父节点（即未被合并到其他节点中）
        if (huffTree[i].parent == 0) {
            // 将节点的权值和索引作为一对插入优先队列
            pq.push({huffTree[i].weight, i});
        }
    }

    // 从优先队列中取出权值最小的元素（即队首元素），并从队列中移除该元素
    pair<int, int> first = pq.top(); pq.pop();
    // 再次取出队列中权值最小的元素，这时是第二小的元素
    pair<int, int> second = pq.top(); pq.pop();

    // 返回这两个最小权值节点的索引
    return {first.second, second.second};
}


// 构建赫夫曼树
void HuffMan::BuildTree() {
    for(int i = lnum + 1; i <= len; i++) {
        auto [s1, s2] = SelectMin(i - 1);  // 选择最小的两个节点
        // 设置这两个节点的父节点为新节点
        huffTree[s1].parent = huffTree[s2].parent = i;
        // 新节点的左右子节点分别设置为这两个节点
        huffTree[i].leftchild = s1;
        huffTree[i].rightchild = s2;
        // 新节点的权值为这两个节点权值之和
        huffTree[i].weight = huffTree[s1].weight + huffTree[s2].weight;
    }
}

// 创建赫夫曼树
void HuffMan::MakeTree(int n, const vector<int>& wt) {
    InitializeTree(n, wt);  // 初始化赫夫曼树
    BuildTree();  // 构建赫夫曼树
}

// 进行赫夫曼编码
void HuffMan::Coding() {
    string cd;
    for(int i = 1; i <= lnum; ++i) {
        cd.clear();
        for(int c = i, f = huffTree[i].parent; f != 0; c = f, f = huffTree[f].parent) {
            // 从叶子到根反向生成编码
            cd = (huffTree[f].leftchild == c ? '0' : '1') + cd;
        }
        huffCode[i] = cd;  // 保存编码
    }
}

// 销毁赫夫曼树
void HuffMan::Destroy() {
    len = lnum = 0;
    huffTree.clear();
    huffCode.clear();
}

// 主函数
int main() {
    int t, n;
    cin >> t;
    while(t--) {
        unordered_set<char> alpha;  // 存放不重复的字母表
        string input; // 输入的字符串
        cin >> input;
        for (char c : input) {
            alpha.insert(c); // 提取唯一字母
        }
        // 每个字母出现多少次, 权重就是多少
        vector<int> wt;
        for (auto c : alpha) {
            wt.push_back(count(input.begin(), input.end(), c));
        }
        // 建树
        HuffMan myHuff;
        myHuff.MakeTree(alpha.size(), wt);  // 创建赫夫曼树
        myHuff.Coding();  // 进行编码
        int sum(0);
        for (int i = 1; i <= alpha.size(); ++i) {
            sum += (myHuff.huffCode[i].length() * wt[i-1]);
        }
        cout << sum << endl;
        myHuff.Destroy();  // 销毁赫夫曼树
    }
    return 0;
}
