#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct BiNode {
    int data;
    BiNode *lchild, *rchild;
    BiNode() : data(0), lchild(nullptr), rchild(nullptr) {}
    BiNode(int x) : data(x), lchild(nullptr), rchild(nullptr) {}
};

// 使用层序遍历构建二叉树
BiNode* buildTree(const vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;

    queue<BiNode*> q;
    BiNode *root = new BiNode(nodes[0]);
    q.push(root);
    int i = 1;

    while (!q.empty() && i < nodes.size()) {
        BiNode *node = q.front();
        q.pop();

        if (i < nodes.size() && nodes[i] != -1) {
            node->lchild = new BiNode(nodes[i]);
            q.push(node->lchild);
        }
        i++;

        if (i < nodes.size() && nodes[i] != -1) {
            node->rchild = new BiNode(nodes[i]);
            q.push(node->rchild);
        }
        i++;
    }
    return root;
}

// 检查二叉树是否为二叉排序树的递归函数
bool isBST(BiNode *node, int &prev) {
    if (node == nullptr) return true;
    if (!isBST(node->lchild, prev)) return false;
    if (node->data <= prev) return false;
    prev = node->data;
    return isBST(node->rchild, prev);
}

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) {
            cin >> nodes[i];
        }
        BiNode *root = buildTree(nodes);
        int prev = INT_MIN; // 使用一个很小的初始值
        cout << (isBST(root, prev) ? "true" : "false") << endl;
    }
    return 0;
}
