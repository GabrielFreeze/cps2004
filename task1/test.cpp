#include <iostream>
#include <memory>
#include <vector>

using namespace std;

//Directed Acyclic Graph Node
typedef struct Node {
    int data;
} Node;

using NodePtr = std::shared_ptr<std::unique_ptr<Node>>;

typedef struct Edge {
    NodePtr from;
    NodePtr to;
} Edge;

typedef struct Graph {
    unique_ptr<Edge> e1;

} Graph;


int main() {


    NodePtr node1(new unique_ptr<Node>(new Node{1}));
    NodePtr node2(new unique_ptr<Node>(new Node{2}));
    NodePtr node3(new unique_ptr<Node>(new Node{3}));
    

    unique_ptr<Edge> edge1(new Edge{node1, node2});
    unique_ptr<Edge> edge2(new Edge{node2, node3});
    unique_ptr<Edge> edge3(new Edge{node3, node1});


    cout << (*edge1->from)->data << endl;
    cout << (*edge3->to)->data << endl;

    Graph g = {move(edge1)};

    cout << (*edge2->to)->data << endl; //Displays as we have not transfered the ownership of node3 to g
    cout << (*edge2->from)->data << endl; //Causes SEGV as we have transfered the ownership of node2 to g



    // Edge edge1 = {move(node1), move(node2)};
    // Edge edge2 = {move(node2), move(node3)};


    //Dag* dag = new Dag();



    return 0;
}


