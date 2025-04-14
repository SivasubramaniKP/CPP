package Model_2.Backtracking.nQueens;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

public class NQueens {
    static List<List<String>> solveNQueens(int n) {
        List<List<String>> res = new ArrayList<>();
        char [][] board = new char[n][n];

        for ( char row[] : board ) Arrays.fill(row, '.');

        HashSet<Integer> cols = new HashSet<>();
        HashSet<Integer> posDiag = new HashSet<>();
        HashSet<Integer> negDiag = new HashSet<>();
        backtrack(0, board, res, cols, posDiag, negDiag);
        return res;
    }

    static void backtrack(int row, char[][]board,List<List<String>> res, HashSet<Integer> cols, HashSet<Integer> posDiag, HashSet<Integer> negDiag) {
        if ( row == board.length ) {
            res.add(construct(board));
            return;
        }
        for ( int col = 0; col < board.length; col++ ) {
            if ( cols.contains(col) || posDiag.contains(row + col) || negDiag.contains(row - col) ) {
                continue;
            }
            board[row][col] = 'Q';
            cols.add(col);
            posDiag.add(row + col);
            negDiag.add(row - col);
            backtrack( row + 1, board, res, cols, posDiag, negDiag);    
            board[row][col] = '.';
            cols.remove(col);
            posDiag.remove(row + col);
            negDiag.remove(row - col);
        } 
    }
    
    static List<String> construct(char [][] board) {
        List<String> layout = new ArrayList<>();
        for ( char[] row : board ) layout.add(new String(row));
        return layout;
    } 
    

    public static void main(String[] args) {
        int n = 8;
        List<List<String>> solutions = solveNQueens(n);
        for (List<String> sol : solutions) {
            for (String row : sol) {
                System.out.println(row);
            }
            System.out.println();
        }
        System.out.println("Total: " + solutions.size());
    }
}
