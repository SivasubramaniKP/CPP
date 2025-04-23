package Final.CAT_2;
import java.util.*;
public class nQueen {
    static void solveNQueen(int n) {
        char [][] board = new char[n][n];
        HashSet<Integer> posDiag = new HashSet<>();
        HashSet<Integer> negDiag = new HashSet<>();
        HashSet<Integer> col = new HashSet<>();
        for ( char [] row : board ) Arrays.fill(row, '.');
        backtrack(board, posDiag, negDiag, col, n, 0);
    }

    static void printBoard(char [][] board) {
        for ( int i = 0 ; i < board.length; i++ ) {
            for ( int j = 0 ;j < board.length ; j++ ) {
                System.out.print(board[i][j] + " ");
            } 
            System.out.println();
        }
        System.out.println();
    }
    static void backtrack(char[][]board, HashSet<Integer> posDiag, HashSet<Integer> negDiag, HashSet<Integer> col, int n, int r) {
        if (  r == n ) {
            printBoard(board);
            return;
        }

        for ( int c = 0 ; c < n ; c++) {
            if ( col.contains(c) || posDiag.contains(c + r) || negDiag.contains( r - c)  ) continue;
            posDiag.add(r + c);
            negDiag.add(r - c);
            col.add(c);
            board[r][c] = 'Q';
            backtrack(board, posDiag, negDiag, col, n, r + 1);
            posDiag.remove(r + c);
            negDiag.remove(r - c);
            col.remove(c);
            board[r][c] = '.';
        }

    }
    public static void main(String[] args) {
        solveNQueen(4);
    }    
}
