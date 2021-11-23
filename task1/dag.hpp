#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <cassert>
#include "edge.hpp"
#include "node.hpp"

template <typename N> class Dag {

    public:
        Dag(std::unique_ptr<Edge<N>>* edges, int size) {
            //Add every edge to edges vector
            for (auto i = 0; i < size; i++){
                addEdge(std::move(edges[i]));
            }     
        }
        Dag(std::unique_ptr<Edge<N>> edge) {
            addEdge(std::move(edge));
        }
        Dag(){};


        bool exists(Node<N>* node){
            return node->index > -1;
        }

        void printTable(){
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    std::cout << table.at(i).at(j) << " ";
                }
                std::cout << std::endl ;
            }
            std::cout << std::endl;
        }

        int addNode(Node<N>* node) {
            if (!node) throw std::invalid_argument("Argument passed is a Null Pointer.");
           
            //If node is already in graph, return -1.
            if (exists(node))
                return -1;

            node->index = numNodes++;

            std::vector<int> nodeVec;

            //Declare that the new node is not pointing to none of the other nodes (or itself)
            for (int i = 0; i < numNodes; i++) {
                nodeVec.push_back(0);
            }

            //Add reference to the new node
            table.push_back(nodeVec);
            

            //For every node, declare that it is not connected to the new node
            for (int i = 0; i < numNodes-1; i++) {
                table[i].push_back(0);
            }

            //The index of this new node should be equal to its position in nodes. 
            nodes.push_back(node);

            return 0;
        }

        int removeNode(Node<N>* node) {
            
            if (!node) throw std::invalid_argument("Argument passed is a Null Pointer.");
            
            //Return -1 in case of non-existent node
            if (!exists(node)) return -1;

            //Find index of the node to be removed
            int j;
            for (int i = 0; i < numNodes; i++){
                if (nodes[i] == node) {
                    j = i;
                    break;
                }
            }
            
            //Remove coloumn
            table.erase(table.begin()+j);

            //Remove reference to deleted node from every other node and decrease numNodes.
            for (int i = 0; i < numNodes-1; i++) {
                table[i].erase(table[i].begin()+j);
            }

            //Update numNodes
            numNodes--;


            //Remove node from vector of all nodes
            nodes.erase(nodes.begin()+j);

            //Decrement index of all nodes that cascaded back
            for (auto it = nodes.begin()+j; it != nodes.end(); it++) {
                (*it)->index--;
            }

            return 0;

        }
        
        //Returns an index to refer to the edge you added.
        int addEdge(std::unique_ptr<Edge<N>> edge){
            if (!edge) throw std::invalid_argument("Argument passed is a Null Pointer.");

            //Ensures the nodes are added in the graph.
            addNode(edge->from);
            addNode(edge->to);

            //Declare a connection between these nodes.
            table[edge->from->index][edge->to->index] = ++numEdges;

            //Move edge to vector of edges.
            edges.push_back(std::move(edge));
            
            return numEdges;

        }
        
        int removeEdge(Node<N>* from, Node<N>* to) {
            if (!from || !to) throw std::invalid_argument("Argument passed is a Null Pointer.");

            //Get the index of the edge describing this connection
            int index = table[from->index][to->index]-1;

            //Remove the edge from the table
            table[from->index][to->index] = 0;

            //Remove the edge from the vector of all edges.
            edges.erase(edges.begin()+index);

            //Decrement the index of the remaining edges.
            for (auto it = edges.begin()+index; it != edges.end(); it++){
                int from = (*it)->from->index;
                int to   = (*it)->to->index;

                table[from][to]--;
            }   

            return --numEdges;
        }
       

        
    private:
        std::vector<Node<N>*> nodes; //Set of all nodes.
        std::vector<std::unique_ptr<Edge<N>>> edges; //Set of all edges.
        int numNodes = 0;
        int numEdges = 0;

        std::vector<std::vector<int>> table;

        int checkCycle() {
            assert(0 && "Cycle Checking Function not yet implemented");
            return 0;
        }

        

};