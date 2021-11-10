#include <iostream>
#include "dag.hpp"
using namespace std;

/*
    TODO: Think if Edge should be a class or stay a struct.
    TODO: Implement checkCycles function.
    TODO: Implement removeNode and removeEdge functions.

*/

int main() {
    
    /*  
    [A]-¹->[B]--²>[C]
    ↑             |
    ⌞_____₁______⌟
    */

    Edge<char, int>* edges[3];

    Edge<char, int> edge1;
    Edge<char, int> edge2;
    Edge<char, int> edge3;

    edges[0] = &edge1;
    edges[1] = &edge2;
    edges[2] = &edge3;


    Node<char> A;
    Node<char> B;
    Node<char> C;


    A.val = 'A';
    B.val = 'B';
    C.val = 'C';


    edges[0]->weight = 1;
    edges[0]->from = &A;
    edges[0]->to = &B;

    edges[1]->weight = 2;
    edges[1]->from = &B;
    edges[1]->to = &C;

    edges[2]->weight = 1;
    edges[2]->from = &C;
    edges[2]->to = &A;

    
    Dag<char, int>* dag = new Dag<char, int>(edges, 3);

}