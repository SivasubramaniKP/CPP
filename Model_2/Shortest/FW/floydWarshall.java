package Model_2.Shortest.FW;

import java.util.ArrayList;
import java.util.Scanner;

class Edge {
    int source;
    int destination;
    int weight;

    Edge(int source, int destination, int weight) {
        this.source = source;
        this.weight = weight;
        this.destination = destination;
    }
}

class Graph {
    int nE;
    int nV;
    ArrayList<Edge> List;
    Scanner sc = new Scanner(System.in);
    Graph(int nE, int nV) {
        this.nE = nE;
        this.nV = nV;
        List = new ArrayList<>();
    }

    void inputGraph () {
        for ( int i = 0 ; i < nE; i++ ) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int w = sc.nextInt();
            List.add(new Edge(u, v, w));
        }
    }
    void printMatrix(int a[][]) {
        for ( int i = 0; i < a.length; i++ ) {
            for ( int j = 0 ; j < a[i].length; j++ ) {
                if ( a[i][j] == Integer.MAX_VALUE ) {
                    System.out.print("INF\t");
                } else {
                    System.out.print(a[i][j]+ "\t");
                }
            }
        }
    } 
    void floydWarshall () {
        int W[][][] = new int[nV][nV][nV];
        for ( int i = 0; i < nV; i++ ) {
            for( int j = 0; j < nV; j++ ) {
                W[0][i][j] = Integer.MAX_VALUE;    
                if ( i == j ) W[0][i][j] = 0;
            }
        }

        for ( Edge e : List ) {
            W[0][e.source][e.destination] = e.weight;    
        }
        printMatrix(W[0]);
        for ( int k = 1; k < nV; k++ ) {
            for ( int i = 0 ; i < nV; i++ ) {
                for ( int j = 0 ; j < nV; j++ ) {
                    if (W[k-1][i][k] != Integer.MAX_VALUE ||W[k-1][k][j] != Integer.MAX_VALUE ) {
                        W[k][i][j] = Math.min(W[k-1][i][j], W[k-1][i][k] + W[k-1][k][j]);
                    } else {
                        W[k][i][j] = W[k-1][i][j];
                    }
                }
            }
            printMatrix(W[k]);
        }
    }
}


public class floydWarshall {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int nE = sc.nextInt();
        int nV = sc.nextInt();
        Graph graph = new Graph(nE, nV);
        graph.inputGraph();
        graph.floydWarshall();

    }

}