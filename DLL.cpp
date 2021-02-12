#include <iostream>

using namespace std;

struct Node{
    int value;
    struct Node* prev;
    struct Node* next;
};

class DoublyLinkedlist{
    Node* head;
    Node* tail;
    public:
    DoublyLinkedlist(){
        head = nullptr;
        tail = nullptr;
    }

    void insert_front(int);
    void insert_end(int);
    void insert_before(Node*, int);
    void insert_after(Node*, int);
    void delete_node(Node*);
    void print_DLL();

};

void DoublyLinkedlist::insert_front(int value){
    Node* new_node = new Node();
    new_node->value = value;
    new_node->next = head;
    if (head == nullptr) tail = new_node;
    else head->prev = new_node;
    head = new_node;
}

void DoublyLinkedlist::insert_end(int value) {
    Node* new_node = new Node();
    new_node->value = value;
    new_node->prev = tail;
    if (head == nullptr) head = new_node;
    else tail->next = new_node;
    tail = new_node;
}

void DoublyLinkedlist::insert_before(Node* node, int value) {
    Node* new_node = new Node();
    new_node->value = value;
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev = new_node;
    if (node->prev == nullptr){
        head = new_node;
    }
}

void DoublyLinkedlist::insert_after(Node* node, int value) {
    Node* new_node = new Node();
    new_node->value = value;
    new_node->prev = node;
    new_node->next = node->next;
    node->next = new_node;
    if (node->next == nullptr){
        tail = new_node;
    }
}

void DoublyLinkedlist::print_DLL() {
    Node* current = head;
    while(current != nullptr){
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
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
    delete(node);
}

int main() {
  auto* dll = new DoublyLinkedlist();
    dll->insert_end(1);
    dll->insert_end(2);
    dll->insert_end(6);
    dll->insert_end(8);
    dll->insert_end(12);
    dll->insert_front(-2);
    dll->print_DLL();
}
