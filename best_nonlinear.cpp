#include <iostream>
#include <vector>
#include <list>


using namespace std;

struct Graph{
    int size;
    int** matrix;
};

void add_edge(Graph *g, int u, int v){
    g->matrix[u][v] = 1;
    g->matrix[v][u] = 1;
}

Graph init_graph(int size){
    Graph g{};
    g.size = size;
    g.matrix = new int* [size];
    for (int i = 0; i < size; i++){
        g.matrix[i] = new int [size];
        for(int j = 0; j < size; j++) g.matrix[i][j] = 0;
    }
    return g;
}


int* lexBFS(Graph* g){
    int* visit_order = new int[g->size];
    list<int> v_set;
    for (int v = 0; v < g->size; v++){
        v_set.push_back(v);
    }

    list<list<int>> L;
    L.push_back(v_set);

    list<int> last_set;
    int v;
    int order = 1;

    for (int i = 0; i < g->size; i++) {

        last_set = L.back();
        v = last_set.front();
        L.back().pop_front();

        if (last_set.empty()) {
            L.pop_back();
        }

        visit_order[v] = order;
        order++;

        // update v_sets
        list<list<int>> new_L;
        for (auto &it : L) {
            list<int> connected;
            list<int> not_connected;
            for (int &it2 : it) {
                if (g->matrix[v][it2] == 1) connected.push_back(it2);
                else not_connected.push_back(it2);
            }
            if (not not_connected.empty())
                new_L.push_back(not_connected);
            if (not connected.empty())
                new_L.push_back(connected);
        }
        L = new_L;
    }

    return visit_order;
}

int max_clique(Graph* g){
    int* visit_order;
    visit_order = lexBFS(g);

    int max_clique = 1;
    int current_clique;

    int index;
    for (int v = 0; v < g->size; v++){
        current_clique = 1;
        index = visit_order[v];

        for (int i = 0; i < g->size; i++) {
            if (g->matrix[v][i] == 1) {
                int ngh = i;
                if (visit_order[ngh] < index) {
                    current_clique++;
                }
            }
        }
        max_clique = max(max_clique, current_clique);
    }

    return max_clique;
}


int kings_blockade(Graph* g){
    return max(max_clique(g) - 1, 2);
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
        cout << kings_blockade(&g) << endl;
    }
}

