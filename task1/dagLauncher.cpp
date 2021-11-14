#include <iostream>
#include "dag.hpp"
using namespace std;

/*
    TODO: Think if Edge should be a class or stay a struct.
    TODO: Implement checkCycles function.
    TODO: Optimise the 2 sets for nodes and edges.

*/



/*
 The return type of addX() will be 0 if X was new, 1 if X was already in the graph.
 Therefore caling addX() will not only add X but will tell you wether X was already present or not.

 0 -> expected behaviour
 1 -> deviant behaviour

 Code can then be structured like so: 
    
    if (function()) {
        ...function did not exit normally...
    }

*/
int main() {
    
    /*  
    [A]-¹->[B]--²>[C]
    ↑             |
    ⌞_____₁______⌟
    */

    Node<char, int>* A = new Node<char, int>('A');
    Node<char, int>* B = new Node<char, int>('B');
    Node<char, int>* C = new Node<char, int>('C');


    Edge<char, int>* edges[] =  {new Edge<char, int>(A,B, 1),
                                new Edge<char, int>(B,C,2),
                                new Edge<char, int>(C,A,1)};
    
    int edgeNum = sizeof(edges)/sizeof(edges[0]);

    
    Dag<char, int> dag = Dag(edges, edgeNum);
    

    dag.addEdge(new Edge<char,int>(A,B,7)); //Will be added because it's unique.
    dag.addEdge(new Edge<char,int>(A,B,1)); //Won't be added as an edge with the same values already exists.
    dag.addEdge(edges[2]);                  //Won't be added because edge was already added before.

    
    dag.printEdges();
    // cout << dag.addNode(D) << endl;

}