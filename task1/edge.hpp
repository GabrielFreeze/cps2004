template <typename N, typename W> class Node;
template <typename N, typename W> class Dag;

template <typename N, typename W> class Edge {
    
    friend class Dag<N, W>;

    public:
        
        Node<N,W>* from;
        Node<N,W>* to;
        W weight;

        Edge(Node<N,W>* from, Node<N,W>* to, W weight) {
            this->from = from;
            this->to = to;
            this->weight = weight;
        }


        void printEdge() {
            std::cout << "(" << from->val << ") --" << weight << "-> (" << to->val << ")" << std::endl;
        }


        Node<N,W>* getFrom() {
            return this->from;
        }
        void setFrom(Node<N,W>* from) {
            this->from->removeOut(this);
            from->addOut(this);
            
            this->from = from;
        }
        
        Node<N,W>* getTo() {
            return this->to;
        }
        void setTo(Node<N,W>* to) {
            this->to->removeIn(this);
            to->addIn(this);
            
            this->to = to;
        }

};