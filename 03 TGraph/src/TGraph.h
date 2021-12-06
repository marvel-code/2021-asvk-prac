#pragma once
#include <string>
#include <vector>
#include <stdexcept>


class TGraph {
    
public:    
    virtual std::string ToString() const = 0;
    virtual const std::vector<char> GetVertices() const = 0;
    virtual std::vector<std::vector<char>> GetEdges() const = 0;
    
    //WeightedGraph TGraph.AsWeighted(int default_weight) {}
};

