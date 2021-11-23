template <typename N> class Node;
template <typename N> class Dag;


template <typename N> struct Edge {
    
    Node<N> *from;
    Node<N> *to;
};
