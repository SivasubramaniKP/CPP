package Model_2.Shortest.Bellman;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.*;
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
    int [] Parent;
    int nV;
    ArrayList<Edge> List;
    Scanner sc = new Scanner(System.in)    ;
    Graph(int nE, int nV) {
        List = new ArrayList<>();
        this.nE = nE;
        this.nV = nV;
        Parent = new int[nV];
        Arrays.fill(Parent, -1);
    }


    void inputGraph() {
        for(int i = 0 ; i < nE; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int w = sc.nextInt();
            List.add(new Edge(u, v, w));
        }
    }

    ArrayList<Integer> constructPath(int source, int destination) {
        ArrayList<Integer> path = new ArrayList<>();
        if (Parent[destination] == -1 && destination != source) {
            return path; // No path exists
        }
        
        // Backtrack from destination to source
        for (int v = destination; v != -1; v = Parent[v]) {
            path.add(v);
            if (v == source) break;
        }
        
        // Reverse to get source to destination order
        Collections.reverse(path);
        return path;
    }

    void BellmanFord(int source) {
        int Dist[] = new int[nV];
        for ( int i = 0 ; i < nV ; i++ ) Dist[i] = Integer.MAX_VALUE;
        Dist[source] = 0;
        for ( int i = 0; i < nV - 1; i++ ) {
            for ( Edge e : List ) {
                if ( Dist[e.source] != Integer.MAX_VALUE && Dist[e.destination] > Dist[e.source] + e.weight ) {
                    Dist[e.destination] = Dist[e.source] + e.weight;
                    Parent[e.destination] = e.source;
                }
            }
            System.out.println();
        }

         System.out.println("\nShortest paths from source " + source + ":");
        for (int i = 0; i < nV; i++) {
            if (i == source) continue;
            
            ArrayList<Integer> path = constructPath(source, i);
            if (path.isEmpty()) {
                System.out.println("No path from " + source + " to " + i);
            } else {
                System.out.print("Path to " + i + ": ");
                for (int j = 0; j < path.size(); j++) {
                    System.out.print(path.get(j));
                    if (j < path.size() - 1) System.out.print(" -> ");
                }
                System.out.println(" (Distance: " + 
                    (Dist[i] == Integer.MAX_VALUE ? "∞" : Dist[i]) + ")");
            }
        }
    } 


    public static void main(String[] args) {    
        Graph graph = new Graph(5, 5);
        graph.inputGraph();
        graph.BellmanFord(0);
    }
}
