package Backtracking;
import java.util.*;

public class comb {
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        Arrays.sort(candidates);
        List<List<Integer>> result = new ArrayList<>();
        backtrack(candidates, target, 0, new ArrayList<>(), result);
        return result;
    }

    private void backtrack(int[] candidates, int target, int index,
                           List<Integer> current, List<List<Integer>> result) {
        if (target == 0) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int i = index; i < candidates.length; i++) {
            if (i > index && candidates[i] == candidates[i - 1]) continue; // skip duplicates
            if (candidates[i] > target) break;

            current.add(candidates[i]);
            backtrack(candidates, target - candidates[i], i + 1, current, result);
            current.remove(current.size() - 1);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        comb cs = new comb();

        System.out.print("Enter number of candidates: ");
        int n = scanner.nextInt();
        int[] candidates = new int[n];

        System.out.print("Enter the candidate values: ");
        for (int i = 0; i < n; i++) {
            candidates[i] = scanner.nextInt();
        }

        System.out.print("Enter the target sum: ");
        int target = scanner.nextInt();

        List<List<Integer>> result = cs.combinationSum2(candidates, target);
        System.out.println("Combinations:");
        for (List<Integer> combo : result) {
            System.out.println(combo);
        }

        scanner.close();
    }
}
