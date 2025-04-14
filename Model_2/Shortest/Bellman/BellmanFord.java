package Model_2.Shortest.Bellman;

import java.security.IdentityScope;
import java.util.ArrayList;
import java.util.Scanner;

class Edge {
    int source;
    int destination;
    int weight;

    Edge(int source, int destination, int weight) {
        this.source = source;
        this.destination = destination;
        this.weight = weight;
    }
}

class Graph {
    int nE;
    ArrayList<Integer> Parent;
    int nV;
    ArrayList<Edge> List;
    Scanner sc = new Scanner(System.in)    ;
    Graph(int nE, int nV) {
        List = new ArrayList<>();
        Parent = new ArrayList<>();
        this.nE = nE;
        this.nV = nV;
        for( int i =0 ; i < nV; i++ ) {
            Parent.add(-1);
        }
    }


    void inputGraph() {
        for(int i = 0 ; i < nE; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int w = sc.nextInt();
            List.add(new Edge(u, v, w));
        }
    }

    void BellmanFord(int source) {
        int Dist[] = new int[nV];
        for ( int i = 0 ; i < nV ; i++ ) Dist[i] = Integer.MAX_VALUE;
        Dist[source] = 0;
        for ( int i = 0; i < nV - 1; i++ ) {
            for ( Edge e : List ) {
                if ( Dist[e.source] != Integer.MAX_VALUE && Dist[e.destination] > Dist[e.source] + e.weight ) {
                    Dist[e.destination] = Dist[e.source] + e.weight;
                    Parent.set(e.destination, e.source);
                }
            }
            for( int temp = 0 ; temp < nV; temp ++ ) {
                System.out.print(Dist[temp] + "  "  + Parent.get(temp) + "\t");
            }
            System.out.println();
        }
    } 


    public static void main(String[] args) {    
        Graph graph = new Graph(5, 5);
        graph.inputGraph();
        graph.BellmanFord(0);
    }
}
