package Model_2.DP.Mat;

import java.util.ArrayList;
import java.util.Scanner;

class Diagonal  {
    int i;
    int j;
    Diagonal ( int i, int j ) {
        this.i = i;
        this.j = j;
    }  
}

public class matrixChain {
    int dim[];
    int DP[][];
    int Ktable[][];

    int n;
    Scanner sc = new Scanner(System.in);
    matrixChain(int n) {
        this.n = n;
        dim = new int[n];
        DP = new int[n][n];
        Ktable = new int[n][n];
        for ( int i = 0 ; i < n; i++ ) {
            dim[i] = sc.nextInt();
        }
        for ( int i = 0 ; i < n - 1; i++) {
            for ( int j = 0 ; j < n - 1; j++ ) {
                if ( i > j ) {
                    DP[i][j] = Integer.MAX_VALUE;
                    Ktable[i][j] = Integer.MAX_VALUE;
                } else if ( i == j ) {
                    DP[i][j] = 0;
                    Ktable[i][j] = 0;
                }
            }
        }
    }

    ArrayList<Diagonal> generateDiagonals( int k ) {
        ArrayList<Diagonal> res = new ArrayList<>();    

        for ( int i = 0; i < n; i++ ) {
            for ( int j = 0 ; j < n; j++ ) {
                if ( i != 0 && j != 0 && j - i == k ) res.add(new Diagonal(i, j));
            }
        }
        return res;
    } 

    // int solveMatrixChain() {
    //     for ( int t = 1; t < n - 1; t++ ) {
    //         ArrayList<Diagonal> givenDiagonal = generateDiagonals(t);
    //         for ( Diagonal d : givenDiagonal ) {
    //             int i = d.i;
    //             int j = d.j;
    //             int minCost = Integer.MAX_VALUE;
    //                 int minK = -1;
    //                 for ( int k = i; k < j; k++ ) {
    //                     int cost = DP[i][k] + DP[k + 1][j] + dim[i] * dim[k + 1] * dim[j + 1];
    //                     if (cost < minCost) {
    //                         minCost = cost;
    //                         minK = k;
    //                     }
    //                 }
    //                 Ktable[i][j] = minK;
    //                 DP[i][j] = minCost;
    //         }
    //     }
    //     return DP[0][n-1];
    // }
int solveMatrixChain() {
        // Fill DP table and initialize Ktable
        for (int i = 0; i < n; i++) {
            DP[i][i] = 0;  // No cost for multiplying one matrix
        }

        // Solve using diagonal-based dynamic programming
        for (int t = 1; t < n - 1; t++) { // t is the diagonal offset
            ArrayList<Diagonal> givenDiagonal = generateDiagonals(t);
            for (Diagonal d : givenDiagonal) {
                int i = d.i;
                int j = d.j;
                int minCost = Integer.MAX_VALUE;
                int minK = -1;

                // Find the optimal k to split the matrices at
                for (int k = i; k < j; k++) {
                    // Corrected cost formula (dim[i] * dim[k + 1] * dim[j + 1])
                    int cost = DP[i][k] + DP[k + 1][j] + dim[i] * dim[k + 1] * dim[j + 1];
                    if (cost < minCost) {
                        minCost = cost;
                        minK = k;
                    }
                }

                // Store the result in DP and the split point in Ktable
                DP[i][j] = minCost;
                Ktable[i][j] = minK;
            }
        }

        // Return the minimum cost for multiplying the entire matrix chain
        return DP[0][n - 1];
    }
    public static void main(String[] args) {
        matrixChain sol = new matrixChain(5);
        System.out.println(sol.solveMatrixChain());
    }



}
