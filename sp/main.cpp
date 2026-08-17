#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, x, t, biggest;
int k[15][100005];
int dp[100005][15];      // 动态规划数组：dp[时间][位置] = 最大金币

int main() {
    while (1) {
        cin >> n;
        if (n == 0) break;
        memset(k, 0, sizeof(k));
        memset(dp, -0x3f, sizeof(dp)); //不可达设为极小值
        biggest = 0;

        for (int i = 0; i < n; i++) {
            cin >> x >> t;
            k[x][t]++;
            biggest = max(biggest, t);
        }

        dp[0][5] = 0;
        for (int nowt = 0; nowt < biggest; nowt++) {
            for (int pos = 0; pos <= 10; pos++) {
                if (dp[nowt][pos] == -0x3f) continue;

                //左、不动、右
                if (pos - 1 >= 0)
                    dp[nowt+1][pos-1] = max(dp[nowt+1][pos-1], dp[nowt][pos] + k[pos-1][nowt+1]);
                // 不动
                dp[nowt+1][pos] = max(dp[nowt+1][pos], dp[nowt][pos] + k[pos][nowt+1]);
                // 右
                if (pos + 1 <= 10)
                    dp[nowt+1][pos+1] = max(dp[nowt+1][pos+1], dp[nowt][pos] + k[pos+1][nowt+1]);
            }
        }

        // 找最大值
        int summax = 0;
        for (int i = 0; i <= 10; i++) {
            summax = max(summax, dp[biggest][i]);
        }
        cout << summax << endl;
    }
    return 0;
}