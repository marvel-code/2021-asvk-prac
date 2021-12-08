#include "h/BipartiteGraph.h"
#include "h/graphUtils.h"
#include "set"

BipartiteGraph::BipartiteGraph(
    std::vector<char> topVertices, 
    std::vector<char> bottomVertices
) : _topVertices(topVertices), _bottomVertices(bottomVertices) {

    // Fill vertices
    _vertices.reserve(topVertices.size() + bottomVertices.size());
    for (auto vertex: topVertices) {
        _vertices.push_back(vertex);
    }
    for (auto vertex: bottomVertices) {
        _vertices.push_back(vertex);
    }

    // Make edges
    for (auto topVertex: topVertices) {
        for (auto bottomVertex: bottomVertices) {
            _edges.push_back(std::vector<char>{ topVertex, bottomVertex });
        }
    }
}

std::string BipartiteGraph::ToString() const {
    return std::string()
        .append("Top: ")
        .append(makeVerticesString(_topVertices))
        .append(". Bottom: ")
        .append(makeVerticesString(_bottomVertices))
        .append(".");
}

BipartiteGraph operator+(const BipartiteGraph& g1, const BipartiteGraph& g2) {

    // Top vertices merge
    std::vector<char> mergedTopVertices;
    mergedTopVertices.reserve(g1._topVertices.size() + g2._topVertices.size());
    for (auto v: g1._topVertices) {
        mergedTopVertices.push_back(v);
    }
    std::set<char> g1TopVertexSet(g1._topVertices.begin(), g1._topVertices.end());
    for (auto v: g2._topVertices) {
        if (g1TopVertexSet.count(v) == 0)
            mergedTopVertices.push_back(v);
    }
    
    // Bottom vertices merge
    std::vector<char> mergedBottomVertices;
    mergedBottomVertices.reserve(g1._bottomVertices.size() + g2._bottomVertices.size());
    for (auto v: g1._bottomVertices) {
        mergedBottomVertices.push_back(v);
    }
    std::set<char> g1BottomVertexSet(g1._bottomVertices.begin(), g1._bottomVertices.end());
    for (auto v: g2._bottomVertices) {
        if (g1BottomVertexSet.count(v) == 0)
            mergedBottomVertices.push_back(v);
    }

    return BipartiteGraph(mergedTopVertices, mergedBottomVertices);
}

