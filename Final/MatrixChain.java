package Final;

public class MatrixChain {
    
    static void Paranthesize (int i,int j, int split[][], char[] A) {
        if (i==j) {
            System.out.print(A[0]);
            A[0]++;
            return;
        }
        System.out.print("(");
        Paranthesize(i, split[i][j], split, A);
        Paranthesize(split[i][j] + 1, j, split, A);
        System.out.print(")");
    }

    static int solveMatrixChain(int dims[], int split[][]) {
        int n = dims.length - 1;
        int [][] DP = new int[n][n];
        for( int len = 2; len <= n; len++ ) 
        {
            for ( int i = 0 ; i <= n - len; i++ ) {
                int j = i + len - 1;
                DP[i][j] = Integer.MAX_VALUE;
                for ( int k = i; k < j; k++ ) {
                    int cost = DP[i][k] + DP[k+1][j] + dims[i] * dims[k+1] * dims[j+1];
                    if ( cost < DP[i][j] ) {
                        DP[i][j] = cost;
                        split[i][j] = k;
                    }
                } 
            }
        }
        return DP[0][n-1];
    } 
    public static void main(String[] args) {
        int dims[] = {4, 10, 3, 12, 20,7};
        int split[][] = new int[dims.length][dims.length];
        System.out.println("Cost : " + solveMatrixChain(dims, split));
        Paranthesize(0, dims.length - 2, split, new char[]{'A'});
    }
}
