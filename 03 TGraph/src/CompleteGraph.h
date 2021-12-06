#pragma once
#include "TGraph.h"

class CompleteGraph : public TGraph {

    std::vector<char> _vertices;

public:
    CompleteGraph() = default;
    CompleteGraph(std::vector<char> vertices);

    std::string ToString() const override;
    const std::vector<char> GetVertices() const override;
    std::vector<std::vector<char>> GetEdges() const override;

    friend CompleteGraph operator+(const CompleteGraph& g1, const CompleteGraph& g2);
    friend CompleteGraph operator-(const CompleteGraph& g1, const CompleteGraph& g2);
};
