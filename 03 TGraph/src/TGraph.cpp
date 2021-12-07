#include <string>
#include <vector>
#include <stdexcept>
#include "h/TGraph.h"
#include <set>
#include <unordered_set>
#include "h/graphUtils.h"
#include "h/utils.h"
#include <algorithm>
#include "h/SimpleGraph.h"

#include <iostream>


std::string TGraph::ToString() const {
    return "123";
}

const std::vector<char> TGraph::GetVertices() const {
    return _vertices;
}

const std::vector<std::vector<char>> TGraph::GetEdges() const {
    return _edges;
}

SimpleGraph operator+(const TGraph& g1, const TGraph& g2) {
    std::unordered_set<std::vector<char>, UnorderedEdgeHash> mergedEdges;
    for (auto edge: g1.GetEdges()) {
        mergedEdges.insert(edge);
    }
    for (auto edge: g2.GetEdges()) {
        mergedEdges.insert(edge);
    }
    return SimpleGraph(std::vector(mergedEdges.begin(), mergedEdges.end()));
}

SimpleGraph operator-(const TGraph& g1, const TGraph& g2) {
    return SimpleGraph();
}
