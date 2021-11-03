#include <string>
#include <set>

template <typename N, typename I>

class Dag {

    class Edge {

        private:
            N node1;
            N node2;
            I value;
    };

    public:
        int x;

    private:
        std::set<N> nodes;
        std::set<Edge> edges;
    
    

};

