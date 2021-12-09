#include "h/WeightedGraph.h"
#include <vector>
#include "h/utils.h"
#include "h/graphUtils.h"
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "h/graphValidation.h"
#include "h/SimpleGraph.h"

WeightedGraph::WeightedGraph(std::vector<Edge> edges, std::vector<int> weights) : _weights(weights) {
    if (!validateEdges(edges))
        throw std::invalid_argument("Edges validation failed: " + makeEdgesString(edges));
    if (edges.size() != weights.size())
        throw std::invalid_argument(
            "Edge and weight count difference: " 
            + std::string("Edge count: ")
            + std::to_string(edges.size()) + ". "
            + std::string("Weight count: ")
            + std::to_string(weights.size()) + "."
        );
    
    _edges = edges;
    syncVertices();
}

WeightedGraph::WeightedGraph(std::vector<const char*> edgeStrings, std::vector<int> weights) : _weights(weights) {
    std::vector<std::vector<char>> edges;
    for (auto edgeString: edgeStrings) {
        edges.push_back(Edge{ edgeString[0], edgeString[1] });
    }
    if (!validateEdges(edges))
        throw std::invalid_argument("Edges validation failed: " + makeEdgesString(edges));

    _edges = edges;
    syncVertices();
}

void WeightedGraph::syncVertices() {
    std::set<Vertex> vertices;
    for (auto edge: _edges) {
        vertices.insert(edge[0]);
        vertices.insert(edge[1]);
    }
    _vertices = std::vector(vertices.begin(), vertices.end());
}

std::string WeightedGraph::ToString() const {
    std::vector<std::string> weightedEdgeStrings;
    for (int i = 0; i < _edges.size(); ++i) {
        weightedEdgeStrings.push_back(
            charJoin(_edges[i], "") + ":" + std::to_string(_weights[i])
        );
    }
    return std::string()
        .append("{ ")
        .append(stringJoin(weightedEdgeStrings, ", "))
        .append(" }");
}

std::vector<int> WeightedGraph::GetWeights() const {
    return _weights;
}

WeightedGraph operator+(const WeightedGraph& g1, const WeightedGraph& g2) {
    std::unordered_map<
        const Edge, 
        int, 
        UnorderedEdgeHash
    > edgeWeights;
    for (int i = 0; i < g1._edges.size(); ++i) {
        edgeWeights.insert({ g1._edges[i], g1._weights[i] });
    }
    for (int i = 0; i < g2._edges.size(); ++i) {
        auto it = edgeWeights.find( g2._edges[i] );
        if (it == edgeWeights.end()) {
            edgeWeights.insert({ g2._edges[i], g2._weights[i] });
        } else if (it->second > g2._weights[i])
            it->second = g2._weights[i];
    }

    std::vector<Edge> edges;
    std::vector<int> weights;
    for (auto it = edgeWeights.begin(); it != edgeWeights.end(); ++it) {
        edges.push_back(it->first);
        weights.push_back(it->second);
    }
    return WeightedGraph(edges, weights);
}

TGraph operator+(const WeightedGraph& g1, const TGraph& g2) {
    throw std::logic_error("WeightedGraph + OtherGraph error: Edge weights not defined for other graphs.");
}

TGraph operator+(const TGraph& g1, const WeightedGraph& g2) {
    throw std::logic_error("OtherGraph + WeightedGraph error: Edge weights not defined for other graphs.");
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

