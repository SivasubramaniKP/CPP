package Model_2.Backtracking.combinationalSum;
import java.util.*;

public class newCombSum {
    static List<List<Integer>> solveCombinationSum(int [] arr, int target) {
        List<List<Integer>> res = new ArrayList<>();


        return res;

    }

    int findSum(List<Integer> arr) {
        int sum = 0;
        for( int i : arr ) sum += i;
        return sum;
    }

    void backtrack(int index, int arr[], int target, List<Integer> subSet, List<List<Integer>> res ) {
        if ( findSum(subSet) == target ) {
            res.add(new ArrayList<>(subSet));
            return;
        }

        subSet.add(arr[index]);
        backtrack(index + 1, arr, target, subSet, res);
        subSet.remove(subSet.size() - 1);
        backtrack(index + 1, arr, target, subSet, res);
    }
}
