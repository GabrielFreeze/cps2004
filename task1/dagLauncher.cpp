#include <iostream>
#include <unordered_set>
#include "dag.hpp"
using namespace std;

/*
    TODO: Implement checkCycles function.
    TODO: Optimise the 2 sets for nodes and edges.
    TODO: Figure out ownership
    TODO: Deprecate edge class.
*/

//Shared pointer of a unique pointer to a node.
//Convert unique_ptr into shared_ptr once unqie_ptr is passed to Graph.





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


    Node<char>* A = new Node<char>('A'); 
    Node<char>* D = new Node<char>('D');
    Node<char>* G = new Node<char>('G');
    Node<char>* B = new Node<char>('B'); 
    Node<char>* E = new Node<char>('E');
    Node<char>* H = new Node<char>('H');
    Node<char>* C = new Node<char>('C'); 
    Node<char>* F = new Node<char>('F');
    Node<char>* I = new Node<char>('I');
    

    unique_ptr<Edge<char>> A_B(new Edge<char>{A, B});
    unique_ptr<Edge<char>> B_C(new Edge<char>{B, C});
    unique_ptr<Edge<char>> C_D(new Edge<char>{C, D});
    unique_ptr<Edge<char>> B_E(new Edge<char>{B, E});
    unique_ptr<Edge<char>> E_A(new Edge<char>{E, A});
    unique_ptr<Edge<char>> edge6(new Edge<char>{F, G});
    unique_ptr<Edge<char>> edge7(new Edge<char>{G, H});
    unique_ptr<Edge<char>> edge8(new Edge<char>{H, I});
    unique_ptr<Edge<char>> edge9(new Edge<char>{I, A});
    




    unique_ptr<Edge<char>> edges[2] = {move(A_B), move(B_C)};

    Dag<char> dag = Dag<char>(edges, sizeof(edges)/sizeof(edges[0]));
    /*  
    Current Graph:
    [A]-->[B]-->[C]
    */

    dag.addNode(C);
    /*  
    Current Graph: (C was already added before in B_C)
    [A]-->[B]-->[C]
    */

   Node<char>* nodes[2] = {C,D};
   dag.addNode(nodes, sizeof(nodes)/sizeof(nodes[0]));
   
    /*  
    Current Graph: (C was already added before)
    [A]-->[B]-->[C]
          
        [D]
    */
    
    dag.addEdge(move(C_D));

    /*  
    Current Graph: (C and D was already added before)
     [A]-->[B]-->[C]
                  |        
        [D]<-----⌟      
    */


    dag.printTable(); //Shows the adjacency matrix of the edges.

    vector<Node<char>*> children = dag.getSuccessors(B);
    cout << "Children of B are: " << children[0]->val << endl;

    dag.addEdge(move(B_E));

    /*  
    Current Graph:
     [A]-->[B]-->[C]-->[D]
            |        
      [E]<--⌟      
    */

    children = dag.getSuccessors(B);
    cout << "Children of B are: " << children[0]->val << ", " << children[1]->val << endl << endl;


    /*  
    Current Graph:
     [A]-->[B]   [D]
            |        
      [E]<--⌟      
    */

    dag.removeNode(C);
    dag.printTable();
    children = dag.getSuccessors(B);
    cout << "Children of B are: " << children[0]->val << endl << endl;


    /*  
    Propsed Graph:
      [A]-->[B]   [D]
       ^     |
       |     |        
      [E]<--⌟      
    */
   dag.addEdge(move(E_A));
    try {
        dag.addEdge(move(E_A)); //Will generate an exception as it adds cycle
    } catch(...) {
        cout << "Exception Caught" << endl;
        dag.removeEdge(E,A);
    }

    dag.printTable();

    //View all current edges
    vector<unique_ptr<Edge<char>>>& edgesRef = dag.getEdges();

    for (auto it = edgesRef.begin(); it != edgesRef.end(); it++)
        cout << (*it)->from->val << " -> " << (*it)->to->val << endl;
    
    




}