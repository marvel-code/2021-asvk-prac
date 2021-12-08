#include "h/BipartiteGraph.h"
#include "h/graphUtils.h"

BipartiteGraph::BipartiteGraph(
    std::vector<char> topVertices, 
    std::vector<char> bottomVertices
) : _topVertices(topVertices), _bottomVertices(bottomVertices) {

    // Fill vertices
    _vertices.reserve(topVertices.size() + bottomVertices.size());
    for (auto vertex: topVertices) {
        _vertices.push_back(vertex);
    }
    for (auto vertex: bottomVertices) {
        _vertices.push_back(vertex);
    }

    // Make edges
    for (auto topVertex: topVertices) {
        for (auto bottomVertex: bottomVertices) {
            _edges.push_back(std::vector<char>{ topVertex, bottomVertex });
        }
    }
}
