#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 105;
const int MAXB = 10005;

int n, budget;
int prices[MAXN], preferences[MAXN];
int dp[MAXN][MAXB];

int main() {
    // Example test case
    n = 5;
    budget = 10;
    int prices[] = {2, 3, 4, 5, 6};
    int preferences[] = {1, 2, 3, 4, 5};

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= budget; j++) {
            if (prices[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-prices[i-1]] + preferences[i-1]);
            }
        }
    }

    cout << dp[n][budget] << endl;

    // To reconstruct the items that were chosen, we can backtrack through the dp array:
    int i = n, j = budget;
    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i-1][j]) {
            // item i was not included in the optimal solution
            i--;
        } else {
            // item i was included in the optimal solution
            cout << i << " ";
            j -= prices[i-1];
            i--;
        }
    }
    cout << endl;

    // Additional test case
    n = 4;
    budget = 7;
    int prices2[] = {1, 3, 4, 5};
    int preferences2[] = {1, 4, 5, 7};

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= budget; j++) {
            if (prices2[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-prices2[i-1]] + preferences2[i-1]);
            }
        }
    }

    cout << dp[n][budget] << endl;

    // To reconstruct the items that were chosen, we can backtrack through the dp array:
    i = n, j = budget;
    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i-1][j]) {
            // item i was not included in the optimal solution
            i--;
        } else {
            // item i was included in the optimal solution
            cout << i << " ";
            j -= prices2[i-1];
            i--;
        }
    }
    cout << endl;

    return 0;
}
