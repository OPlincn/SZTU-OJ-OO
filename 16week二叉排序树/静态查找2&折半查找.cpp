#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int x=0; // target

bool halfSearch(double& left, double& right) {
    double mid = (left + right) / 2;
    double result = (mid*mid) - x;
    if (abs(result) < 0.00001) return true;
    if (result > 0) right = (left+right) / 2.0;
    else left = (left+right) / 2.0;
    return false;
}

int main () {
    int n; cin >> n;
    while (n--) {
        double left = 0;
        double right; cin >> right; x = right;
        while (true) {
            bool pr = halfSearch(left, right);
            if (pr) {
                cout<<fixed<<setprecision(3)<< (left+right)/2.0 <<endl;
                break;
            }
        }

    }
    return 0;
}