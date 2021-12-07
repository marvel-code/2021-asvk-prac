#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class SimpleGraph;

class TGraph {

protected:
    std::vector<char> _vertices;
    std::vector<std::vector<char>> _edges;
    
public:    
    virtual std::string ToString() const = 0;
    virtual const std::vector<char> GetVertices() const;
    virtual std::vector<std::vector<char>> GetEdges() const;
    
    friend SimpleGraph operator+(const TGraph& g1, const TGraph& g2);
    friend SimpleGraph operator-(const TGraph& g1, const TGraph& g2);

    //WeightedGraph TGraph.AsWeighted(int default_weight) {}
};

