package Final;
import java.util.*;

class Edge {
    int source;
    int destination;
    int weight;
    Edge( int source, int destination, int weight ) {
        this.source = source;
        this.weight = weight;
        this.destination = destination;
    }
}

class Graph {
    int nE;
    int nV;
    Scanner sc = new Scanner(System.in);
    ArrayList<Edge> List;
    Graph(int nE, int nV) {
        this.nE = nE;
        this.nV = nV;
        List = new ArrayList<>();
    }
    void inputGraph() {
        for ( int i = 0 ; i < nE; i++ ) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int w = sc.nextInt();
            List.add(new Edge(u, v, w));
        }
    }

    static void printMatrix(int a[][]) {
        for ( int i = 0; i < a.length; i++ ) {
            for ( int j = 0 ; j < a[i].length; j++ ) {
                if ( a[i][j] == Integer.MAX_VALUE ) System.out.print("INF ");
                else System.out.print(a[i][j] + " ");
            }
            System.out.println();
        }
    }

    void solveFloydWarshall() {
        int W[][] = new int[nV][nV];
        for ( int i = 0 ; i < nV; i++ ) {
            for ( int j = 0 ; j < nV; j++ ) {
                W[i][j] = Integer.MAX_VALUE;
                if ( i == j ) W[i][j] = 0;
            }
        }
        for ( Edge e : List ) {
            W[e.source][e.destination] = e.weight;    
        }
        for ( int k = 0; k < nV; k++ ) {
            for ( int i = 0; i < nV; i++ ) {
                for (int j = 0 ; j < nV; j++ ) {
                    if ( W[i][k] != Integer.MAX_VALUE && W[k][j] != Integer.MAX_VALUE ) {
                        W[i][j] = Math.min(W[i][j], W[i][k] + W[k][j]);
                    }
                }
            }
        }
        printMatrix(W);
    }

}

public class floyd {
    public static void main(String[] args) {
        Graph graph = new Graph(10, 5);
        graph.inputGraph();
        graph.solveFloydWarshall();
    }
}