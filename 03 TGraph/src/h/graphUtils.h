#pragma once
#include <string>
#include <vector>

std::string makeEdgeString(const std::vector<char>& edge);

std::string makeEdgesString(const std::vector<std::vector<char>>& edges);

std::string makeVerticesString(const std::vector<char>& vertices);

struct UnorderedEdgeHash {
    std::size_t operator()(const std::vector<char>& edge) const;
};
