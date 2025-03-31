#include<iostream>
#include <vector>

void partition(std::vector<int> arr, int low, int high) {
    int left = low + 1;
    int right = high;
    int pivot = ( low == 0 ) ? arr[0] : arr[low - 1];
    while (left < right) {
        while ( left < right && arr[left] < pivot ) left+=1;
        while ( right > left && arr[right] > pivot ) right -= 1;
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left+=1;
        right-=1;
    }

}

int main () {
    std::vector<int> a = {5, -4, 6, 0, -7, 1, 3, 11, 2};
    partition(a, 0, a.size() - 1);
    return 0;
}