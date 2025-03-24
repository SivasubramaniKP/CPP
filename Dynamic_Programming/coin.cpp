#include <bits/stdc++.h>
using namespace std;

int minCoins(vector<int>& coins, int target) {
    int n = coins.size();
    vector<int> dp(target + 1, INT_MAX); 
    dp[0] = 0; 

    for (int i = 1; i <= target; i++) {
        for (int coin : coins) {
            if (i >= coin && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return (dp[target] == INT_MAX) ? -1 : dp[target]; 
}

int main() {
    vector<int> coins = {1, 3, 4}; 
    int target = 6; 
    cout << "Minimum coins required: " << minCoins(coins, target) << endl;
    return 0;
}
