#include <iostream>
using namespace std;

// 在旋转排序数组中进行二分查找
int searchInRotatedArray(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; // 计算中间索引

        // 检查中间元素是否为目标值
        if (arr[mid] == target) {
            return mid; // 找到目标值，返回其索引
        }

        // 判断中间元素所在的子数组是否为升序
        if (arr[low] <= arr[mid]) {
            // 中间元素在左侧升序子数组中
            if (arr[low] <= target && target < arr[mid]) {
                high = mid - 1; // 目标值位于左侧子数组
            } else {
                low = mid + 1; // 目标值位于右侧子数组
            }
        } else {
            // 中间元素在右侧升序子数组中
            if (arr[mid] < target && target <= arr[high]) {
                low = mid + 1; // 目标值位于右侧子数组
            } else {
                high = mid - 1; // 目标值位于左侧子数组
            }
        }
    }
    return -1; // 在数组中没有找到目标值
}

int main() {
    int t;
    cin >> t; // 读取测试样例的数量
    while (t--) {
        int n, target;
        cin >> n; // 读取数组大小
        int *arr = new int[n]; // 动态分配数组
        for (int i = 0; i < n; ++i) {
            cin >> arr[i]; // 读取数组元素
        }
        cin >> target; // 读取要查找的目标值

        // 在旋转排序数组中查找目标值
        int result = searchInRotatedArray(arr, n, target);
        cout << result << endl; // 输出查找结果

        delete[] arr; // 释放动态分配的内存
    }
    return 0;
}
