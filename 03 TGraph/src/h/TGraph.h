#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "graphTypes.h"

class SimpleGraph;
class WeightedGraph;

class TGraph {

protected:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
    
public:
    TGraph() = default;
    TGraph(std::vector<Vertex> vertices, std::vector<Edge> edges);

    virtual std::string ToString() const;
    virtual const std::vector<Vertex> GetVertices() const;
    virtual const std::vector<Edge> GetEdges() const;
    
    friend SimpleGraph operator+(const TGraph& g1, const TGraph& g2);
    friend SimpleGraph operator-(const TGraph& g1, const TGraph& g2);
    friend WeightedGraph operator-(const WeightedGraph& g1, const WeightedGraph& g2);
    friend WeightedGraph operator-(const WeightedGraph& g1, const TGraph& g2);
    friend TGraph operator-(const TGraph& g1, const WeightedGraph& g2);

    WeightedGraph AsWeighted(int defaultWeight);
};

