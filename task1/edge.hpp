template <typename N> class Node;
template <typename N> class Dag;


template <typename N> struct Edge {
    

    std::shared_ptr<Node<N>> from;
    std::shared_ptr<Node<N>> to;

    // Node<N> *from;
    // Node<N> *to;
};
