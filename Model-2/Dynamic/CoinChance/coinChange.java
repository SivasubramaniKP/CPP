package CoinChance;

import java.util.ArrayList;
import java.util.Scanner;

import Backtracking.nQueens;

public class coinChange {
    
    static void printMatrix(int [][] Matrix, int I, int J) {
        for ( int i = 0; i < I ; i++ ) {
            for ( int j = 0 ; j < J; j++ ) {
                System.out.print(Matrix[i][j] + " ");
            }    
            System.out.println();
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int target = sc.nextInt();
        int nD = sc.nextInt();
        int denom[] = new int[nD];
        for ( int i = 0; i < nD; i++ ) {
            denom[i] = sc.nextInt();
        }
        int DP[][] = new int[nD+1][target + 1];
        for ( int i = 0; i <= nD; i++ ) {
            for ( int  j = 0; j <= target; j++ ) {
                if ( i == 0 ) DP[i][j] = Integer.MAX_VALUE;
                if ( j == 0 ) DP[i][j] = 0;
            }    
        } 

        for ( int i = 1; i <= nD; i++ ) {
            for ( int j = 1; j <= target; j++ ) {
                if ( j - denom[i - 1] < 0 ) {
                    DP[i][j] = DP[i-1][j];
                } else {
                    DP[i][j] = Math.min(DP[i-1][j], 1 + DP[i][j - denom[i - 1]]);
                }
            }
        }

        printMatrix(DP, nD + 1, target + 1);

        ArrayList<Integer> coinsUsed = new ArrayList<>();
        int i = nD;
        int j  = target;
        while ( i > 0 && j > 0 ) {
            if ( i >= 0 && DP[i-1][j] == DP[i][j] ) {
                i -= 1;
            } else {
                coinsUsed.add(denom[i - 1]);
                j -= denom[i - 1];
            }
        }

        for ( int coin : coinsUsed ) {
            System.out.println(coin);
        }
}
}
