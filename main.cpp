#include <iostream>
#include <vector>
#include <list>
#include <climits>


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


void print_graph(Graph* g){
    for(int i=0; i<g->size; i++){
        cout << i + 1 << ": ";
        for(auto & j : g->adj_list[i]){
            cout<< j -> v + 1 << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print_arr(int *arr, int size){

    cout << "Arr ";
    for (int i=0; i<size; i++){
        cout  << arr[i]  << " ";
    }
    cout << endl;
}

void print_list_of_lists(list<list<int>> L){
    cout << "Sets ";
    for (auto & it : L){
        cout << "{ ";
        for (int & it2 : it){
            cout << it2 + 1 << " ";
        }
        cout << "} ";
    }
    cout << endl;
}


// check if v is neighbour of u
bool is_ngh(Graph* g, int u, int v) {
    for (auto & j : g->adj_list[u]) {
        if (j->v == v) return true;
    }
    return false;
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
//        print_list_of_lists(L);

        last_set = L.back();
        v = last_set.front();
//        cout << v + 1 << endl;
        L.back().pop_front();

        if (last_set.empty()) {
            L.pop_back();
        }

        visit_order[v] = order;
        order++;

        // update v_sets  -> TODO: faster
        list<list<int>> new_L;
        for (auto &it : L) {
            list<int> connected;
            list<int> not_connected;
            for (int &it2 : it) {
                if (is_ngh(g, v, it2)) connected.push_back(it2);
                else not_connected.push_back(it2);
            }
            if (not not_connected.empty())
                new_L.push_back(not_connected);
            if (not connected.empty())
                new_L.push_back(connected);
        }
        L = new_L;
//        cout << endl;
    }
//    print_list_of_lists(L);

    return visit_order;

}

int max_clique(Graph* g){
    int* visit_order = new int[g->size];
    visit_order = lexBFS(g);
//    print_arr(visit_order, g->size);
    vector<list<int>> RNs(g->size);

//    list<list<int>> RNs;

    int max_clique = 1;
    int current_clique;

    int index;
    for (int v = 0; v < g->size; v++){
        current_clique = 1;
//        cout << "v " << v + 1<< endl;
        index = visit_order[v];
//        cout << v << " " << index << endl;
        for (auto & j : g->adj_list[v]) {
            int ngh = j->v;
//            cout << "ngh " << ngh + 1 << endl;
            if (visit_order[ngh] < index){
                RNs[v].push_back(ngh);
//                cout << "dodaj " << ngh + 1 << endl;
                current_clique++;
            }
        }
        max_clique = max(max_clique, current_clique);
//        cout << endl << endl;
    }
//    cout << endl;

//    cout << "MAX CLIQUE: " << max_clique << endl;
//     print RNs
//    for(int i=0; i<g->size; i++){
//        cout << i + 1 << ": ";
//        for (auto & it : RNs[i]){
//            cout << it + 1 << " ";
//        }
//        cout << endl;
//    }

    return max_clique;
}


int kings_blockade(Graph* g){
    return max(max_clique(g) - 1, 2);
}


int main() {
//    int size = 5;
//    int edges = 5;
//    // 1 2 1 3 1 4 2 3 2 4 3 4
//    // franklin:   1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 10 10 11 11 12 12 1 1 8 2 7 3 10 4 9 5 12 6 11
//    // interval-rnd6:   1 2 1 3 1 5 2 3 2 4 2 5 2 6 3 4 3 6 4 6
//    // chain: 1 2 2 3  ||  1 2 2 3 3 4 4 5 5 6
//    // proj: 5 5 1 2 2 3 3 4 3 5 2 5
//
//    Graph g = init_graph(size);
//    for (int e = 0; e < edges; e++){
//        int u, v;
//            cin >> u >> v;
//            add_edge(&g, u - 1, v - 1);
//            add_edge(&g, v - 1, u - 1);
//    }
//
//    print_graph(&g);
//
//    cout << "KING'S PAWNS: " << kings_blockade(&g) << endl;

///////////////////////////////////////////////////////////////////////////
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
//        print_graph(&g);
        cout << kings_blockade(&g);
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
