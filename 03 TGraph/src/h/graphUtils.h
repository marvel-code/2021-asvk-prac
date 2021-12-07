#pragma once
#include <string>
#include <vector>

std::string makeEdgeString(const std::vector<char>& edge);

struct UnorderedEdgeHash {
    std::size_t operator()(const std::vector<char>& edge) const;
};
