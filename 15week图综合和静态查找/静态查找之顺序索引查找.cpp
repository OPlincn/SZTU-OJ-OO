#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k, t; // n 是主表的数据个数，k 是块的数量，t 是要查找的数据个数
    while(cin >> n) {
        vector<int> a(n + 1); // 创建主表，存储数据，从索引1开始
        for (int i = 1; i <= n; i++) {
            cin >> a[i]; // 读取主表的数据
        }

        cin >> k; // 读取块的数量
        vector<int> max(k); // 存储每个块的最大值
        for (int i = 0; i < k; i++) {
            cin >> max[i]; // 读取索引表中每个块的最大值
        }

        vector<int> index(k); // 存储每个块的起始索引
        index[0] = 1; // 第一个块从索引1开始
        int j = 0; // 块的索引
        for (int i = 1; i <= n; i++) {
            // 如果当前数据项大于当前块的最大值，则更新下一个块的起始索引
            if (a[i] > max[j]) {
                index[++j] = i; // 更新下一个块的起始索引
            }
        }

        cin >> t; // 读取要查找的数据个数
        while (t--) {
            int num, sum = 0, found = 0; // num 是要查找的数，sum 是查找次数，found 表示是否找到
            cin >> num; // 读取要查找的数

            // 检查 num 是否小于等于整个数组中的最大值
            if (num <= max[k - 1]) {
                // 计算 num 所在的区间
                for (j = 0; j < k; j++) {
                    sum++; // 每检查一个区间，查找次数加1
                    if (num <= max[j]) { // 找到所在区间
                        break;
                    }
                }

                // 计算查找区间的结束点
                int temp = (j == k - 1) ? n : index[j + 1];

                // 在确定的区间内进行查找
                for (int i = index[j]; i <= temp; i++) {
                    sum++; // 每检查一个数据项，查找次数加1
                    if (num == a[i]) { // 如果找到了，输出位置和查找次数
                        cout << i << "-" << sum << endl;
                        found = 1; // 标记为找到
                        break;
                    }
                }

                // 如果在区间内没找到，输出 error
                if (!found) {
                    cout << "error" << endl;
                }
            } else {
                // 如果 num 超过了整个数组的最大值，输出 error
                cout << "error" << endl;
            }
        }
    }

    return 0;
}
