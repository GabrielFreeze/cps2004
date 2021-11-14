template <typename N, typename W> class Edge;
template <typename N, typename W> class Dag;

template <typename N, typename W> class Node {
    
    friend class Dag<N, W>;
    
    public:

        N val;

        Node(N val) {
            this->val = val;
        }
    
    private:
        std::unordered_set<Edge<N,W>*> in;
        std::unordered_set<Edge<N,W>*> out;

        int addIn(Edge<N,W>* edge) {
            return 1 - in.insert(edge).second; //Returns 0 if edge was added, 1 if edge was already present. 
        }
        int removeIn(Edge<N,W>* edge) {
            return 1 - in.erase(edge); //Returns 0 if edge was removed, 1 if edge was not present.
        }
        int addOut(Edge<N,W>* edge) {
            return 1 - out.insert(edge).second; //Returns 0 if edge was added, 1 if edge was already present. 
        }
        int removeOut(Edge<N,W>* edge) {
            return 1 - out.erase(edge); //Returns 0 if edge was removed, 1 if edge was not present.
        }
}; 
