#include <iostream>
using namespace std;

struct outpost {
    int size;
    int* array;

    outpost(int n) {
        this->size = n;
        this->array = new int[n+1]; // 正确地初始化成员变量array
        for (int i = 1; i <= n; ++i) {
            cin >> array[i];
        }
    }

    ~outpost() {
        if (array != nullptr) {
            delete[] array;
        }
    }
};

/*带哨兵的直接顺序查找*/
int sequential_search(outpost& myOutpost,int key)  //n为数组元素个数，key为待查找元素
{
    int i = myOutpost.size;
    myOutpost.array[0]=key;   //a[0]是监视哨

    while(myOutpost.array[i]!=key)  //若数组中无key，则一定会得到a[0]=key
        i--;

    return i;     //查找失败返回0
}

int main () {
    int n;
    while (cin >> n) {
        outpost myPost(n);
        int t; cin >> t;
        while (t--) {
            int x;
            cin >> x;
            int result = sequential_search(myPost, x);
            if (result) cout << result;
            else cout << "error";
            cout << endl;
        }
    }
    return 0;
}