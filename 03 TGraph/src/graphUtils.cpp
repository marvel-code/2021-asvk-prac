#include "h/graphUtils.h"
#include <algorithm>
#include "h/utils.h"

std::string makeEdgeString(const std::vector<char>& edge) {
    std::string result;
    result.push_back(edge[0]);
    result.push_back(edge[1]);
    return result;
}

std::string makeEdgesString(const std::vector<std::vector<char>>& edges) {
    std::vector<std::string> edgeStrings(edges.size());
    std::transform(edges.begin(), edges.end(), edgeStrings.begin(), makeEdgeString);
    return std::string()
        .append("{ ")
        .append(stringJoin(edgeStrings, ", "))
        .append(" }");
}

std::string makeVerticesString(const std::vector<char>& vertices) {
    return std::string()
        .append("{ ")
        .append(charJoin(vertices, ", "))
        .append(" }");
}

std::size_t UnorderedEdgeHash::operator()(const std::vector<char>& edge) const {
    char a = std::min(edge[0], edge[1]);
    char b = std::max(edge[0], edge[1]);
    std::string stroke;
    stroke.push_back(a);
    stroke.push_back(b);
    return std::hash<std::string>{}(stroke);
}
