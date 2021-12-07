#include "h/SimpleGraph.h"
#include <vector>
#include "h/utils.h"
#include "h/graphUtils.h"
#include <algorithm>
#include <set>
#include <iostream>

SimpleGraph::SimpleGraph(std::vector<std::vector<char>> edges) {
    _edges = edges;
    syncVertices();
}

SimpleGraph::SimpleGraph(std::vector<const char*> edgeStrings) {
    std::vector<std::vector<char>> edges;
    for (auto edgeString: edgeStrings) {
        edges.push_back(std::vector{ edgeString[0], edgeString[1] });
    }
    _edges = edges;
    syncVertices();
}

void SimpleGraph::syncVertices() {
    std::set<char> vertices;
    for (auto edge: _edges) {
        vertices.insert(edge[0]);
        vertices.insert(edge[1]);
    }
    _vertices = std::vector(vertices.begin(), vertices.end());
}

std::string SimpleGraph::ToString() const {
    std::vector<std::string> edgeStrings(_edges.size());
    std::transform(_edges.begin(), _edges.end(), edgeStrings.begin(), makeEdgeString);
    return std::string()
        .append("{ ")
        .append(stringJoin(edgeStrings, ", "))
        .append(" }");
}
