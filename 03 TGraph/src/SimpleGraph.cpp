#include "h/SimpleGraph.h"
#include <vector>
#include "h/utils.h"
#include "h/graphUtils.h"
#include <algorithm>
#include <set>
#include <iostream>

SimpleGraph::SimpleGraph(std::vector<Edge> edges) {
    _edges = edges;
    syncVertices();
}

SimpleGraph::SimpleGraph(std::vector<const char*> edgeStrings) {
    std::vector<Edge> edges;
    for (auto edgeString: edgeStrings) {
        edges.push_back(Edge{ edgeString[0], edgeString[1] });
    }
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
