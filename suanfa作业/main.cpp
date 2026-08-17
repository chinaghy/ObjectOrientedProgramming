#include <iostream>
#include <climits>
using namespace std;

int a[10][10];
int sum = 0;
int mins = INT_MAX;
int startX, startY, endX, endY;

void bp(int minnow, int m, int n) {
    if (m == endX && n == endY) {
        if (minnow < mins) {
            mins = minnow;
        }
        sum++;
        return;
    }

    if (!a[m+1][n]) { a[m][n] = 1; bp(minnow+1, m+1, n); a[m][n] = 0; }
    if (!a[m-1][n]) { a[m][n] = 1; bp(minnow+1, m-1, n); a[m][n] = 0; }
    if (!a[m][n+1]) { a[m][n] = 1; bp(minnow+1, m, n+1); a[m][n] = 0; }
    if (!a[m][n-1]) { a[m][n] = 1; bp(minnow+1, m, n-1); a[m][n] = 0; }
}

int main() {
    int n = 9;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    cin >> startX >> startY >> endX >> endY;

    bp(0, startX, startY);

    cout << sum << endl;
    cout << mins << endl;

    return 0;
}