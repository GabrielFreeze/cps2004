#include <iostream>
#include "dag.hpp"
using namespace std;


int main() {
    
    /*  
    [A]-¹->[B]--²>[C]
    ↑             |
    ⌞_____₁______⌟
    */

    auto A = make_shared<Node<char>>('A'); 
    auto D = make_shared<Node<char>>('D');
    auto G = make_shared<Node<char>>('G');
    auto B = make_shared<Node<char>>('B'); 
    auto E = make_shared<Node<char>>('E');
    auto H = make_shared<Node<char>>('H');
    auto C = make_shared<Node<char>>('C'); 
    auto F = make_shared<Node<char>>('F');
    auto I = make_shared<Node<char>>('I');
    

    auto A_B = make_unique<Edge<char>>(Edge<char>{A, B});
    auto B_C = make_unique<Edge<char>>(Edge<char>{B, C});
    auto C_D = make_unique<Edge<char>>(Edge<char>{C, D});
    auto B_E = make_unique<Edge<char>>(Edge<char>{B, E});
    auto E_A = make_unique<Edge<char>>(Edge<char>{E, A});
    

    

    unique_ptr<Edge<char>> edges[2] = {move(A_B), move(B_C)};
    //unique_ptr<Edge<char>> test = A_B; Unique pointer cannot be moved

    Dag<char> dag = Dag<char>(edges, sizeof(edges)/sizeof(edges[0]));
    dag.printTable();
    cout << "Added: A->B, B->C" << endl << endl;
    /*  
    Current Graph:
    [A]-->[B]-->[C]
    */

    dag.addNode(C);
    dag.printTable();
    cout << "Added: C (was already in the graph)" << endl << endl;

    /*  
    Current Graph: (C was already added before in B_C)
    [A]-->[B]-->[C]
    */

   shared_ptr<Node<char>> nodes[2] = {C,D};
   dag.addNode(nodes, sizeof(nodes)/sizeof(nodes[0]));
   dag.printTable();
   cout << "Added: C, D (C was already in the graph)" << endl << endl;

   
    /*  
    Current Graph: (C was already added before)
    [A]-->[B]-->[C]
          
        [D]
    */
    
    dag.addEdge(move(C_D));
    dag.printTable();
    cout << "Added: C->D" << endl << endl;


    /*  
    Current Graph: (C and D was already added before)
     [A]-->[B]-->[C]
                  |        
        [D]<-----⌟      
    */


    vector<shared_ptr<Node<char>>> children = dag.getSuccessors(B);
    cout << "Children of B are: " << children[0]->val << endl;
    dag.addEdge(move(B_E));
    dag.printTable();
    cout << "Added: B->E" << endl << endl;


    /*  
    Current Graph:
     [A]-->[B]-->[C]-->[D]
            |        
      [E]<--⌟      
    */

    children = dag.getSuccessors(B);
    cout << "Children of B are: " << children[0]->val << ", " << children[1]->val << endl;


    dag.removeNode(C); //Will remove the edges B->C C->D
    dag.printTable();
    cout << "Removed: C" << endl << endl;

    children = dag.getSuccessors(B);
    cout << "Children of B are: " << children[0]->val << endl;

    /*  
    Current Graph:
     [A]-->[B]   [D]
            |        
      [E]<--⌟      
    */


   dag.addEdge(move(E_A));
    try {
        dag.addEdge(move(E_A)); //Will generate an exception as it adds cycle
    } catch(...) {
        cout << "Exception Caught" << endl << endl;
        dag.removeEdge(E,A);
    }
    /*  
    Propsed Graph:
      [A]-->[B]   [D]
       ^     |
       |     |        
      [E]<--⌟      
    */

    dag.printTable();
    cout << "Could not add E->A because of cycles" << endl << endl;

    //View all current edges
    const vector<unique_ptr<Edge<char>>>& edgesRef = dag.getEdges();
    cout << "Final edges: " << endl;
    for (auto it = edgesRef.begin(); it != edgesRef.end(); it++) {
        cout << (*it)->from->val << " -> " << (*it)->to->val << endl;
    }
    
}