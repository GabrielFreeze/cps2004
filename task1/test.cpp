#include <iostream>
#include "dag.hpp"
using namespace std;


int main() {

    auto A = make_shared<Node<char>>('A'); 
    auto D = make_shared<Node<char>>('D');
    auto B = make_shared<Node<char>>('B'); 
    auto C = make_shared<Node<char>>('C'); 
    
    auto A_B = make_unique<Edge<char>>(Edge<char>{A, B});
    auto B_C = make_unique<Edge<char>>(Edge<char>{B, C});
    auto C_D = make_unique<Edge<char>>(Edge<char>{C, D});
    auto C_A = make_unique<Edge<char>>(Edge<char>{C, A});
    
    unique_ptr<Edge<char>> edges[2] = {move(A_B), move(B_C)};

    Dag<char> dag(edges, sizeof(edges)/sizeof(edges[0]));
    assert(dag.addNode(A) == 3);
    assert(dag.addNode(B) == 3);
    assert(dag.addNode(C) == 3);
    assert(dag.addNode(D) == 4);
    assert(dag.getNumNodes() == 4);

    assert(dag.getSuccessors(A)[0] == B);
    assert(dag.getSuccessors(dag.getSuccessors(A)[0])[0] == C);
    assert(dag.getSuccessors(C).empty());

    assert(dag.getNumEdges() == 2);
    assert(dag.addEdge(move(C_D)) == 3);
    assert(dag.getNumEdges() == 3);

    assert(!dag.getSuccessors(C).empty());
    assert(dag.getSuccessors(C)[0] == D);

    assert(dag.getSuccessors(D).empty());

    assert(dag.removeNode(D) == 3);
    assert(dag.getNumEdges() == 2);

    try {
        dag.addEdge(move(C_A));
        assert(0 && "Cycles not detected in dag\n");    
    } catch (...) {dag.removeEdge(C,A);}
    
    cout << "All Unit Tests Worked!\n";

}
