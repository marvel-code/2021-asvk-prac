#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class SimpleGraph;
class WeightedGraph;

class TGraph {

protected:
    std::vector<char> _vertices;
    std::vector<std::vector<char>> _edges;
    
public:
    TGraph() = default;
    TGraph(std::vector<char> vertices, std::vector<std::vector<char>> edges);

    virtual std::string ToString() const;
    virtual const std::vector<char> GetVertices() const;
    virtual const std::vector<std::vector<char>> GetEdges() const;
    
    friend SimpleGraph operator+(const TGraph& g1, const TGraph& g2);
    friend SimpleGraph operator-(const TGraph& g1, const TGraph& g2);
    friend WeightedGraph operator-(const WeightedGraph& g1, const WeightedGraph& g2);
    friend WeightedGraph operator-(const WeightedGraph& g1, const TGraph& g2);
    friend TGraph operator-(const TGraph& g1, const WeightedGraph& g2);

    //WeightedGraph TGraph.AsWeighted(int default_weight) {}
};

