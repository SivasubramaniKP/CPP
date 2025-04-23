package Final;
import java.util.*;

public class combinationalSum {

    static int findSum(ArrayList<Integer>a) {
        int sum = 0;
        for (int i : a) {
            sum += i;
        }
        return sum;
    }

   static void printArray(ArrayList<Integer>a) {
    for ( int i : a ) {
        System.out.print(i + " ");
    }
    System.out.println();
   } 

    static void solveCombinationSum (int [] arr, int target) {
        ArrayList<Integer> subSet = new ArrayList<>();
        backtrakc(0, arr, subSet, target); 
    }
    
    static void backtrakc(int index, int arr[],ArrayList<Integer> subSet, int target) {
        if (findSum(subSet) == target) {
            printArray(subSet);
            return;
        }

        if ( index == arr.length ) return;
        subSet.add(arr[index]);
        backtrakc(index + 1, arr, subSet, target);  
        subSet.remove(subSet.size() - 1);
        backtrakc(index + 1, arr, subSet, target); 
    }


    public static void main(String[] args) {
        int a[] = {1,4,5,2,-4, -3};
        int target = 7;
        solveCombinationSum(a, target);
    }
}
