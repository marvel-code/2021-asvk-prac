#include "h/CompleteGraph.h"
#include "h/utils.h"
#include "h/graphUtils.h"
#include <vector>
#include <string>
#include <set>

CompleteGraph::CompleteGraph(std::vector<Vertex> vertices) {
    _vertices = vertices;
    std::vector<std::vector<Vertex>> edges;
    for (auto v1: _vertices) {
        for (auto v2: _vertices) {
            edges.push_back({ v1, v2 });
        }
    }

    _edges = edges;
}

std::string CompleteGraph::ToString() const {
    return makeVerticesString(_vertices);
}

CompleteGraph operator+(const CompleteGraph& g1, const CompleteGraph& g2) {
    std::vector<Vertex> mergedVertices;
    mergedVertices.reserve(g1._vertices.size() + g2._vertices.size());
    for (auto v: g1.GetVertices()) {
        mergedVertices.push_back(v);
    }
    std::set<Vertex> g1VertexSet(g1._vertices.begin(), g1._vertices.end());
    for (auto v: g2.GetVertices()) {
        if (g1VertexSet.count(v) == 0)
            mergedVertices.push_back(v);
    }

    return CompleteGraph(mergedVertices);
}

CompleteGraph operator-(const CompleteGraph& g1, const CompleteGraph& g2) {
    std::vector<Vertex> vertices;
    vertices.reserve(g1._vertices.size());
    std::set<Vertex> g2VertexSet(g2._vertices.begin(), g2._vertices.end());
    for (auto v: g1.GetVertices()) {
        if (g2VertexSet.count(v) == 0)
            vertices.push_back(v);
    }

    return CompleteGraph(vertices);
}
