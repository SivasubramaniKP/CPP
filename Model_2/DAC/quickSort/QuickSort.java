package Model_2.DAC.quickSort;

public class QuickSort {
    
    
    static int partition(int [] arr, int low, int high) {
        int pivot = arr[low];
        int l = low - 1;
        int r = high + 1;
        while ( true ) {
            do {
                l += 1;
            }while ( arr[l] < pivot );

            do {
                r -= 1;
            }while( arr[r] > pivot );
            if ( l >= r ) return r;
            int temp = arr[r];
            arr[r] = arr[l];
            arr[l] = temp; 
        }
    }

    static void quickSort(int [] arr, int low,int high) {
        if ( low < high ) {
            int p = partition(arr, low, high);
            quickSort(arr, low, p);
            quickSort(arr, p + 1, high);
        }
    }

    static void printArray(int a[], int l) {
        for ( int i = 0 ; i < l; i++ ) {
            System.out.print(a[i] + " ");
        }
    }
    public static void main(String[] args) {
        int a[] = { 9, 8, 7,6,4,3,2,1 };
        quickSort(a, 0, a.length - 1);
        printArray(a, a.length); 
    }
}
