template <typename N> struct Edge;
template <typename N> class Dag;

template <typename N> class Node {
    
    friend class Dag<N>;
    
    public:

        N val;
        Node() {}
        Node(N val) {
            this->val = val;
        }


    private:
        int index = -1;
}; 

