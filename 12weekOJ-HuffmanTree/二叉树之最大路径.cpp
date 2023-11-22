#include <iostream>
#include <map>
using namespace std;
struct TreeNode {
    char val;
    TreeNode *left, *right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

// 先序遍历构建二叉树
TreeNode* buildTree(string &preorder, int &index) {
    if (index >= preorder.size() || preorder[index] == '0') {
        index++;
        return nullptr;
    }
    TreeNode *root = new TreeNode(preorder[index++]);
    root->left = buildTree(preorder, index);
    root->right = buildTree(preorder, index);
    return root;
}


// 找到并打印每个叶子节点的深度
int nowMax = 0;
void findLeafDepths(TreeNode *node, int nowSumWeight, map<char, int>& weights) {
    if (node == nullptr) {
        return;
    }
    nowSumWeight += weights[node->val];
    if (nowSumWeight > nowMax) nowMax = nowSumWeight;
    findLeafDepths(node->left, nowSumWeight, weights);
    findLeafDepths(node->right, nowSumWeight, weights);
}


int main() {
    int t;
    cin >> t;
    while (t--) {
        string preorder;
        cin >> preorder;
        int index = 0;
        TreeNode *root = buildTree(preorder, index);
        int n;
        cin >> n;
        map<char, int> Weights;
        char cIndex = 'A';
        for (int i = 0; i < n; ++i) {
            int temp; cin >> temp;
            Weights.emplace(cIndex+i, temp);
        }
        findLeafDepths(root, 0, Weights);  // 从根节点开始，深度为0
        cout << nowMax;
        nowMax = 0;
        if (t!=0) cout << endl;
    }
    return 0;
}

