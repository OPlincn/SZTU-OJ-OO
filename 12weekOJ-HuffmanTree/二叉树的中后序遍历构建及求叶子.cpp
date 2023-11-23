#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
// 为了理解通过中序\后序遍历来构建左右子树, 可以参考:
// https://zhuanlan.zhihu.com/p/266037746 里面那张左右子树构建图非常精髓

// 定义二叉树的节点结构
struct TreeNode {
    int val;             // 节点存储的值
    TreeNode *left;      // 指向左子节点的指针
    TreeNode *right;     // 指向右子节点的指针
    // 构造函数初始化节点
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 递归函数来根据中序和后序遍历结果构建二叉树
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, int inStart, int inEnd, int postStart, int postEnd) {
    if (inStart > inEnd) {
        return nullptr; // 基本情况，如果没有元素来构建树，则返回空
    }

    // 后序遍历的最后一个元素是当前的根节点
    int rootVal = postorder[postEnd];
    TreeNode* root = new TreeNode(rootVal); // 创建根节点

    // 在中序遍历中找到根节点的位置
    int rootIndex = std::find(inorder.begin() + inStart, inorder.begin() + inEnd + 1, rootVal) - inorder.begin(); // -掉头, 只返回一个index
    // rootVal 是后序遍历的最后一个元素，即当前子树的根节点。
    //std::find 函数在 inorder（中序遍历结果）的子范围 [inStart, inEnd] 中查找 rootVal。
    //找到后，计算 rootVal 在 inorder 中的索引 rootIndex。这个索引是相对于整个 inorder 数组的，所以需要从 inorder.begin() 开始计算。

    // 递归构建左子树 [isStart, rootIndex-1] [postStart, postStart+(rootIndex - inStart - 1)]
    root->left = buildTree(inorder, postorder, inStart, rootIndex - 1, postStart, postStart + rootIndex - inStart - 1);
    //左子树的中序遍历是从 inStart 到 rootIndex - 1（因为 rootIndex 是根节点）。
    //对于左子树的后序遍历，它开始于 postStart，结束于 postStart + rootIndex - inStart - 1。
    //postStart + rootIndex - inStart - 1 的计算方式是基于中序遍历的左子树长度，它等于 rootIndex - inStart（左子树的元素数量），减去 1 是因为后序遍历中不包含根节点。

    // 递归构建右子树
    root->right = buildTree(inorder, postorder, rootIndex + 1, inEnd, postStart + rootIndex - inStart, postEnd - 1);
    //右子树的中序遍历从 rootIndex + 1（跳过根节点）到 inEnd。
    //右子树的后序遍历从 postStart + rootIndex - inStart（左子树后序遍历的下一个元素）开始，到 postEnd - 1 结束（因为 postEnd 是根节点）。

    return root; // 返回构建的树的根节点
}

// 递归函数来找出叶子节点中的最小值
int findMinLeaf(TreeNode* node) {
    if (node == nullptr) {
        return INT_MAX; // 基本情况，如果节点为空，则返回最大整数值
    }
    // 如果是叶子节点，则返回该节点的值
    if (node->left == nullptr && node->right == nullptr) {
        return node->val;
    }
    // 递归检查左右子树，并返回最小值
    return min(findMinLeaf(node->left), findMinLeaf(node->right));
}

// 主函数
int main() {
    int t, N;
    cin >> t; // 读取测试数据的组数
    while (t--) {
        cin >> N; // 读取每组测试数据的节点数
        vector<int> inorder(N), postorder(N);
        for (int i = 0; i < N; ++i) {
            cin >> inorder[i]; // 读取中序遍历结果
        }
        for (int i = 0; i < N; ++i) {
            cin >> postorder[i]; // 读取后序遍历结果
        }
        // 构建树
        TreeNode* root = buildTree(inorder, postorder, 0, N - 1, 0, N - 1);
        // 遍历 [0, N-1], isStart/End 用于中序遍历, postStart/End 用于后序遍历
        // 输出叶子节点中的最小值
        cout << findMinLeaf(root) << endl;

    }
    return 0;
}
