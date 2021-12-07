#pragma once
#include "TGraph.h"

class SimpleGraph : public TGraph {

public:
    SimpleGraph() = default;
    SimpleGraph(std::vector<std::vector<char>> edges);

    std::string ToString() const override;
};
