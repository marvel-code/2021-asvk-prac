#pragma once
#include "TGraph.h"

class BipartiteGraph : public TGraph {

private:
    std::vector<Vertex> _topVertices;
    std::vector<Vertex> _bottomVertices;

public:
    BipartiteGraph() = default;
    BipartiteGraph(std::vector<Vertex> topVertices, std::vector<Vertex> bottomVertices);

    std::string ToString() const override;

    friend BipartiteGraph operator+(const BipartiteGraph& g1, const BipartiteGraph& g2);
    friend BipartiteGraph operator-(const BipartiteGraph& g1, const BipartiteGraph& g2);
};
