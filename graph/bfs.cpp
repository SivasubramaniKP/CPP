#include <iostream>
#include <vector>
#include <queue>


class Graph {
    public:
    int nE; // Number of edges
    int nV; // Number of vertices

    std::vector<std::vector<int>> List; // Adjacency list representation of graph
    std::vector<int> Parent;
    std::vector<int> Distance;
    // Create a constructor for the grpah
    // The constructor gets an input of number of vertices and edges as arguement
    // and create adjacency list representation for the graph

    Graph ( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;

        // Lets input the edges and store it in the list
        List.resize(nV);
        
        std::cout << "Enter the edges in this format 'vertex1 vertex2'" << std::endl;
        // To denote an edge from vertex 1 to 5
        // input
        // 1 5             ---- 1 space 5
        //In this graph im indexing from 1
        for ( int i = 0 ; i < nE; i++ ) {
            int u,v;
            std::cin >> u >> v;
            if ( u > 0 && u <= nE && v > 0 && v <= nE ) {
                List[u-1].push_back(v-1);
                // Add the following line for undirected graph
                List[v-1].push_back(u-1);
                //This line suggests that the edge is bidirectional
            }
        } 
    }

    void BFS ( int Source ) {

        // This function updates the Parent and distance vectors
        // by following BFS traversal 
        // Starting at the Source Vertex

        Parent.resize(nV);
        Distance.resize(nV);

        // Resize the parent and distance vector to hold nV number of entries
        // for each vertex

        // Initialize the parent and distance vectors.

        for ( int i = 0; i < nV; i++ ) {
            Parent[i] = -1;          // Parent of each vertex is unknown
            Distance[i] = 2147483647; // We dont know the distance of the vertex from the Source vertex so the distance of each vertex be at infinite distance
        }

        // Distance of Source vertex is Zero 

        Distance[Source - 1] = 0;
        // Source - 1 because the indexing starts with 0

        std::queue<int> Q;
        // C++ comes with an inbuild Queue data structure
        // q.empty() returns an boolean whether the queue is empty or not ---- true : Queue is empty
        // q.push(10) : Enqueues 10 to the queue
        // q.pop() : Dequeue the queue
        // Q.front() : returns the element which is at the top of the queue
        // Enqueue the Source vertex to the Queue

        std::vector<int> Visited(nE);

        Q.push(Source - 1);
        while ( !Q.empty() ) {

            // Dequeue 
            int node = Q.front();
            Q.pop();

            // Mark the node as visited
            Visited[node] = 1;
            // Find the neighbouring vertex
            // To find the neighbouring vertices, traverse the node'th row of Adjacency list
            for ( int i = 0; i < List[node].size(); i++ ) {

                // If the vertex is unvisited 
                if ( Visited [List[node].at(i)] == 0 ) {
                        Q.push(List[node].at(i));
                        Parent[List[node].at(i)] = node;
                        Distance[List[node].at(i)] = 1 + Distance[node];
                }
            }              
            
        }

        std::cout << "\n\n";
        std::cout << "Parent Vector";
            for ( int i = 0 ; i < nV; i++ ) {
                std::cout << i + 1 << ": " << Parent[i] + 1<< std::endl;
            }
            std::cout << "\n\n Distances : \n";

            for ( int i = 0 ; i < nV; i++ ) {
                std::cout << i + 1 << ": " << Distance[i] << std::endl;
            } 

    } 

    void printAdjacencyList() {
        // Just a helper functiion to visualize the adjacency list

        for ( int i = 0 ; i < nV; i++ ) {
            std::cout <<  i+1 << ": ";
            for ( int j = 0 ; j < List[i].size(); j++ ) {
                std::cout << j+1 << ", ";
            }
            std::cout << "\n";
        }
    }    
};

int main () {
    Graph * graph = new Graph(6,10);
    graph->printAdjacencyList();
    graph->BFS(1);
    return 0;
}