
public class mergeSort {
   static void merge(int arr[], int low, int mid, int high) {
        int n1 = mid - low + 1;
        int n2 = high - mid;
        int A[] = new int[n1];
        int B[] = new int[n2];

        for ( int i = 0; i < n1; i++ ) A[i] = arr[low + i];
        for ( int i = 0; i < n2; i++ ) B[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = low;
        while ( i < n1 && j < n2 ) {
            if ( A[i] < B[j] ) arr[k++] = A[i++];
            else arr[k++] = B[j++];
        }
        while ( i < n1 ) arr[k++] = A[i++];
        while (j < n2 ) arr[k++] = B[j++];

    }

    static void MergeSort(int [] arr, int low , int high) {
        if ( low < high ) {
            int mid = (low + high)/2;
            MergeSort(arr, low, mid);
            MergeSort(arr, mid + 1, high);
            merge(arr, low, mid, high);
        }
    }
    static void printArray(int a[], int l) {
        for ( int i = 0 ; i < l; i++ ) {
            System.out.print(a[i] + " ");
        }
    }
    public static void main(String[] args) {
        int a[] = {9,8,7,6,5,4,3,2,1,0};
        MergeSort(a, 0, a.length - 1);
        printArray(a, a.length); 

    } 
}
