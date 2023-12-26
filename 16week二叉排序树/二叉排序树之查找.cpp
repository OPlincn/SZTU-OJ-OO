#include <iostream>
using namespace std;
struct BiNode {
    int data;
    BiNode *lchild, *rchild;
    BiNode() {
        data = 0;
        lchild = nullptr;
        rchild = nullptr;
    }
};



class BiSortTree {
private:
    BiNode *root;
public:
    BiSortTree(int array[], int arrayLength);
//    ~BiSortTree();
    BiNode* searchBST(BiNode *bt, int key, int& count);
    void deleteNode(BiNode *bt);
    void inOrder(const BiNode *bt);
    void insertBST(BiNode* &bt, int key);
    BiNode* getRoot() {return root;};
};

BiSortTree::BiSortTree(int *array, int arrayLength) {
    root = nullptr;
    for (int i = 0; i < arrayLength; ++i) {
        insertBST(root, array[i]);
    }
}

//BiSortTree::~BiSortTree() {
//}

void BiSortTree::insertBST(BiNode *&bt, int key) {
    if (bt == nullptr) {
        bt = new BiNode;
        bt->data = key;
    }
    else {
        if (key < bt->data) insertBST(bt->lchild, key);
        else insertBST(bt->rchild, key);
    }
}

void BiSortTree::inOrder(const BiNode *bt) {
    if (!bt) return;
    if (bt->lchild) inOrder(bt->lchild);
    cout << bt->data << ' ';
    if (bt->rchild) inOrder((bt->rchild));
    if (!bt->lchild && !bt->rchild) return;
}

BiNode* BiSortTree::searchBST(BiNode *bt, int key, int& count) {
    if (!bt) return nullptr;
    ++count;
    if (bt->data == key) return bt;
    else {
        if (bt->data < key) return searchBST(bt->rchild, key, count);
        else return searchBST(bt->lchild, key, count);

    }
}


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
            int count(0);
            auto result = tree.searchBST(tree.getRoot(), x, count);
            if (result) cout << count;
            else cout << "-1";
            cout << endl;
        }
    }
    return 0;
}
