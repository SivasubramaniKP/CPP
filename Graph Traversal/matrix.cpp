#include<iostream>
#include <ostream>
#include <vector>
#include "vector"
#include <queue>
class Graph {
        public:
                std::vector<std::vector<int>> Matrix;
                int nVertices;
                int nEdges;
        Graph(int nVertices, int NEdges) {
                this->nVertices = nVertices;
                this->nEdges = NEdges;
                Matrix.resize(nVertices);
                for ( int i = 0 ; i < nVertices; i++ ) {
                    Matrix[i].resize(nVertices, 0);
                }
        }
        void inputGraph() {
                std::cout << "Enter the edge in this format" << std::endl;
                for ( int i = 0 ; i < this->nEdges; i++ ) {
                        int u, v;
                        std::cin >> u >> v;
                        Matrix[u-1][v-1] = 1;
                        // Matrix[v-1][u-1] = 1;
                        // list[u - 1].push_back(v - 1);
                        //list[v - 1].push_back(u - 1);
                }
        }
        void displayGraph () {
                for ( int i = 0; i < nVertices; i++ ) {
                        std::cout << i << ":";
                        for ( int j : Matrix[i] ) {
                                std::cout << j << " ";
                        }
                        std::cout << "\n";
                }  
        }
        std::vector<int> inDegree() {
                std::vector<int> res(nVertices, 0);
                for ( int i = 0; i < nVertices; i++ ) {
                    for ( int j = 0 ; j < nVertices; j++) {
                        if ( Matrix[i][j] == 1 ) {
                            res[j]++;
                        }
                    }
                }
                return res;
        }

        std::vector<int> outDegree() {
                std::vector<int> res(nVertices, 0);
                for ( int i = 0; i < nVertices; i++ ) {
                    for ( int j = 0 ; j < nVertices; j++) {
                        if ( Matrix[i][j] == 1 ) {
                            res[i]++;
                        }
                    }
                }
                return res;
        }
        
};

void printList(std::vector<int> list)  {
        for ( int i = 0 ; i < list.size(); i++ ) {
                std::cout << i << ": " << list[i] << "\n";
        }
}

int main () {

        int nE, nV;
        std::cout << "Input the graph\n";
        std::cout << "Enter the number of vertices";
        std::cin >> nV;
        std::cout << "Enter the number of edges";
        std::cin >> nE;

        Graph * graph = new Graph(nV, nE);
        graph->inputGraph();
        std::cout << "Enter 1 to find the Indegree 2 to find the outdegree 3 to print the adjecency list";
        int ch;
        std::cin >> ch;
        while ( true ) {
                switch(ch) {
                        case 1:{
                                printList(graph->inDegree());
                                break;
                        }
                        case 2:{
                                printList(graph->outDegree());
                                break;
                        } case 3:{ 
                                graph->displayGraph();
                                break;
                        }
                }

                std::cout << "Enter 1 to find the Indegree 2 to find the outdegree 3 to print the adjecency list";
                std::cin >> ch;
        }
        return 0;
}