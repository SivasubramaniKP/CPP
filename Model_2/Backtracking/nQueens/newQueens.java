package Model_2.Backtracking.nQueens;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

public class newQueens {


    static List<List<String>> solveNQueens(int row) {
       List<List<String>> res = new ArrayList<>();
        HashSet<Integer> col = new HashSet<>();
        HashSet<Integer> posDiag = new HashSet<>();
        HashSet<Integer> negDiag = new HashSet<>();

        char [][] board = new char[row][row];
        for( char [] r : board ) Arrays.fill(r, '.');
        Backtrack(0, board, col, posDiag, negDiag, res);
       return res;
    }

    static void Backtrack(int row, char[][] board, HashSet<Integer> col,
        HashSet<Integer> posDiag, HashSet<Integer> negDiag, List<List<String>> res 
    ) {
        if ( row == board.length ) {
            res.add(constructBoard(board));
            return;
        }

        for ( int c = 0; c < board.length; c++ ) {
            if ( col.contains(c) || posDiag.contains(row + c) || negDiag.contains(row - c) ) {
                continue;
            }
            col.add(c);
            posDiag.add(row + c);
            negDiag.add(row - c);
            board[row][c] = 'Q';

            Backtrack(row + 1, board, col, posDiag, negDiag, res);

            col.remove(c);
            posDiag.remove(row + c);
            negDiag.remove(row - c);
            board[row][c] = '.'; 
        }
    }

    static List<String> constructBoard(char [][] board) {
        List<String> layout = new ArrayList<>();
        for ( char [] row : board ) layout.add(new String(row));
        return layout;
    }
    
    public static void main(String[] args) {
        List<List<String>> res = solveNQueens(4);
        for ( List<String> sol : res ) {
            for ( String row : sol ) {
                System.out.println(row);
            } 
            System.out.println();
        } 
    }
}
