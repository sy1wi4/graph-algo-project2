#include <iostream>
#include <vector>

using namespace std;

struct Edge{
    int v;
};

struct Graph{
    int size;
    vector<Edge*> *adj_list;
};

void add_edge(Graph *g, int u, int v){
    Edge* edge = new Edge;
    edge->v = v;
    (*g).adj_list[u].push_back(edge);
}



Graph init_graph(int size){
    Graph g{};
    g.size = size;
    g.adj_list = new vector<Edge*>[size];
    return g;
}


void printGraph(Graph* g){
    for(int i=0; i<g->size; i++){
        cout << i + 1 << ": ";
        for(auto & j : g->adj_list[i]){
            cout<< j -> v + 1 << " ";
        }
        cout << endl;
    }
    cout << endl;
}



int main() {
    int T;  //games
    cin >> T;

    int vertices, edges;
    for (int t = 0; t < T; t++){
        cin >> vertices >> edges;
        Graph g = init_graph(vertices);
        for (int e = 0; e < edges; e++){
            int u, v;
            cin >> u >> v;
            add_edge(&g, u - 1, v - 1);
            add_edge(&g, v - 1, u - 1);
        }
        printGraph(&g);
    }
}

/*
    1
    5 5
    1 2
    2 3
    3 4
    3 5
    2 5
 */
