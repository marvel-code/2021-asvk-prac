#include "h/graphUtils.h"
#include <algorithm>

#include <iostream>

std::string makeEdgeString(const std::vector<char>& edge) {
    std::string result;
    result.push_back(edge[0]);
    result.push_back(edge[1]);
    return result;
}

std::size_t UnorderedEdgeHash::operator()(const std::vector<char>& edge) const {
    char a = std::min(edge[0], edge[1]);
    char b = std::max(edge[0], edge[1]);
    std::string stroke;
    stroke.push_back(a);
    stroke.push_back(b);
    return std::hash<std::string>{}(stroke);
}
