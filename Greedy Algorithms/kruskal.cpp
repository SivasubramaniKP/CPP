#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <bits/stdc++.h>
class DisjointSet {
    public:
    std::vector<int> Parent;
    int nodes;
    DisjointSet(int nodes) {
        this->nodes = nodes;
        Parent.resize(nodes + 1);
        for ( int i = 0 ; i < nodes; i++ ) {
            Parent[i] = i;
        }
    }
    int find( int u ) {
        if ( Parent[u] != u ) {
            Parent[u] = find(Parent[u]);
        } 
         return Parent[u];
    }   
    void Union ( int u, int v ) {
        if ( find(u) != find(v) ) {
            Parent[find(v)] = u;
        }
    }
    void printParentArray() {
        for ( int i : Parent ) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
};

class Edge {
    public:
        int source;
        int destination;
        int weight;
        Edge(int source,int destination, int weight) {
            this->destination = destination;
            this->weight = weight;
            this->source = source;
        }
};
class Graph {
    public:
    int nE, nV;
    std::unordered_map<int, std::vector<Edge>> List;
    Graph ( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;
        List.reserve(nV);
    }
    void inputGraph() {
        int inputs = 0;
            std::cout << "Enter the edges in this format vertex 1 vertex 2 weight \n";
        while ( inputs < nE ) {
            int v1, v2, w;
            std::cin >> v1 >> v2 >> w;
            if ( v1 <= nV && v2 <= nV ){
                List[v1].emplace_back(v1, v2, w);
                List[v2].emplace_back(v2, v1, w);
                inputs++;
            } else {
                std::cout << "NOt a valid edge \n"; 
            }
       }
    }
    
    static bool customComparator(const Edge &e1, const Edge &e2) {
        return e1.weight < e2.weight;
    }   

      
    void Kruskal() {
        /*
            1. Sort the edges in ascending order;
            2. Choose the weight with least weight
            3. Add it to the tree
            4. Add the edges which does not form a cycle
                Defined in terms of Disjoint set as find[u] != find[v]
        */


        /*
            sort() function C++ STL
            sort () function takes 
                first arguement : beginning iterator of the container ( Usually <iterable>.begin() )
                second arguement : ending iterator ( <iterable>.end() )

                third arguemnt : 
                    Comparator function : to define custom ordering 
                    Takes in two arguements and return a boolean
                    
                    Consider the following lambda expression of the comparator function

                    If e1 wants to be places before e2 then the function should return true
                    Since we want to sort by weight
                    return true if e1 weight is lower

        */
        auto cmp = [](const Edge &e1, const Edge &e2) {
            return e1.weight < e2.weight;
        };
        
        // Copy the edges
        std::vector<Edge> Edges;
        for ( int i = 0 ; i <= nV; i++ ) {
            for ( Edge u : List[i] ) {
                Edges.push_back(u);
            }
        }

        std::sort(Edges.begin(), Edges.end(), customComparator);

        std::vector<Edge> result; // To store the Minimum Cost Spanning tree edges 
        int resWeight = 0; // Cost of MCST
        int nTreeEdge = 0; // nTreeEdges should be equal to nV - 1 for MCST
        int i = 0;
        DisjointSet * set = new DisjointSet(nV + 1); // Define a Disjoint set to detect cycles
        while ( nTreeEdge != nV - 1 ) {
            Edge temp = Edges[i++]; // Choose the edge with least weight

            // Vertex under the same component of Disjoint Set forms cycle
            // Ensure that source and destination is not in the same component
            if ( set->find(temp.source) != set->find(temp.destination) ) {
                result.push_back(temp); // Add the edge to the tree
                set->Union(temp.source, temp.destination); // Union operation to include the new vertex to the component
                resWeight += temp.weight;
                nTreeEdge++;
            }
        }
        for ( Edge i : result ) 
        {
            std::cout << "Edge : source : " << i.source << " Destination :  " << i.destination << " weight  : " << i.weight << std::endl; 
        }
        std::cout << "Cost of Tree : " << resWeight << std::endl;
    }

};

int main () {
    Graph * graph = new Graph(14,9);
    graph->inputGraph();
    graph->Kruskal();
}