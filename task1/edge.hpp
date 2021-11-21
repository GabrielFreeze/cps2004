template <typename N, typename W> class Node;
template <typename N, typename W> class Dag;


template <typename N, typename W> struct Edge {
    
    Node<N,W> *from;
    Node<N,W> *to;
    W weight;
};
