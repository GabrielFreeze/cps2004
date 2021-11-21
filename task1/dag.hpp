#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <memory>
#include "edge.hpp"
#include "node.hpp"

// template <typename N, typename W>
// using Edge_ = std::pair<std::unique_ptr<Node<N,W>>,std::unique_ptr<Node<N,W>>>;
//using Edge_ = std::pair<std::shared_ptr<Node<N,W>>,std::shared_ptr<Node<N,W>>>;


template <typename N, typename W> class Dag {

    public:

        Dag(Edge<N,W>** edges, int n_edges) {
            
            for (auto i = 0; i < n_edges; i++) {
                addEdge(edges[i]); //Inserts a pointer to an edge into the set of edges.

                edges[i]->from->addOut(edges[i]);//Let every node have a reference to the edges emerging from it.
                edges[i]->to->addIn(edges[i]);//Let every node have a reference to the edges incident to it.

                // edges[i]->from->out.insert(edges[i]);
                // edges[i]->to->in.insert(edges[i]);

                addNode(edges[i]->from); //Inserts the 'from' node into the set of nodes.
                addNode(edges[i]->to);   //Inserts the 'to' node into the set of nodes.

            }

            checkCycle(); //TODO: Implement this
        };



        // //Returning a node should only return a reference to the node in the set of all nodes.

        // int addNode(N value) {
        //     //Create a new node with the value.
        //     //Returns the index of the new node in the set of nodes.
        // }

        // int removeNode(int index) {
        //     //Remove the node at the index from the set of nodes.
        //     //Destroy the unique pointer to the node.
        //     //Returns the index of the node that was removed.
        // }



        // N getValue(int index) { 
        //     //Returns the value of the node at the given index.
        // }


        // int connect(int from, int to) { //Parameters are indices of nodes already present in the Dag.
        //     //Check that the nodes are in the set of all nodes.
        //     //Connect the 'from' node to the 'to' node.
            
        //     //Create a new edge between the two nodes.
        // }

        // int disconnect(int from, int to) {
        //     //Check that the nodes are in the set of all nodes.
        //     //Disconnect the 'from' node from the 'to' node.
        // }





        std::unordered_set<Edge<N,W>*> getEdges() {
            return edges;
        }

        std::unordered_set<Node<N,W>*> getNodes() {
            return nodes;
        }

        void printEdges() { //Prints all edges.
            for (auto it = edges.begin(); it != edges.end(); it++)
                std::cout << "(" << (*it)->from->val << ") --" << (*it)->weight << "-> (" << (*it)->to->val << ")" << std::endl;
        }

        int addNode(Node<N,W>* node) {
            
            /*A node with the same value to another node already in the graph may be added,
            but a pointer to a node already in the set of nodes is not.*/

            if (!node)
                throw std::invalid_argument("Argument passed is a Null Pointer");

            return 1 - nodes.insert(node).second; //Returns 0 if node was added, 1 if node was already in graph.
        }
       
        int removeNode(Node<N,W>* node) { //Removing a node also meanns removing all edges connected to the node.
            //TODO: Destroy node
            for (auto it = edges.begin(); it != edges.end(); it++) {
                if ((*it)->from == node || (*it)->to == node) //Remove all edges connected to node.
                    removeEdge(it);
            }
            
            return 1 - nodes.erase(node); //Returns 0 if node was removed, 1 if no node was removed.
        }
        
        int addEdge(Edge<N,W>* edge) { //Adding an Edge also implies adding any new nodes connected to the edge.
            
            if (!edge)
                throw std::invalid_argument("Argument passed is a Null Pointer.");

            //Checks wether there is an identical edge already in the graph.
            for (auto it = edges.begin(); it != edges.end(); it++) {
                
                if ((*it)->from == edge->from &&
                    (*it)->to == edge->to     &&
                    (*it)->weight == edge->weight) {
                    
                    return 1; //Returns 1 if edge was already in the set.
                }     
            }

            /*Adds the nodes referenced by the edge to the graph.
            Nodes could already be in the graph, so return type is not checked.*/
            addNode(edge->from);
            addNode(edge->to);
            
            edge->from->addOut(edge);//Make a reference to the new emergent edge to the FROM node.
            edge->to->addIn(edge);//Make a reference to the new incident edge from the TO node.

            // addOut(edge->from, edge); //Make a reference to the new emergent edge to the FROM node.
            // addIn(edge->to, edge); //Make a reference to the new incident edge from the TO node.

            return 1 - edges.insert(edge).second; //Returns 0 is edge was added, 1 if edge was already in the set.
        }

        int removeEdge(Edge<N,W>* edge) { //When an edge is removed, the 'from' and 'to' nodes are not removed.
            //TODO: Destroy node

            //When an edge is removed, all references to that edge in a node must be removed as well.
            for (auto node = nodes.begin(); node != nodes.end(); node++) {
                
                /*Small Optimisation: This if statement ensures that if an edge was removed from IN, 
                we don't need to check for it in OUT.*/

                if (node->removeIn(edge))
                    node->removeOut(edge);

                // if (removeIn(*node,edge))
                //     removeOut(*node,edge);
            }


            return 1 - edges.erase(edge); //Returns 0 if edge was removed, 1 if edge was not present.
        }

        
    private:
        std::unordered_set<Node<N,W>*> nodes; //Set of all nodes.
        std::unordered_set<Edge<N,W>*> edges; //Set of all edges.
        
        
        // std::vector<std::unique_ptr<Node<N,W>>> _nodes; 
        // std::set<std::unique_ptr<Node<N,W>>> _edges;
        int numNodes;
        int numEdges;

        int checkCycle() {
            return 0;
        }

        

};
