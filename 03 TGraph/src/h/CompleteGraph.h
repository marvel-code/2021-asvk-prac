#pragma once
#include "TGraph.h"

class CompleteGraph : public TGraph {

public:
    CompleteGraph() = default;
    CompleteGraph(std::vector<Vertex> vertices);

    std::string ToString() const override;

    friend CompleteGraph operator+(const CompleteGraph& g1, const CompleteGraph& g2);
    friend CompleteGraph operator-(const CompleteGraph& g1, const CompleteGraph& g2);
};
