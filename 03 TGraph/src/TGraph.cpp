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

WeightedGraph operator-(const WeightedGraph& g1, const WeightedGraph& g2) {
    return g1 - (TGraph)g2;
}

/**
 * @brief A - B = G:
 * - Множество рёбер G эквивалентно разности множеств рёбер A и B;
 * - Веса рёбер, присутствующих в результирующем множестве рёбер G, переносятся из A.
 */
WeightedGraph operator-(const WeightedGraph& g1, const TGraph& g2) {
    // Make edges
    std::unordered_set<Edge, UnorderedEdgeHash> edgesSet;
    for (auto edge: g1.GetEdges()) {
        edgesSet.insert(edge);
    }
    for (auto edge: g2.GetEdges()) {
        edgesSet.extract(edge);
    }
    std::vector<Edge> edges(edgesSet.begin(), edgesSet.end());

    // Set weights
    std::vector<int> weights;
    for (auto edge: edges) {
        int index = findIndex(
            g1.GetEdges(), 
            std::function<bool(Edge)>([&edge](Edge e) {
                return edge[0] == e[0] && edge[1] == e[1]; 
            })
        );
        weights.push_back(g1.GetWeights()[index]);
    }

    return WeightedGraph(edges, weights);
}

/**
 * @brief A - B = G:
 * - Множество рёбер G эквивалентно разности множеств рёбер A и B
 */
TGraph operator-(const TGraph& g1, const WeightedGraph& g2) {
    // Make edges
    std::unordered_set<Edge, UnorderedEdgeHash> edges;
    for (auto edge: g1.GetEdges()) {
        edges.insert(edge);
    }
    for (auto edge: g2.GetEdges()) {
        edges.extract(edge);
    }

    return SimpleGraph(std::vector(edges.begin(), edges.end()));
}

WeightedGraph TGraph::AsWeighted(int defaultWeight) {
    // Init weights
    std::vector<int> weights;
    for (int i = 0; i < _edges.size(); ++i) {
        weights.push_back(defaultWeight);
    }

    return WeightedGraph(_edges, weights);
}
