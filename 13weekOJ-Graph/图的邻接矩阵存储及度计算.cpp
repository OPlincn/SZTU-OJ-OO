#include <iostream>
using namespace std;

int n;
int getNodeIndex(const string* nodeVec, string node) {
    for (int i = 0; i < n; ++i) {
        if (node == nodeVec[i]) return i;
    }
}

void setMatrixZero(int** matrix) {
    for (int i = 0; i < n+1; ++i) {
        for (int j = 0; j < n+1; ++j) {
            matrix[i][j] = 0;
        }
    }
}

void printMatrix(int** matrix) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j];
            j!=n-1 ? cout << ' ' : cout << endl;
        }
    }
}
int main() {
    int T;
    cin >> T;
    char type;
    while (T--) {
        cin >> type >> n;
        string* nodeVec = new string[n];
        int* numVec = new int[n]; // the last group used to storage the sum
        for (int i = 0; i < n; ++i) {
            cin >> nodeVec[i];
            numVec[i] = i;
        }
        int **nearMatrix = new int*[n+1];
        for (int i = 0; i < n+1; ++i) {
            nearMatrix[i] = new int[n+1];
        }
        setMatrixZero(nearMatrix);
        int k; cin >> k;
        if (type == 'D') {
            while (k--) {
                string x, y;
                cin >> x >> y;
                int xIndex, yIndex;
                xIndex= getNodeIndex(nodeVec, x);
                yIndex= getNodeIndex(nodeVec, y);
                nearMatrix[xIndex][yIndex] = 1;
            }
            printMatrix(nearMatrix);
            // iterate x axis
            for (int i = 0; i < n; ++i) {
                // node's out sum
                int sum(0);
                for (int j = 0; j < n; ++j) {
                    sum += nearMatrix[i][j];
                }
                nearMatrix[i][n] = sum;
            }

            // iterate y axis
            for (int i = 0; i < n; ++i) {
                // node's in sum
                int sum(0);
                for (int j = 0; j < n; ++j) {
                    sum += nearMatrix[j][i];
                }
                nearMatrix[n][i] = sum;
            }
            for (int i = 0; i < n; ++i) {
                cout << nodeVec[i];
                int outSum, inSum, Sum;
                outSum=nearMatrix[i][n];inSum=nearMatrix[n][i];Sum=inSum+outSum;
                if (Sum!=0) {
                    cout << ": " << outSum
                    << ' ' << inSum
                    << ' ' << Sum;
                }
                cout << endl;
            }

        } else {
            while (k--) {
                string x, y;
                cin >> x >> y;
                int xIndex, yIndex;
                xIndex= getNodeIndex(nodeVec, x);
                yIndex= getNodeIndex(nodeVec, y);
                nearMatrix[xIndex][yIndex] = 1;
                nearMatrix[yIndex][xIndex] = 1;
            }
            printMatrix(nearMatrix);

            for (int i = 0; i < n; ++i) {
                // node's out sum
                int sum(0);
                for (int j = 0; j < n; ++j) {
                    sum += nearMatrix[i][j];
                }
                nearMatrix[i][n] = sum;
            }

            for (int i = 0; i < n; ++i) {
                cout << nodeVec[i];
                int outSum;
                outSum=nearMatrix[i][n];
                if (outSum!=0) {
                    cout << ": " << outSum;
                }

                cout << endl;
            }

        }
        for (int i = 0; i <= n; ++i) {
            delete[] nearMatrix[i];
        }
        delete[] nearMatrix;
    }
    return 0;
}