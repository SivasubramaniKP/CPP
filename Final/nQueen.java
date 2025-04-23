package Final;
import java.util.*;

public class nQueen {
    
    static void printBoard(char [][] board) {
        for ( int i = 0 ; i < board.length; i++ ) {
            for( int j = 0 ; j < board.length; j++ ) {
                System.out.print(board[i][j] + "  ");
            }
            System.out.println();
        }
        System.out.println();
    }

    static List<List<String>> solveNQueen(int n) {
        List<List<String>> res = new ArrayList<>();
        char [][] board = new char[n][n];
        for ( int i =0 ; i < n; i++ ) Arrays.fill(board[i], '.');
        HashSet<Integer> col = new HashSet<>();
        HashSet<Integer> posDiag = new HashSet<>();
        HashSet<Integer> negDiag = new HashSet<>();
        backtrack(0, res, col, posDiag, negDiag, n, board);
        return res;
    }

    static void backtrack(int r,List<List<String>> res, HashSet<Integer> col,HashSet<Integer> posDiag,HashSet<Integer> negDiag, int n, char [][] board) {
        if ( r == n ) {
            printBoard(board);
            return;
        }
        for ( int c = 0 ; c < n ; c ++ ) {
            if ( col.contains(c) || posDiag.contains(r + c) || negDiag.contains(r - c) ) continue;
            col.add(c);
            posDiag.add(r + c);
            negDiag.add(r - c);
            board[r][c] = 'Q';
            backtrack(r + 1, res, col, posDiag, negDiag, n, board); 
            board[r][c] = '.';
            col.remove(c);
            posDiag.remove(r + c);
            negDiag.remove(r - c);
        }
    }

    // static List<String> ConstructBoard(char [][] board) {

    // }

    public static void main(String[] args) {
        solveNQueen(4);

    }
}
