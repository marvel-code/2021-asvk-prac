#include "h/graphValidation.h"

bool validateVertex(Vertex vertex) {
    return vertex >= 'A' && vertex <= 'Z';
}

bool validateEdge(Edge edge) {
    return edge.size() == 2 && validateVertex(edge[0]) && validateVertex(edge[1]);
}

bool validateVertices(std::vector<Vertex> vertices) {
    for (auto vertex: vertices) {
        if (!validateVertex(vertex))
            return false;
    }
    return true;
}

bool validateEdges(std::vector<Edge> edges) {
    for (auto edge: edges) {
        if (!validateEdge(edge))
            return false;
    }
    return true;
}
