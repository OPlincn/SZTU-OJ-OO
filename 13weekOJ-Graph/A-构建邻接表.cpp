#include <iostream>
using namespace std;
int n;
int getNodeIndex(const char* nodeVec, char node) {
    for (int i = 0; i < n; ++i) {
        if (node == nodeVec[i]) return i;
    }
}

void setMatrixZero(int** matrix) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = 0;
        }
    }
}

int main () {
    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> n >> k;
        int* numVec = new int[n];
        char* nodeVac = new char[n];
        for (int i = 0; i < n; ++i) {
            cin >> nodeVac[i];
            numVec[i] = i;
        }
        int **nearMatrix = new int*[n];
        for (int i = 0; i < n; ++i) {
            nearMatrix[i] = new int[n];
        }
        setMatrixZero(nearMatrix);

        while (k--) {
            char x, y;
            cin >> x >> y;
            int xIndex, yIndex;
            xIndex= getNodeIndex(nodeVac, x);
            yIndex= getNodeIndex(nodeVac, y);
            nearMatrix[xIndex][yIndex] = 1;
        }
        for (int i = 0; i < n; ++i) {
            cout << i << ' ' << nodeVac[i];
            for (int j = 0; j < n; ++j) {
                if (nearMatrix[i][j] == 1) cout << '-' << numVec[j];
            }
            cout << '-' << '^' << endl;
        }
        for (int i = 0; i < n; ++i) {
            delete[] nearMatrix[i];
        }
        delete[] nearMatrix;
    }
    return 0;
}