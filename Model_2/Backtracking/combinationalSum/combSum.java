package Model_2.Backtracking.combinationalSum;

import java.util.ArrayList;

public class combSum {
    static int findSum(ArrayList<Integer> arr) {
        int sum = 0;
        for ( int i : arr ) {
            sum += i;
        }
        return sum;
    }
    static ArrayList<ArrayList<Integer>>  WrapperFunction(int a[], int target) {
        ArrayList<ArrayList<Integer>> res = new ArrayList<>();
        Backtrack(a, 0, new ArrayList<>(), res, target);
        return res;
    } 

    static void Backtrack(int [] array, int index, ArrayList<Integer> curSubSet, ArrayList<ArrayList<Integer>> res, int target) {
        if ( findSum(curSubSet) == target ) {
            res.add(new ArrayList<>(curSubSet)); 
            return;
        } if ( index == array.length ) return;
        curSubSet.add(array[index]);
        Backtrack(array, index + 1, curSubSet, res, target);
        curSubSet.remove(curSubSet.size() - 1);
        Backtrack(array, index + 1, curSubSet, res, target);
    }


    public static void main(String[] args) {
        int a[] = {1,2,3};
        ArrayList<ArrayList<Integer>> ans = WrapperFunction(a, 5);
        for ( ArrayList<Integer> i : ans ) {
            for( int j : i ) {
                System.out.print(j + " ");
            }
            System.out.println();
        } 
    }
}
