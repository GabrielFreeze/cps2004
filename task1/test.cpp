// #include <iostream>
// #include <memory>
// #include <vector>

// using namespace std;

// //Directed Acyclic Graph Node
// typedef struct Node {
//     int data;
// } Node;


// typedef struct Edge {
//     Node& from;
//     Node& to;
// } Edge;

// typedef struct Graph {
//     unique_ptr<Node> node1;
//     unique_ptr<Node> node2;

// } Graph;


// int main() {

//     unique_ptr<Node> A(new Node{1});
//     unique_ptr<Node> B(new Node{2});
//     unique_ptr<Node> C(new Node{3});

//     Edge edge1 = {*A, *B};
//     Edge edge2 = {*B, *C};
//     Edge edge3 = {*C, *A};

//     cout << edge1.from.data << endl;
//     cout << edge1.to.data << endl;
//     cout << edge2.from.data << endl;
    
//     Graph dag = {move(edge1.from), move(edge1.t)};

//     cout << edge2.from.data << endl;
//     cout << edge1.from.data << endl;
//     cout << edge1.to.data << endl;

//     return 0;
// }


