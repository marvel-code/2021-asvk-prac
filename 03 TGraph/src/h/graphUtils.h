#pragma once
#include <string>
#include <vector>
#include "graphTypes.h"
#include "WeightedGraph.h"

bool equalUnorderedEdges(Edge e1, Edge e2);

std::string makeEdgeString(const std::vector<char>& edge);

std::string makeEdgesString(const std::vector<std::vector<char>>& edges);

std::string makeVerticesString(const std::vector<char>& vertices);

struct UnorderedEdgeHash {
    std::size_t operator()(const std::vector<char>& edge) const;
};

std::vector<Edge> makeDijkstraShortestPath(
    const WeightedGraph& graph, 
    const Vertex& startVertex,  
    const Vertex& endVertex
);
