#pragma once
#include <string>
#include <vector>
#include <stdexcept>


class TGraph {
    
public:    
    virtual std::string ToString() = 0;
    virtual const std::vector<char> GetVertices() = 0;
    virtual std::vector<std::vector<char>> GetEdges() = 0;
    
    //WeightedGraph TGraph.AsWeighted(int default_weight) {}
};

