#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void printOptimalParenthesis(vector<vector<int>>& bracket, int i, int j, char& name) {
    if (i == j) {
        cout << name++;
        return;
    }
    cout << "(";
    printOptimalParenthesis(bracket, i, bracket[i][j], name);
    printOptimalParenthesis(bracket, bracket[i][j] + 1, j, name);
    cout << ")";
}

void matrixChainMultiplication(vector<int>& dims) {
    int n = dims.size() - 1; 
    vector<vector<int>> dp(n, vector<int>(n, 0));   
    vector<vector<int>> bracket(n, vector<int>(n, 0));  

    for (int L = 2; L <= n; L++) {
        for (int i = 0; i < n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    bracket[i][j] = k; 
                }
            }
        }
    }

    cout << "Minimum number of multiplications: " << dp[0][n - 1] << endl;
    cout << "Optimal Parenthesization: ";
    char name = 'A';
    printOptimalParenthesis(bracket, 0, n - 1, name);
    cout << endl;
}

int main() {
    vector<int> dims = {10, 30, 5, 60}; 
    matrixChainMultiplication(dims);
    return 0;
}
