#include "TGraph.h"

class BipartiteGraph : public TGraph {

private:
    std::vector<char> _topVertices;
    std::vector<char> _bottomVertices;

public:
    BipartiteGraph() = default;
    BipartiteGraph(std::vector<char> topVertices, std::vector<char> bottomVertices);

    std::string ToString() const override;

    friend BipartiteGraph operator+(const BipartiteGraph& g1, const BipartiteGraph& g2);
    friend BipartiteGraph operator-(const BipartiteGraph& g1, const BipartiteGraph& g2);
};
