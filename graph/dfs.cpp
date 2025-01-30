#include <iostream>
#include <vector>

class Graph {
    public:
    int nE; // Number of edges
    int nV; // Number of vertices

    private:
    std::vector<std::vector<int>> List; // Adjacency list representation of graph
    std::vector<int> Parent;
    std::vector<int> Distance;
    std::vector<int> Start;
    std::vector<int> Finish;
    std::vector<bool> Visited;
    int Time;
    // Create a constructor for the grpah
    // The constructor gets an input of number of vertices and edges as arguement
    // and create adjacency list representation for the graph
    public:
    Graph ( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;
        Parent.resize(nV, -1);
        Distance.resize(nV, 2147483647);
        Start.resize(nV, 0);
        Finish.resize(nV, 0);
        // Lets input the edges and store it in the list
        List.resize(nV);        
        Visited.resize(nV, 0);
        this->Time = 0;
        std::cout << "Enter the edges in this format 'vertex1 vertex2'" << std::endl;
        // To denote an edge from vertex 1 to 5
        // input
        // 1 5             ---- 1 space 5
        //In this graph im indexing from 1
        for ( int i = 0 ; i < nE; i++ ) {
            int u,v;
            std::cin >> u >> v;
            if ( u > 0 && u <= nV && v > 0 && v <= nV ) {
                List[u-1].push_back(v-1);
                // Add the following line for undirected graph
                // List[v-1].push_back(u-1);
                //This line suggests that the edge is bidirectional
            }
        } 
    }

    void DFS(int vertex) {
        Visited[vertex] = true;        
        Start[vertex] = Time++;
        for ( int i : List[vertex] ) {
            Parent[i] = vertex;
            Distance[i] = 1  + Distance[vertex];
            if ( !Visited[i] ) {
                DFS(i);
            }
        }
        Finish[vertex] = Time++;
    }
    
    void runDFS() {
        for ( int i = 0 ; i < nV; i++ ) {
            if( !Visited[i] ) {
                Parent[i] = -1;
                Distance[i] = 0;
                DFS(i);
            }
        }
    }

    void DisplayGraphInfo() {
        for ( int i = 0 ; i < nV; i++ ) {
            std::cout << "Vertex " << (i + 1) << std::endl;
            std::cout << "Parent : " << Parent[i] + 1 << std::endl;
            std::cout << "Distace : " << Distance[i] << std::endl;
            std::cout << "Neighbours : ";
            for ( int neighbours : List[i] ) {
                std::cout << neighbours + 1 << ", ";
            }
            std::cout << "\nstarting time : " << Start[i] << std::endl;
            std::cout << "Finishing time : " << Finish[i] << std::endl;
            std::cout << "\n\n";
        }
    }

    void CategoriseEdges() {
        runDFS();
        std::vector<std::pair<std::pair<int, int>, std::string>> Classifier;
        for ( int i = 0 ; i < nV; i++ ) {
            for ( int neighbour : List[i] ) {
                if ( Start[i] < Start[neighbour] && Finish[i] > Finish[neighbour] ) {
                    Classifier.push_back({{i,neighbour}, "tree edge"});
                } else if ( Start[i] > Start[neighbour] && Finish[neighbour] > Finish[i] ) {
                    Classifier.push_back({{i, neighbour}, "Backedge"});
                } else if ( Start[neighbour] < Start[i] ) {
                    Classifier.push_back({{i, neighbour}, "cross edge"});
                } else {
                    Classifier.push_back({{i, neighbour}, "Forward edge"});
                }
            }
        }
        for ( std::pair<std::pair<int,int>, std::string> i : Classifier ) {
             std::cout << i.first.first + 1 << "->" << i.first.second + 1 << " : " << i.second << std::endl;
        }
    }

};

int main () {
    Graph * graph = new Graph(6,4);
    graph->CategoriseEdges();
}