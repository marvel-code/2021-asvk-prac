#include "h/graphUtils.h"
#include <algorithm>
#include "h/utils.h"
#include "h/graphTypes.h"
#include "h/WeightedGraph.h"
#include <limits.h>

using std::string, std::vector;

string makeEdgeString(const Edge& edge) {
    string result;
    result.push_back(edge[0]);
    result.push_back(edge[1]);
    return result;
}

string makeEdgesString(const vector<Edge>& edges) {
    vector<string> edgeStrings(edges.size());
    std::transform(edges.begin(), edges.end(), edgeStrings.begin(), makeEdgeString);
    return string()
        .append("{ ")
        .append(stringJoin(edgeStrings, ", "))
        .append(" }");
}

string makeVerticesString(const vector<Vertex>& vertices) {
    return string()
        .append("{ ")
        .append(charJoin(vertices, ", "))
        .append(" }");
}

std::size_t UnorderedEdgeHash::operator()(const Edge& edge) const {
    char a = std::min(edge[0], edge[1]);
    char b = std::max(edge[0], edge[1]);
    string stroke;
    stroke.push_back(a);
    stroke.push_back(b);
    return std::hash<string>{}(stroke);
}

vector<Edge> makeDijkstraShortestPath(
    const WeightedGraph& graph, 
    const Vertex& startVertex,  
    const Vertex& endVertex
) {
    auto weights = graph.GetWeights();
    if (findIndex(weights, std::function([](int weight) { return weight < 0; })) != -1)
        throw std::invalid_argument("Failed to make Dijkstra shortest path: graph must not have negative weight.");

    auto vertices = graph.GetVertices();
    auto edges = graph.GetEdges();
    int startVertexIndex = findIndex(vertices, startVertex);
    int endVertexIndex = findIndex(vertices, endVertex);

    // Init vertex informations: visited and minimum total weight from start.
    using VertexInfo = std::pair<bool/*visited*/, int/*min total weight from start*/>;
    vector<VertexInfo> vertexInfos(vertices.size(), std::pair<bool, int>(false, INT_MAX));

    // Fill graph matrix
    vector<vector<int>> graphMatrix(vertices.size(), vector(vertices.size(), -1));
    for (int i = 0; i < edges.size(); ++i) {
      Edge edge = edges[i];
      int weight = weights[i];
      Vertex v1 = edge[0];
      Vertex v2 = edge[1];
      int v1Index = findIndex(vertices, v1);
      int v2Index = findIndex(vertices, v2);
      graphMatrix[v1Index][v2Index] = weight;
      graphMatrix[v2Index][v1Index] = weight;
    }
    
    // Calc total weights to vertices
    int visitedVertexCount = 0;
    Vertex vertex = startVertex;
    int vertexIndex = startVertexIndex;
    VertexInfo vertexInfo = vertexInfos[vertexIndex];
    vertexInfo.second = 0;
    do {
      // Stage 1. Update near vertices.
      auto weightToNearVertices = graphMatrix[vertexIndex];
      for (int i = 0; i < vertices.size(); ++i) {
        int weightToNearVertex = weightToNearVertices[i];
        if (weightToNearVertex == -1)
          continue;
        int totalWeightToNearVertex = weightToNearVertex + vertexInfo.second;
        if (totalWeightToNearVertex < vertexInfos[i].second)
          vertexInfos[i].second = totalWeightToNearVertex;
      }
      vertexInfo.first = true;
      ++visitedVertexCount;
      if (visitedVertexCount == vertices.size())
        break;

      // Stage 2. Hop next vertex.
      int minTotalWeightedVertexIndex = -1;
      for (int i = 0; i < vertices.size(); ++i) {
        if (weightToNearVertices[i] == -1 || vertexInfos[i].first)
          continue; 
        if (vertexInfos[i].second < vertexInfos[minTotalWeightedVertexIndex].second)
          minTotalWeightedVertexIndex = i;
      }
      // Check for graph connectivity.
      if (minTotalWeightedVertexIndex == -1) {
        if (!vertexInfos[endVertexIndex].first)
          throw std::logic_error(std::string("No path from ").append(1, startVertex).append(" to ").append(1, endVertex).append("."));
        break;
      }
      // Hop
      vertexIndex = minTotalWeightedVertexIndex;
      vertex = vertices[vertexIndex];
      vertexInfo = vertexInfos[vertexIndex];
    } while (true);

    // Make shortest path from startVertex to endVertex
    vector<Edge> shortestPath;
    vertex = endVertex;
    vertexIndex = endVertexIndex;
    vertexInfo = vertexInfos[vertexIndex];
    do {
      // Find next hop
      int nextVertexIndex = -1;
      auto weightToNearVertices = graphMatrix[vertexIndex];
      for (int i = 0; i < vertices.size(); ++i) {
        int weightToNearVertex = weightToNearVertices[i];
        if (weightToNearVertex == -1)
          continue;
        if (vertexInfo.second == weightToNearVertex + vertexInfos[i].second)
          nextVertexIndex = i;
      }
      if (nextVertexIndex == -1)
        throw std::runtime_error("Not found next hop on shortest path make.");
      // Add edge
      shortestPath.push_back(Edge{ vertex, vertices[vertexIndex] });
      // Hop
      vertexIndex = nextVertexIndex;
      vertex = vertices[vertexIndex];
      vertexInfo = vertexInfos[vertexIndex];
    } while (vertex != startVertex);

    return std::vector(shortestPath.rbegin(), shortestPath.rend());
}
