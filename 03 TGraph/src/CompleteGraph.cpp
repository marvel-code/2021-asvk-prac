#include "CompleteGraph.h"
#include "utils.h"
#include <vector>
#include <string>

CompleteGraph::CompleteGraph(std::vector<char> vertices) : _vertices(vertices) {}

std::string CompleteGraph::ToString() {
    std::string result;
    result
        .append("{")
        .append(stringJoin(_vertices, ", "))
        .append("}");
    return result;
}

const std::vector<char> CompleteGraph::GetVertices() {
    return _vertices;
}

std::vector<std::vector<char>> CompleteGraph::GetEdges() {
    std::vector<std::vector<char>> edges;
    for (auto v1: _vertices) {
        for (auto v2: _vertices) {
            edges.push_back({ v1, v2 });
        }
    }
    return edges;
}
