
package Final;
import java.io.*;
import java.util.*;

public class merge {
    static void Merge(int arr[], int low, int mid, int high) {
        int n1 = mid - low + 1; 
        int n2 = high - mid;
        int a[] = new int[n1];
        int b[] = new int[n2];
        for ( int i = 0; i < n1; i++ ) a[i] = arr[low + i];
        for ( int i = 0; i < n2; i++ ) b[i] = arr[mid + i + 1];

        int i = 0, j = 0, k = low;
        while ( i < n1 && j < n2 ) {
            if ( a[i] < b[j] ) arr[k++] = a[i++];
            else arr[k++] = b[j++];   
        }
        while ( i < n1 ) arr[k++] = a[i++];
        while ( j < n2 ) arr[k++] = b[j++];
    } 


    static void MergeSort(int arr[], int low, int high) {
        if ( low < high ) {
            int mid = (low + high) / 2;
            MergeSort(arr, low, mid);
            MergeSort(arr, mid + 1, high);
            Merge(arr, low, mid, high); 
        }
    }

    static void printArray(int a[]) {
        for( int i : a ) {
            System.out.print(i + "  ");
        }
        System.out.println();
    }

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("./Final/number.txt"));
        int a[] = new int[100];
        for ( int i = 0; i < 100 ; i++ ) {
            a[i] = sc.nextInt();
        }
        PrintWriter pw = new PrintWriter(new File("./Final/result.txt"));
        MergeSort(a, 0, a.length - 1);
        printArray(a);  
        for ( int i = 0 ; i < 100; i++ ) {
            pw.println(Integer.toString(a[i]));
        }
        sc.close();
        pw.close();
    }
}
