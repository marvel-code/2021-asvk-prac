#include "h/SimpleGraph.h"
#include <vector>
#include "h/utils.h"
#include "h/graphUtils.h"
#include <algorithm>
#include <set>

SimpleGraph::SimpleGraph(std::vector<std::vector<char>> edges) {
    _edges = edges;
    
    std::set<char> vertices;
    for (auto edge: _edges) {
        vertices.insert(edge[0]);
        vertices.insert(edge[1]);
    }
    _vertices = std::vector(vertices.begin(), vertices.end());
}

std::string SimpleGraph::ToString() const {
    std::vector<std::string> edgeStrings;
    std::transform(_edges.begin(), _edges.end(), edgeStrings.begin(), makeEdgeString);
    return std::string()
        .append("{ ")
        .append(stringJoin(edgeStrings, ", "))
        .append(" }");
}
