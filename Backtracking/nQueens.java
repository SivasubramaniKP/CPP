package Backtracking;
import java.util.*;
public class nQueens {
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> result = new ArrayList<>();
        char[][] board = new char[n][n];
        for (char[] row : board)
            Arrays.fill(row, '.');

        HashSet<Integer> cols = new HashSet<>();
        HashSet<Integer> diag1 = new HashSet<>();  
        HashSet<Integer> diag2 = new HashSet<>();  

        backtrack(0, board, result, cols, diag1, diag2, n);
        return result;
    }

    private void backtrack(int row, char[][] board, List<List<String>> result,
                           HashSet<Integer> cols, HashSet<Integer> diag1, HashSet<Integer> diag2, int n) {
        if (row == n) {
            List<String> solution = new ArrayList<>();
            for (char[] r : board)
                solution.add(new String(r));
            result.add(solution);
            return;
        }

        for (int col = 0; col < n; col++) {
            int d1 = row - col;
            int d2 = row + col;

            if (cols.contains(col) || diag1.contains(d1) || diag2.contains(d2)) continue;

            
            board[row][col] = 'Q';
            cols.add(col);
            diag1.add(d1);
            diag2.add(d2);

            backtrack(row + 1, board, result, cols, diag1, diag2, n);

            
            board[row][col] = '.';
            cols.remove(col);
            diag1.remove(d1);
            diag2.remove(d2);
        }
    }

    public static void main(String[] args) {
        nQueens nq = new nQueens();
        List<List<String>> solutions = nq.solveNQueens(4);
        for (List<String> sol : solutions) {
            for (String row : sol)
                System.out.println(row);
            System.out.println();
        }
    }
}
