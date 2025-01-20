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
        Graph(int nVertices) {
                this->nVertices = nVertices;
                list.resize(nVertices);
        }
        void inputGraph() {
                int nEdges;
                std::cout << "Enter the number of edges pls" << std::endl;
                std::cin >> this->nEdges;
                std::cout << "Enter the edge in this format" << std::endl;
                for ( int i = 0 ; i < this->nEdges; i++ ) {
                        int u, v;
                        std::cin >> u >> v;
                        list[u - 1].push_back(v - 1);
                        list[v - 1].push_back(u - 1);
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
        std::vector<std::vector<int>> BFS ( int start ) {
                std::vector<bool> visited(nVertices, false);
                std::queue<int> q;
                
               std::vector<std::vector<int>> levels;
               visited[start] = true;
               q.push(start);

               while (!q.empty()) {
                int levelSize = q.size();
                std::vector<int> level;
                
                for ( int i = 0; i < levelSize; i++ ) {
                        int node = q.front();

                        q.pop();
                        level.push_back(node);
                        for ( int neighbour : list[node] ) {
                                if ( !visited[neighbour] ) {
                                        visited[neighbour] = true;
                                        q.push(neighbour);

                                }
                        }
                }
                levels.push_back(level);
               }
                return levels;
        }
};

void printLevels ( std::vector<std::vector<int>> Levels ) {
        for ( std::vector<int> rows : Levels ) {
                std::cout << "[ ";
                for ( int items : rows ) {
                        std:: cout << items + 1 << ", ";
                }
                std::cout << "]\n"; 
        }
} 

int main () {
        int nV;
        std::cin >> nV;
        Graph graph(nV);
        graph.inputGraph();
        graph.displayGraph();
        std::vector<std::vector<int>> levels = graph.BFS(1);
        printLevels(levels);
        return 0;
}
