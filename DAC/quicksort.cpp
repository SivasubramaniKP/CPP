#include<iostream>
#include <vector>
#include <algorithm>

int partition(std::vector<int> &arr, int low, int high) {
        int pivot = arr[low];
        int l = low - 1;
        int r = high + 1;

        while (true) {
            do {
                l++;
            }while(arr[l] < pivot);
            do {
                r -= 1;

            } while ( arr[r] > pivot );
            if ( l >= r ) return r;
            std::swap(arr[l], arr[r]);
        }

        std::swap(arr[low], arr[r]);
}

void quickSort(std::vector<int> &arr, int low, int high) {
   if ( low < high ) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p);
        quickSort(arr, p + 1, high); 
    }
}
void printArray(const std::vector<int>& arr) {
    for (int num : arr)
        std::cout << num << " ";
    std::cout << "\n";
}

int main () {
    std::vector<int> a = {5, -4, 6, 0, -7, 1, 3, 11, 2};
    printArray(a);
    quickSort(a, 0, a.size() - 1);
    printArray(a);
    return 0;
}