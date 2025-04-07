#include <bits/stdc++.h>

// Merging two sorted subarrays
void Merge(std::vector<int> &arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
   
    std::vector<int> A(n1), B(n2);

    for ( int i = 0 ; i < n1; i++ ) {
        A[i] = arr[low + i];
    }
    for ( int i = 0 ; i < n2; i++ ) B[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = low;

    while ( i < n1 && j < n2 ) {
        if ( A[i] < B[j] ) arr[k++] = A[i++];
        else arr[k++] = B[j++];
    }
    while ( i < n1 ) arr[k++] = A[i++];
    while ( j < n2 ) arr[k++] = B[j++];
}

void MergeSort(std::vector<int> &arr, int low, int high) {
    if ( low < high ) {
        int mid = ( low + high )/2;
        MergeSort(arr, low, mid);
        MergeSort(arr, mid + 1, high);
        Merge(arr, low, mid, high);
    }
}

// Merge Sort function

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    MergeSort(arr, 0, n - 1);

    std::cout << "Sorted array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;
    
    for (int num : arr)
        std::cout << num << " ";
    return 0;
}
