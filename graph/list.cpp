#include<iostream>
#include <ostream>
#include <vector>
#include "vector"
#include <queue>
class Graph {
        public:
                std::vector<std::vector<int>> list;
                int nVertices;
                int nEdges;
        Graph(int nVertices, int NEdges) {
                this->nVertices = nVertices;
                this->nEdges = NEdges;
                list.resize(nVertices);
        }
        void inputGraph() {
                std::cout << "Enter the edge in this format" << std::endl;
                for ( int i = 0 ; i < this->nEdges; i++ ) {
                        int u, v;
                        std::cin >> u >> v;
                        list[u - 1].push_back(v - 1);
                        //list[v - 1].push_back(u - 1);
                }
        }
        void displayGraph () {
                for ( int i = 0; i < nVertices; i++ ) {
                        std::cout << i << ":";
                        for ( int j : list[i] ) {
                                std::cout << j << " ";
                        }
                        std::cout << "\n";
                }  
        }
        std::vector<int> inDegree() {
                std::vector<int> res(nVertices, 0);
                for ( int i = 0 ; i < nVertices; i++ ) {
                        for ( std::vector<int> v : list ) {
                                for ( int neighbours : v ) {
                                        if ( neighbours == i ) res[i]++;
                                }
                        }
                }
                return res;
        }

        std::vector<int> outDegree() {
                std::vector<int> res(nVertices, 0);
                for ( int i = 0 ; i < nVertices; i++ ) {
                        res[i] = list[i].size();
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
