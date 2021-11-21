template <typename N, typename W> struct Edge;
template <typename N, typename W> class Dag;

template <typename N, typename W> class Node {
    
    friend class Dag<N, W>;
    
    public:

        N val;
        Node() {}
        Node(N val) {
            this->val = val;
        }
        std::unordered_set<Node<N,W>*> getIn() {
            return in;
        }
        std::unordered_set<Node<N,W>*> getOut() {
            return out;
        }

    private:
        std::unordered_set<Node<N,W>*> in;
        std::unordered_set<Node<N,W>*> out;

        int addIn(Node<N,W>* node) {
            return 1 - in.insert(node).second; //Returns 0 if node was new, 1 otherwise.
        }

        int addOut(Node<N,W>* node) {
            return 1 - out.insert(node).second; //Returns 0 if node was new, 1 otherwise.
        }

        int removeIn(Node<N,W>* node) {
            return 1 - in.erase(node); //Returns 0 if node was erased, 1 otherwise.
        }

        int removeOut(Node<N,W>* node) {
            return 1 - out.erase(node); //Returns 0 if node was erased, 1 otherwise.
        }
}; 
