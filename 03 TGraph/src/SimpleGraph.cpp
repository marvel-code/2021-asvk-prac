#include "h/SimpleGraph.h"
#include <vector>
#include "h/utils.h"
#include "h/graphUtils.h"
#include <algorithm>
#include <set>
#include <iostream>
#include "h/graphValidation.h"

SimpleGraph::SimpleGraph(std::vector<Edge> edges) {
    if (!validateEdges(edges))
        throw std::invalid_argument("Edges validation failed: " + makeEdgesString(edges));

    _edges = edges;
    syncVertices();
}

SimpleGraph::SimpleGraph(std::vector<const char*> edgeStrings) {
    std::vector<Edge> edges;
    for (auto edgeString: edgeStrings) {
        edges.push_back(Edge{ edgeString[0], edgeString[1] });
    }
    if (!validateEdges(edges))
        throw std::invalid_argument("Edges validation failed: " + makeEdgesString(edges));
        
    _edges = edges;
    syncVertices();
}

void SimpleGraph::syncVertices() {
    std::set<Vertex> vertices;
    for (auto edge: _edges) {
        vertices.insert(edge[0]);
        vertices.insert(edge[1]);
    }
    _vertices = std::vector(vertices.begin(), vertices.end());
}

std::string SimpleGraph::ToString() const {
    return makeEdgesString(_edges);
}
