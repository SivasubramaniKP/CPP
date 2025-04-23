package Final.CAT_2;

public class MatrixChain {
    static int solveMatrixChain(int dims[] , int split[][]) {
        int n  = dims.length - 1;;
        int DP [][] = new int[n][n];
        for ( int len = 2; len <= n; len++ ) {
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

    static void printParanthesis(int [][] split, int i, int j, char[]name) {
        if ( i == j ) {
            System.out.print(name[0]);
            name[0]++;
            return;
        }
        System.out.print("(");
        printParanthesis(split, i, split[i][j], name);     
        printParanthesis(split, split[i][j] + 1, j, name);
        System.out.print(")");
    }
    public static void main(String[] args) {
        int [] dims = {5,6,4,2,3};
        int n = dims.length - 1;
        int split[][] = new int[n][n];
        solveMatrixChain(dims, split);
        printParanthesis(split, 0, n - 1, new char[]{'A'});
    }
}
