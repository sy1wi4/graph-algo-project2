#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Node{
    list<int> vertices;
    struct Node* prev;
    struct Node* next;

public:
    Node(){
        prev = nullptr;
        next = nullptr;
    }
    bool no_vertices() const;

};

bool Node::no_vertices() const {
    return vertices.empty();
}

class DoublyLinkedlist{
    Node* head;
    Node* tail;
public:
    DoublyLinkedlist(){
        head = nullptr;
        tail = nullptr;
    }

    Node* get_head();
    void insert_front(list<int>&);
    void insert_before(Node*, list<int>&);
    void delete_node(Node*);
    int get_v_from_last_set();
    static list<int>::iterator remove_ith(Node*, int);
};


Node *DoublyLinkedlist::get_head() {
    return head;
}


void DoublyLinkedlist::insert_front(list<int>& l){
    Node* new_node = new Node();
    new_node->vertices = l;
    new_node->next = head;
    if (head == nullptr) tail = new_node;
    else head->prev = new_node;
    head = new_node;
}


void DoublyLinkedlist::insert_before(Node* node, list<int>& l) {
    Node* new_node = new Node();
    new_node->vertices = std::move(l);
    new_node->next = node;
    new_node->prev = node->prev;
    if (node->prev == nullptr){
        head = new_node;
    }
    node->prev = new_node;
}




void DoublyLinkedlist::delete_node(Node* node) {
    if (node->prev == nullptr)
    {
        head = head->next;
        head->prev = nullptr;
    }

    else if (node->next == nullptr){
        tail = tail->prev;
        tail->next = nullptr;
    }

    else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);
}

int DoublyLinkedlist::get_v_from_last_set() {
    int v = tail->vertices.front();
    tail->vertices.pop_front();
    if (tail->vertices.empty()) {
        if (tail->prev != nullptr) delete_node(tail);
    }
    return v;
}


list<int>::iterator DoublyLinkedlist::remove_ith(Node* node, int idx) {
    auto it = node->vertices.begin();
    advance(it, idx);
    return node->vertices.erase(it);
}



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



// check if v is neighbour of u
bool is_ngh(Graph* g, int u, int v) {
    for (auto & j : g->adj_list[u]) {
        if (j->v == v) return true;
    }
    return false;
}


int* lexBFS(Graph* g){
    int* visit_order = new int[g->size];

    // initial set of all vertices
    list<int> v_set;
    for (int v = 0; v < g->size; v++){
        v_set.push_back(v);
    }

    auto* dll = new DoublyLinkedlist();
    dll->insert_front(v_set);

    list<int> last_set;
    int v;
    int order = 1;

    int visits = 0;
    for (int i = 0; i < g->size; i++) {
        v = dll->get_v_from_last_set();
        visit_order[v] = order;
        if (++visits == g->size) {
            free(dll);
            break;
        }
        order++;

        // update v_sets
        Node* current = dll->get_head();
        while (current != nullptr) {
            list<int> not_connected;
            int idx = 0;

            list<int>::iterator it;
            for (it = current->vertices.begin(); it != current->vertices.end(); it++) {
                if (! is_ngh(g, v, *it)) {
                    not_connected.push_back(*it);
                    // remove from current set
                    it = dll->remove_ith(current,idx);
                    it--;
                    idx--;
                }
                idx++;

            }
            if (not not_connected.empty()) {
                dll->insert_before(current, not_connected);
            }

            // remove current if is empty
            if (current->no_vertices()) {

                Node* tmp = current->next;
                dll->delete_node(current);
                current = tmp;
            }
            else current = current->next;
        }
    }

    return visit_order;

}

int max_clique(Graph* g){
    int* visit_order = new int[g->size];
    visit_order = lexBFS(g);


    int max_clique = 1;
    int current_clique;

    int index;
    for (int v = 0; v < g->size; v++){
        current_clique = 1;
        index = visit_order[v];
        for (auto & j : g->adj_list[v]) {
            int ngh = j->v;
            if (visit_order[ngh] < index){
                current_clique++;
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


