#include <string>
#include <set>
#include <vector>

template <typename N> struct Node {
    N val;
    std::vector<Node<N>*> in;
    std::vector<Node<N>*> out;

};

typedef struct Node Node;

template <typename W> struct Edge {
    Node* from;
    Node* to;
    W weight;
};

typedef struct Edge Edge;


template <typename N, typename Weight> class Dag {

    public:
        Dag(Edge* edges);
    
    private:
        std::set<Node<N>*> nodes;
        std::set<Edge<Weight>*> edges;
        int numNodes;
        int numEdges;


    
};

