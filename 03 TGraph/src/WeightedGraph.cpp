#include "h/WeightedGraph.h"
#include <vector>
#include "h/utils.h"
#include "h/graphUtils.h"
#include <algorithm>
#include <set>
#include <unordered_map>
#include "h/graphValidation.h"

WeightedGraph::WeightedGraph(std::vector<Edge> edges, std::vector<int> weights) : _weights(weights) {
    if (!validateEdges(edges))
        throw std::invalid_argument("Edges validation failed: " + makeEdgesString(edges));
    
    _edges = edges;
    syncVertices();
}

WeightedGraph::WeightedGraph(std::vector<const char*> edgeStrings, std::vector<int> weights) : _weights(weights) {
    std::vector<std::vector<char>> edges;
    for (auto edgeString: edgeStrings) {
        edges.push_back(Edge{ edgeString[0], edgeString[1] });
    }
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
