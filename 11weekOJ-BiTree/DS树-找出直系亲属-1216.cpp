#include <iostream>
#include <string>
using namespace std;

// 树节点的定义
class Node {
public:
    int parent1, parent2;
    Node() : parent1(-1), parent2(-1) {}
};

// 在树中递归搜索
int findRelation(Node tree[], int from, int to, int depth) {
    if (from == to) return depth; // 找到了
    if (tree[from].parent1 != -1) {
        int d = findRelation(tree, tree[from].parent1, to, depth + 1);
        if (d != -1) return d;
    }
    if (tree[from].parent2 != -1) {
        int d = findRelation(tree, tree[from].parent2, to, depth + 1);
        if (d != -1) return d;
    }
    return -1;
}

// 打印关系
void printRelation(int depth, bool isAncestor) {
    if (depth == 1) cout << (isAncestor ? "parent" : "child") << endl;
    else if (depth > 1) {
        for (int j = depth; j > 2; j--) cout << "great-";
        cout << (isAncestor ? "grandparent" : "grandchild") << endl;
    } else {
        cout << "-" << endl;
    }
}

int main() {
    int n, m;
    Node tree[26];
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        for (int i = 0; i < 26; i++) tree[i] = Node(); // 初始化家族树
        for (int i = 0; i < n; i++) {
            string relation;
            cin >> relation;
            // 如果存在Parent, 则更改值
            if (relation[1] != '-') tree[relation[0] - 'A'].parent1 = relation[1] - 'A';
            if (relation[2] != '-') tree[relation[0] - 'A'].parent2 = relation[2] - 'A';
        }
        // 提问环节
        for (int i = 0; i < m; i++) {
            string query;
            cin >> query;
            int from = query[0] - 'A', to = query[1] - 'A';
            // 先找 child
            int relation = findRelation(tree, from, to, 0);
            if (relation != -1) {
                printRelation(relation, false); // from is a descendant of to
            } else { // 然后找Parents
                relation = findRelation(tree, to, from, 0);
                printRelation(relation, true); // from is an ancestor of to
            }
        }
    }
    return 0;
}
