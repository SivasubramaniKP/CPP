package Model_2.DAC.quickSort;

public class quickSort2 {
    
    
    static int partition(int a[], int low, int high) {
        int pivot = a[low];
        int l= low + 1;
        int r = high;

        while ( true ) {
           while ( l <= r && a[l] < pivot ) l += 1;
           while ( r >= l && a[r] > pivot ) r -= 1;
            if ( l > r ) break; 
            int temp  = a[l];
            a[l] = a[r];
            a[r] = temp;
        } 

        int temp = a[low];
        a[low] = a[r];
        a[r] = temp;
        return r;
    }

    static void quickSort(int a[], int low, int high) {
        if ( low < high ) {
            int p = partition(a, low, high);
            quickSort(a, low, p); 
            quickSort(a, p + 1 , high);
        }
    }

    static void printArray(int a[]) {
        for ( int i : a ) {
            System.out.print(i + " ");
        }
    }


    public static void main(String[] args) {
        int a[] = {9,8,7,6,5,4,3,2,1};
        quickSort(a, 0, a.length - 1);
        printArray(a);
    }
}
