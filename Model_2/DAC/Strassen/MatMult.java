package Model_2.DAC.Strassen;

public class MatMult {
   static int[][] matrixAddition (int a[][], int b[][]) {
        int n = a.length;
        int c[][] = new int[n][n];
        for ( int i = 0 ; i < n; i++ ) {
            for ( int j = 0; j < n ;j++ ) {
                c[i][j] = a[i][j] + b[i][j];
            }
        }
        return c;
   } 

   static int [][] matrixAddition(int a[][], int b[][], int c[][]) {

        int n = a.length;
        int d[][] = new int[n][n];
        for ( int i = 0 ; i < n; i++ ) {
            for ( int j = 0; j < n ;j++ ) {
                d[i][j] = a[i][j] + b[i][j] + c[i][j];
            }
        }
        return d;
   }

   static int[][] matrixSubtraction(int a[][], int b[][]) {
        int n = a.length;
        int c[][] = new int[n][n];
        for ( int i = 0 ; i < n; i++ ) {
            for ( int j = 0; j < n ;j++ ) {
                c[i][j] = a[i][j] - b[i][j];
            }
        }
        return c;
    }


    static int[][] strassen(int a[][], int b[][]) {
        int n = a.length;
        int c[][] = new int[n][n];
        if ( n == 1 ) {
            c[0][0] = a[0][0] * b[0][0];
        } else {
            int newLen = n/2;
            int [][] A11 = new int[newLen][newLen];
            int [][] A12 = new int[newLen][newLen];
            int [][] A21 = new int[newLen][newLen];
            int [][] A22 = new int[newLen][newLen];

            int [][] B11 = new int[newLen][newLen];
            int [][] B12 = new int[newLen][newLen];
            int [][] B21 = new int[newLen][newLen];
            int [][] B22 = new int[newLen][newLen];

            for ( int i =0 ; i < newLen; i++ ) {
                for (int j = 0; j < newLen; j++) {
                    A11[i][j] = a[i][j];
                    A12[i][j] = a[i][newLen + j];
                    A21[i][j] = a[i + newLen][j];
                    A22[i][j] = a[i+newLen][j + newLen];

                    B11[i][j] = b[i][j];
                    B12[i][j] = b[i][newLen + j];
                    B21[i][j] = b[i + newLen][j];
                    B22[i][j] = b[i+newLen][j + newLen];
                }    
            } 
            int [][] P = strassen(matrixAddition(A11, A22), matrixAddition(B11, B22));
            int [][] Q = strassen(B11, matrixAddition(A21, A22));
            int [][] R = strassen(A11, matrixSubtraction(B12, B22));
            int [][] S = strassen(A22, matrixSubtraction(B21, B11));
            int [][] T = strassen(B22, matrixAddition(A11, A12));
            int [][] U = strassen(matrixSubtraction(A21, A11), matrixAddition(B11, B12));
            int [][] V = strassen(matrixAddition(B21, B22), matrixSubtraction(A12, A22));

            int [][] C11 = matrixSubtraction(matrixAddition(P,S,V), T);
            int [][] C12 = matrixAddition(R, T);
            int [][] C21 = matrixAddition(Q, S);
            int [][] C22 = matrixSubtraction(matrixAddition(P, R, U), Q);
            
            for ( int i = 0; i < newLen; i++ ) {
                for ( int j = 0; j < newLen; j++ ) {
                    c[i][j] = C11[i][j];
                    c[i][j + newLen] = C12[i][j];
                    c[i+newLen][j] = C21[i][j];
                    c[i+newLen][j+newLen] = C22[i][j];
                }
            }
        } 
        return c;
    }
    static void printMatrix(int[][] M) {
        for (int[] row : M) {
            for (int val : row)
                System.out.print(val + "\t");
            System.out.println();
        }
    }

    // Main
    public static void main(String[] args) {
        int[][] A = {
            {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, { 0, 0, 0, 0 }
        };

        int[][] B = {
            {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, { 0, 0, 0, 0 }
        };

        int[][] C = strassen(A, B);

        System.out.println("Product of A and B:");
        printMatrix(C);
        
    }
}
