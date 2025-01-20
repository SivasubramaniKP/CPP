#include <iostream>
#include <vector>
class Graph {
    public:
        int nEdges;
        int nVertices;
        std::vector<std::vector<int>> Matrix;
    Graph ( int V ) {
        nVertices = V;
        Matrix.resize(nVertices, std::vector<int>(nVertices, 0));
    }
    
};