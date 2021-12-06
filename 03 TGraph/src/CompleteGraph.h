#pragma once
#include "TGraph.h"

class CompleteGraph : public TGraph {

    std::vector<char> _vertices;

public:
    CompleteGraph() = default;
    CompleteGraph(std::vector<char> vertices);

    std::string ToString() override;
    const std::vector<char> GetVertices() override;
    std::vector<std::vector<char>> GetEdges() override;
};
