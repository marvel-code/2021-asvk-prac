#include "h/CompleteGraph.h"
#include "h/utils.h"
#include "h/graphUtils.h"
#include <vector>
#include <string>
#include <set>
#include "h/graphValidation.h"

CompleteGraph::CompleteGraph(std::vector<Vertex> vertices) {
    if (!validateVertices(vertices))
        throw std::invalid_argument("Vertices validation failed: " + makeVerticesString(vertices));

    _vertices = vertices;
    std::vector<std::vector<Vertex>> edges;
    for (int i = 0; i < vertices.size(); ++i) {
        Vertex v1 = vertices[i];
        for (int j = i + 1; j < vertices.size(); ++j) {
            Vertex v2 = vertices[j];
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
