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
#include "h/WeightedGraph.h"
#include "h/graphValidation.h"

#include <iostream>

TGraph::TGraph(std::vector<Vertex> vertices, std::vector<Edge> edges) {
    if (!validateVertices(vertices))
        throw std::invalid_argument("Vertices validation failed: " + makeVerticesString(vertices));
    if (!validateEdges(edges))
        throw std::invalid_argument("Edges validation failed: " + makeEdgesString(edges));

    _vertices = vertices;
    _edges = edges;
}

std::string TGraph::ToString() const {
    return std::string()
        .append("Vertices: ")
        .append(makeVerticesString(_vertices))
        .append(". Edges: ")
        .append(makeEdgesString(_edges))
        .append(".");
}

const std::vector<Vertex> TGraph::GetVertices() const {
    return _vertices;
}

const std::vector<Edge> TGraph::GetEdges() const {
    return _edges;
}

SimpleGraph operator+(const TGraph& g1, const TGraph& g2) {
    std::unordered_set<Edge, UnorderedEdgeHash> edges;
    for (auto edge: g1.GetEdges()) {
        edges.insert(edge);
    }
    for (auto edge: g2.GetEdges()) {
        edges.insert(edge);
    }
    return SimpleGraph(std::vector(edges.begin(), edges.end()));
}

SimpleGraph operator-(const TGraph& g1, const TGraph& g2) {
    std::unordered_set<Edge, UnorderedEdgeHash> edges;
    for (auto edge: g1.GetEdges()) {
        edges.insert(edge);
    }
    for (auto edge: g2.GetEdges()) {
        edges.extract(edge);
    }
    return SimpleGraph(std::vector(edges.begin(), edges.end()));
}
