#pragma once

#include <string>
#include <set>
#include <vector>

template <typename N> struct Node {
    N val;
    std::vector<Node<N>*> in;
    std::vector<Node<N>*> out;

};





template <typename N, typename W> struct Edge {
    Node<N>* from;
    Node<N>* to;
    W weight;
};


template <typename N, typename W> class Dag {

    public:
        Dag(Edge<N,W>** newEdges, int n_edges) {
            for (auto i = 0; i < n_edges; i++)
                edges.insert(newEdges[i]); //Inserts a pointer to an edge into the set of edges.
        };

        std::set<Edge<N,W>*> getEdges(){
            return edges;
        }

    private:
        std::set<Node<N>*> nodes; //Set of all nodes.
        std::set<Edge<N,W>*> edges; //Set of all edges.
        int numNodes;
        int numEdges;
};
