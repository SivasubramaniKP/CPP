// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <queue>
// class Edge {
//     public:
//     int source;
//     int destination;
//     int Flow;
//     Edge (int source, int destination, int Flow) {
//         this->source = source;
//         this->destination = destination;
//         this->Flow = Flow;
//     }
// };
// typedef std::unordered_map<int, std::vector<Edge>>adjacencyList;
// typedef std::vector<int> Vector;
// class Graph {
//     public:
//     int nE;
//     int nV;
//     adjacencyList List;

//     Graph(int nE, int nV){
//         this->nE = nE;
//         this->nV = nV;
//         List.reserve(nV);
//     }

//     void inputgraph() {
//         for ( int i = 0 ; i < nV; i++ ) {
//             int u, v, w;
//             std::cin >> u >> v >> w;
//             List[u].push_back(Edge(u, v, w));
//         }
//     }

//     std::vector<int> BFSPath ( int source, int sink, std::vector<int> Visited ) {
        
//         std::vector<Edge> path;
//         std::queue<int> Q;
//         Q.push(source);
//         while ( !Q.empty() ) {
//             int node = Q.front(); Q.pop();
//             for ( Edge e : List[node] ) {
//                 if ( Visited[e.destination] == 0 && e. ) {
//                     path.push_back(e);
//                     Visited[e.destination] = 1;
//                 }
//             }
//         }  
//     } 
// };

// int main () {
//     Graph * graph = new Graph(4,4);
//     graph->inputgraph();
    
// }
