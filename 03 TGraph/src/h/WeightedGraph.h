#pragma once
#include "TGraph.h"

class WeightedGraph : public TGraph {

private:
    std::vector<int> _weights;
    void syncVertices();

public:
    WeightedGraph() = default;
    WeightedGraph(std::vector<Edge> edges, std::vector<int> weights);
    WeightedGraph(std::vector<const char*> edgeStrings, std::vector<int> weights);

    std::string ToString() const override;
    std::vector<int> GetWeights() const;
    
    friend WeightedGraph operator+(const WeightedGraph& g1, const WeightedGraph& g2);
    friend WeightedGraph operator-(const WeightedGraph& g1, const WeightedGraph& g2);
    friend WeightedGraph operator-(const WeightedGraph& g1, const TGraph& g2);
    friend TGraph operator-(const TGraph& g1, const WeightedGraph& g2);
};
