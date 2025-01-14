#include <iostream>

class Graph {
    public:
        int E;
        int V;
        int ** Matrix;
    Graph () {
        std::cout << "Enter the number of vertices in the graph";
        std::cin >> this->V;
        std::cout << "Enter the number of edges in the graph";
        std::cin >> this->E;
        int nEdges = 0;
        this->Matrix = ( int ** )malloc( sizeof(int *) * this->V );
        for ( int i = 0; i < this->V; i++ ) {
            this->Matrix[i] = ( int * )malloc( sizeof(int) * this->V );
        }
        std::cout << "Enter the edges in this format <vertex1 vertex2>";
        while( nEdges < this->E ) {
            int v1, v2;
            std::cin >> v1 >> v2;
            nEdges++;
        }
        
    }
};