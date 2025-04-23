#include <iostream>
#include <vector>
#include <queue>
#include <climits>
class Graph
{
public:
    int nE;
    int nV;
    std::vector<std::vector<int>> List;
    std::vector<int> Parent;
    std::vector<int> Distance;
    std::vector<int> Visited;
    Graph(int nE, int nV)
    {
        this->nE = nE;
        this->nV = nV;
        List.resize(nV);
        Parent.resize(nV, -1);
        Distance.resize(nV, INT_MAX);
        Visited.resize(nV, 0);
    }
    void inputGraph()
    {
        for (int i = 0; i < nE; i++)
        {
            int u, v;
            std::cin >> u >> v;
            List[u].push_back(v);
            List[v].push_back(u);
        }
    }
    void BFS()
    {
        for (int i = 0; i < nV; i++)
        {
            if (!Visited[i])
            {
                int SOURCE = i;
                std::queue<int> Q;
                Visited[i] = 1;
                Distance[i] = 0;
                Q.push(SOURCE);
                while (!Q.empty())
                {
                    int u = Q.front();
                    Q.pop();
                    for (int v : List[u])
                    {
                        if (!Visited[v])
                        {

                            Visited[v] = 1;
                            Distance[v] = 1 + Distance[u];
                            Parent[v] = u;
                            Q.push(v);
                        }
                    }
                }
            }
        }
    }
    void printDetail()
    {
        for (int i = 0; i < nV; i++)
        {
            std::cout << "Vertex  : " << i << "\n";
            std::cout << "Distance : " << Distance[i] << "\n";
            std::cout << "Parent : " << Parent[i] << "\n\n\n";
        }
    }

    void reset()
    {
        Parent.resize(nV, -1);
        Distance.resize(nV, -1);
        Visited.resize(nV, -1);
    }

    void BFS(int source)
    {
        reset();
        std::queue<int> Q;
        Visited[source] = 1;
        Distance[source] = 1;
        Q.push(source);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for (int v : List[u])
            {
                if (!Visited[v])
                {
                    Parent[v] = u;
                    Distance[v] = 1 + Distance[u];
                    Visited[v] = 1;
                    Q.push(v);
                }
            }
        }
    }

    void findShortestPath(int source, int destination)
    {
        BFS(source);
        int cur = destination;
        std::vector<int> path;
        for (int v = destination; v != source; v = Parent[v])
        {
            if (v == -1)
            {
                std::cout << "The vertex is unreachable\n";
                return;
            }
            path.push_back(v);
        }
        path.push_back(source);
        for (int i = path.size() - 1; i >= 0; i--)
        {
            std::cout << path[i] << " -> ";
        }
    }

    void DetectCycle()
    {
        reset();
        for (int i = 0; i < nV; i++)
        {
            if (!Visited[i])
            {
                Parent[i] = -1;
                Visited[i] = 1;
                std::queue<std::pair<int, int>> Q;
                Q.push({i, -1});
                while (!Q.empty())
                {
                    int node = Q.front().first;
                    int parent = Q.front().second;
                    Q.pop();
                    for (int v : List[node])
                    {
                        if (!Visited[v])
                        {
                            Visited[v] = 1;
                            Parent[v] = node;
                            Q.push({v, node});
                        }
                        else if (v != parent)
                        {
                            std::cout << "Cycle detected \n";
                            return;
                        }
                    }
                }
            }
        }
        std::cout << "No Cycles\n";
    }

    void printComponents() {
        std::vector<std::vector<int>> res;
        reset();
        for ( int i = 0 ; i < nV; i++ ) {
            if ( !Visited[i] ) {
                int SOURCE = i;
                std::vector<int> CurComponents;
                Visited[i] = 1;
                std::queue<int> Q;
                Q.push(SOURCE);
                while ( !Q.empty() ) {
                    int u = Q.front();
                    CurComponents.push_back(u);
                    Q.pop();
                    for ( int v : List[u] ) {
                        if ( !Visited[v] ) {
                            Visited[v] = 1;
                            Q.push(v);
                        }
                    }
                }
                res.push_back(CurComponents);
            }
        }
        std::cout << "NUmber of Components : "  << res.size() << "\n";
        for ( int i = 0 ; i < res.size(); i++ ) {
            std::cout << "Component  " << i + 1 << ": ";
            for ( int j = 0 ; j < res[i].size(); j++ ) {
                std::cout << res[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    int nE, nV;
    std::cin >> nE >> nV;
    Graph graph(nE, nV);
    graph.inputGraph();
    graph.printComponents();
    return 1;
}