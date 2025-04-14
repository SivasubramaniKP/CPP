package Model_2.Shortest.FW;

import java.net.Inet4Address;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.ThreadPoolExecutor.DiscardOldestPolicy;

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
        int [][] dist = new int[nV][nV];
        for ( int i = 0 ; i < nV; i++ ) {
            for ( int j = 0 ; j < nV; j++ ) {
                if ( i == j ) dist[i][j] = 0;
                else dist[i][j] = Integer.MAX_VALUE;
            }
        }

        for ( Edge e : List ) {
            dist[e.source][e.destination] = e.weight;
        }

        for ( int k = 0 ; k < nV; k++ ) {
            for( int i = 0; i < nV; i++ ) {
                for ( int  j = 0 ; j < nV; j++ ) {
                    if ( dist[i][k] != Integer.MAX_VALUE && dist[k][j] != Integer.MAX_VALUE ) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    } 
                }
            }
        }
        printMatrix(dist);
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