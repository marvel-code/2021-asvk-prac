#include "h/BipartiteGraph.h"
#include "h/graphUtils.h"
#include "set"

BipartiteGraph::BipartiteGraph(
    std::vector<Vertex> topVertices, 
    std::vector<Vertex> bottomVertices
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
            _edges.push_back(Edge{ topVertex, bottomVertex });
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
    std::vector<Vertex> mergedTopVertices;
    mergedTopVertices.reserve(g1._topVertices.size() + g2._topVertices.size());
    for (auto v: g1._topVertices) {
        mergedTopVertices.push_back(v);
    }
    std::set<Vertex> g1TopVertexSet(g1._topVertices.begin(), g1._topVertices.end());
    for (auto v: g2._topVertices) {
        if (g1TopVertexSet.count(v) == 0)
            mergedTopVertices.push_back(v);
    }
    
    // Bottom vertices merge
    std::vector<Vertex> mergedBottomVertices;
    mergedBottomVertices.reserve(g1._bottomVertices.size() + g2._bottomVertices.size());
    for (auto v: g1._bottomVertices) {
        mergedBottomVertices.push_back(v);
    }
    std::set<Vertex> g1BottomVertexSet(g1._bottomVertices.begin(), g1._bottomVertices.end());
    for (auto v: g2._bottomVertices) {
        if (g1BottomVertexSet.count(v) == 0)
            mergedBottomVertices.push_back(v);
    }

    return BipartiteGraph(mergedTopVertices, mergedBottomVertices);
}

BipartiteGraph operator-(const BipartiteGraph& g1, const BipartiteGraph& g2) {

    // Top vertices minus
    std::vector<Vertex> topVertices;
    topVertices.reserve(g1._topVertices.size());
    std::set<Vertex> g2TopVertexSet(g2._topVertices.begin(), g2._topVertices.end());
    for (auto v: g1._topVertices) {
        if (g2TopVertexSet.count(v) == 0)
            topVertices.push_back(v);
    }
    
    // Bottom vertices merge
    std::vector<Vertex> bottomVertices;
    bottomVertices.reserve(g1._bottomVertices.size());
    std::set<Vertex> g2BottomVertexSet(g2._bottomVertices.begin(), g2._bottomVertices.end());
    for (auto v: g1._bottomVertices) {
        if (g2BottomVertexSet.count(v) == 0)
            bottomVertices.push_back(v);
    }

    return BipartiteGraph(topVertices, bottomVertices);
}

