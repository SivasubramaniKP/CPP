package Final;

import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

public class quickSort {
    static int partition(int a[], int low, int high) {
        int pivot = a[low];
        int l = low + 1;
        int r = high;
        while (true) {
            while ( l <= r && a[l] < pivot ) l += 1;
            while ( r >= l && a[r] > pivot ) r -= 1;
            if ( l > r ) break;
            int temp = a[l];
            a[l] = a[r];
            a[r] = temp;
        }
        int temp = a[low];
        a[low] = a[r];
        a[r] = temp;
        return r;
    } 

    static void quickSort_(int [] a, int low, int high) {
        if ( low < high ) {
            int p = partition(a, low, high);
            quickSort_(a, low, p);
            quickSort_(a, p + 1, high);
        }
    }

    static void printArray(int a[]) {
        for ( int i : a ) {
            System.out.print(i + " ");
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
        quickSort_(a, 0, a.length - 1);
        printArray(a);  
        for ( int i = 0 ; i < 100; i++ ) {
            pw.println(Integer.toString(a[i]));
        }
        sc.close();
        pw.close();
    }
}
