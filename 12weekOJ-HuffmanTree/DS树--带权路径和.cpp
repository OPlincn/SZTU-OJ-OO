#include <iostream>
#include <queue>
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
void findLeafDepths(TreeNode *node, int depth, vector<int>& result) {
    if (node == nullptr) {
        return;
    }
    // 如果是叶子节点
    if (node->left == nullptr && node->right == nullptr) {
//        cout << "Leaf " << node->val << " Depth: " << depth << endl;
        result.push_back(depth);
    } else {
        findLeafDepths(node->left, depth + 1, result);
        findLeafDepths(node->right, depth + 1, result);
    }
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
        vector<int> leavesWeight;
        for (int i = 0; i < n; ++i) {
            int temp; cin >> temp;
            leavesWeight.push_back(temp);
        }
        vector<int> leavesLevel;
        findLeafDepths(root, 0, leavesLevel);  // 从根节点开始，深度为0
        // debug use
//        cout << "weight:" << endl;
//        for (auto c : leavesWeight) cout << c;
//        cout << endl;
//        cout << "depth:" << endl;
//        for (auto c : leavesLevel) cout << c;
//        cout << endl;
        int levelIndex(0), sum(0);
        for (auto c : preorder) {
            if (c >= 'A' && c <= 'Z') {
                sum += (leavesWeight[levelIndex] * leavesLevel[levelIndex]);
                ++levelIndex;
            }

        }
        cout << sum;
        if (t!=0) cout << endl;
    }
    return 0;
}

