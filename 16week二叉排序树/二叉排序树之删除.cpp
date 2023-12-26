#include <iostream>
using namespace std;

struct BiNode {
    int data;
    BiNode *lchild, *rchild;
    BiNode() : data(0), lchild(nullptr), rchild(nullptr) {}
};

class BiSortTree {
private:
    BiNode *root;

    // 从二叉排序树中删除指定键的节点
    void deleteBST(BiNode*& bt, int key) {
        if (!bt) return; // 如果节点为空，直接返回
        if (key == bt->data) {
            // 找到要删除的节点
            deleteNode(bt);
        } else if (key < bt->data) {
            // 如果键小于当前节点数据，则在左子树中继续查找
            deleteBST(bt->lchild, key);
        } else {
            // 如果键大于当前节点数据，则在右子树中继续查找
            deleteBST(bt->rchild, key);
        }
    }

    // 删除节点，并根据不同情况重排二叉树
    void deleteNode(BiNode*& node) {
        if (!node->lchild) {
            // 如果没有左子节点，直接用右子节点替代
            BiNode* temp = node;
            node = node->rchild;
            delete temp;
        } else if (!node->rchild) {
            // 如果没有右子节点，直接用左子节点替代
            BiNode* temp = node;
            node = node->lchild;
            delete temp;
        } else {
            // 如果有两个子节点，则找到左子树的最大节点或右子树的最小节点来替代
            BiNode* temp = node->lchild;
            BiNode* parent = node;
            while (temp->rchild) {
                parent = temp;
                temp = temp->rchild;
            }
            node->data = temp->data;
            if (parent == node) parent->lchild = temp->lchild;
            else parent->rchild = temp->lchild;
            delete temp;
        }
    }

public:
    BiSortTree(int array[], int arrayLength) : root(nullptr) {
        // 通过数组构建二叉排序树
        for (int i = 0; i < arrayLength; ++i) {
            insertBST(root, array[i]);
        }
    }

    void insertBST(BiNode*& bt, int key) {
        // 向二叉排序树中插入节点
        if (bt == nullptr) {
            bt = new BiNode;
            bt->data = key;
        } else {
            if (key < bt->data) insertBST(bt->lchild, key);
            else insertBST(bt->rchild, key);
        }
    }

    // 中序遍历二叉树
    void inOrder(const BiNode *bt) {
        if (!bt) return;
        inOrder(bt->lchild);
        cout << bt->data << ' ';
        inOrder(bt->rchild);
    }

    // 对外暴露的删除方法
    void remove(int key) { deleteBST(root, key); }

    // 获取根节点的引用
    BiNode*& getRoot() { return root; }
};

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int* array = new int[n];
        for (int i = 0; i < n; ++i) {
            cin >> array[i];
        }
        BiSortTree tree(array, n);
        tree.inOrder(tree.getRoot());
        cout << endl;
        int m; cin >> m;
        while (m--) {
            int x; cin >> x;
            tree.remove(x);
            tree.inOrder(tree.getRoot());
            cout << endl;
        }
        delete[] array;
    }
    return 0;
}
