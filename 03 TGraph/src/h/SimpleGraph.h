#pragma once
#include "TGraph.h"

class SimpleGraph : public TGraph {

private:
    void syncVertices();

public:
    SimpleGraph() = default;
    SimpleGraph(std::vector<std::vector<char>> edges);
    SimpleGraph(std::vector<const char*> edgeStrings);

    std::string ToString() const override;
};
