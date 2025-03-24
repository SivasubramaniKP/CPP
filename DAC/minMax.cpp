#include <bits/stdc++.h>
using namespace std;

// Structure to store min and max
struct MinMax {
    int min;
    int max;
};

// Function to find min and max using Divide and Conquer
MinMax findMinMax(vector<int>& arr, int low, int high) {
    MinMax result, left, right;

    // Base case: Only one element
    if (low == high) {
        result.min = result.max = arr[low];
        return result;
    }

    // Base case: Two elements
    if (high == low + 1) {
        result.min = min(arr[low], arr[high]);
        result.max = max(arr[low], arr[high]);
        return result;
    }

    // Divide: Find the middle index
    int mid = low + (high - low) / 2;

    // Conquer: Recursively find min and max in left and right halves
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    // Combine: Get final min and max
    result.min = min(left.min, right.min);
    result.max = max(left.max, right.max);

    return result;
}

int main() {
    vector<int> arr = {3, 5, 1, 8, 9, 2, 7};
    int n = arr.size();

    MinMax result = findMinMax(arr, 0, n - 1);

    cout << "Minimum: " << result.min << endl;
    cout << "Maximum: " << result.max << endl;

    return 0;
}
