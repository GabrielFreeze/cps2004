#include <iostream>
#include "dag.hpp"
using namespace std;



int main() {

    //TODO: Make this an array of edge pointers.
        Edge<char, int> edges[3];
    
    /*  
    [A]-¹->[B]--²>[C]
    ↑             |
    ⌞_____₁______⌟
    */

    Node<char> A;
    Node<char> B;
    Node<char> C;

    A.val = 'A';
    B.val = 'B';
    C.val = 'C';

    //TODO: Make edges dynamically allocated.
        // edges[0].weight = 1;
        // edges[0].from = &A;
        // edges[0].to = &B;

        // edges[1].weight = 2;
        // edges[1].from = &B;
        // edges[1].to = &C;

        // edges[2].weight = 1;
        // edges[2].from = &C;
        // edges[2].to = &A;

    
    Dag<char, int>* dag = new Dag<char, int>(&edges, 3);
    
    // set<Edge<char, int>*> edges2 = dag->getEdges();

    // for (auto it = edges2.begin(); it != edges2.end(); it++) {
    //     cout << '['<< (*it)->from << ']' << '--' << (*it)->weight << '>' << '[' << (*it)->to << ']' << endl;
    // }

}