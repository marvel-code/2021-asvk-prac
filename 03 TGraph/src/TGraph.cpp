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

#include <iostream>

TGraph::TGraph(std::vector<char> vertices, std::vector<std::vector<char>> edges) : _vertices(vertices), _edges(edges) {}

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
    std::unordered_set<std::vector<char>, UnorderedEdgeHash> edges;
    for (auto edge: g1.GetEdges()) {
        edges.insert(edge);
    }
    for (auto edge: g2.GetEdges()) {
        edges.insert(edge);
    }
    return SimpleGraph(std::vector(edges.begin(), edges.end()));
}

SimpleGraph operator-(const TGraph& g1, const TGraph& g2) {
    std::unordered_set<std::vector<char>, UnorderedEdgeHash> edges;
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

WeightedGraph operator-(const WeightedGraph& g1, const TGraph& g2) {
    // Make edges
    std::unordered_set<std::vector<char>, UnorderedEdgeHash> edgesSet;
    for (auto edge: g1.GetEdges()) {
        edgesSet.insert(edge);
    }
    for (auto edge: g2.GetEdges()) {
        edgesSet.extract(edge);
    }
    std::vector<std::vector<char>> edges(edgesSet.begin(), edgesSet.end());

    // Set weights
    std::vector<int> weights;
    for (auto edge: edges) {
        int index = findIndex(
            g1.GetEdges(), 
            std::function<bool(std::vector<char>)>([&edge](std::vector<char> e) {
                return edge[0] == e[0] && edge[1] == e[1]; 
            })
        );
        weights.push_back(g1.GetWeights()[index]);
    }

    return WeightedGraph(edges, weights);
}
TGraph operator-(const TGraph& g1, const WeightedGraph& g2) {
    // Make edges
    std::unordered_set<std::vector<char>, UnorderedEdgeHash> edges;
    for (auto edge: g1.GetEdges()) {
        edges.insert(edge);
    }
    for (auto edge: g2.GetEdges()) {
        edges.extract(edge);
    }

    // Make vertices
    std::unordered_set<char> vertices;
    for (auto edge: edges) {
        vertices.insert({ edge[0], edge[1] });
    }

    return TGraph(
        std::vector(vertices.begin(), vertices.end()), 
        std::vector(edges.begin(), edges.end())
    );
}
