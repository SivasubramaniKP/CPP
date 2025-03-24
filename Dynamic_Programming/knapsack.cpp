#include <bits/stdc++.h>
using namespace std;


int knapsack(int W, vector<int>& weights, vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

int main() {
    vector<int> weights = {2, 3, 4, 5}; 
    vector<int> values = {3, 4, 5, 6};  
    int W = 5;
    int n = weights.size();
    
    cout << "Maximum value in Knapsack = " << knapsack(W, weights, values, n) << endl;
    return 0;
}
