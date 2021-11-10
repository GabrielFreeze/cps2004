#pragma once

#include <string>
#include <set>
#include <vector>

template <typename N> struct Node {
    N val;
};


template <typename N, typename W> struct Edge {
    Node<N>* from;
    Node<N>* to;
    W weight;
};


template <typename N, typename W> class Dag {

    public:
        Dag(Edge<N,W>** newEdges, int n_edges) {
            
            for (auto i = 0; i < n_edges; i++) {
                addEdge(newEdges[i]); //Inserts a pointer to an edge into the set of edges.
                
                addNode(newEdges[i]->from); //Inserts the 'from' node into the set of nodes.
                addNode(newEdges[i]->to);   //Inserts the 'to' node into the set of nodes. 
            }


            checkCycle(); //TODO: Implement this
        };

        std::set<Edge<N,W>*> getEdges() {
            return edges;
        }

        std::set<Node<N>*> getNodes() {
            return nodes;
        }


        void printEdges() {
            for (auto it = edges.begin(); it != edges.end(); it++)
                std::cout << (*it)->from->val << " " << (*it)->to->val << " " << (*it)->weight << std::endl;
        }

        int addNode(Node<N>* newNode) {
            
            if (!newNode) throw std::invalid_argument("Argument passed is a Null Pointer");
            
            return nodes.insert(newNode).second;
        }

        int addEdge(Edge<N,W>* newEdge) {
                
            if (!newEdge)
                throw std::invalid_argument("Argument passed is a Null Pointer.");

            if (!newEdge->from || !newEdge->to)
                throw std::invalid_argument("Node of new edge is a Null Pointer.");

            if (!nodes.count(newEdge->from) || !nodes.count(newEdge->to))
                throw std::invalid_argument("Nodes of new edge do not exist in the Graph.");
        
            return edges.insert(newEdge).second; 
        }
        
        int removeNode(Node<N>* node) {

            for (auto it = edges.begin(); it != edges.end(); it++) {
                if ((*it)->from == node || (*it)->to == node) //Remove all edges connected to node.
                    edges.erase(it--);
            }
            
            return nodes.erase(node);//TODO: Abstract this out into a function.
        }

        //TODO: Implement this function.
        int connectNode(Node<N>* fromNode, Node<N>* toNode, W weight) {
            
            if (!fromNode || !toNode) throw std::invalid_argument("Argument passed is a Null Pointer.");
            if (!nodes.count(fromNode) || !nodes.count(toNode)) throw std::invalid_argument("Node passed does not exist in the Graph.");
            

            //Find a way to create a new edge and add it to the set of edges.


            return 0;
        }



    private:
        std::set<Node<N>*> nodes; //Set of all nodes.
        std::set<Edge<N,W>*> edges; //Set of all edges.
        int numNodes;
        int numEdges;

        int checkCycle() {
            return 0;
        }
};
