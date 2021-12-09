#include "h/graphUtils.h"
#include <algorithm>
#include "h/utils.h"
#include "h/graphTypes.h"
#include "h/WeightedGraph.h"
#include <limits.h>

#include <iostream>
using std::cout, std::endl, std::cin;

using std::string, std::vector;

bool equalUnorderedEdges(Edge e1, Edge e2) {
  return e1[0] == e2[0] && e1[1] == e2[1]
        || e1[0] == e2[1] && e1[1] == e2[0];
}

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
    // Case: same vertex
    if (startVertex == endVertex && findIndex(graph.GetVertices(), startVertex) != -1)
      return vector<Edge>();
    // Exception: negative weight
    auto weights = graph.GetWeights();
    if (findIndex(weights, std::function([](int weight) { return weight < 0; })) != -1)
        throw std::invalid_argument("Failed to make Dijkstra shortest path: graph must not have negative weight.");

    // Init
    auto vertices = graph.GetVertices();
    auto edges = graph.GetEdges();
    int startVertexIndex = findIndex(vertices, startVertex);
    int endVertexIndex = findIndex(vertices, endVertex);
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
    
    // // Printing Graph matrix
    // for (int i = 0; i < vertices.size(); ++i) 
    //   cout << vertices[i] << ' ';
    // cout << endl;
    // for (auto y: graphMatrix) {
    //   for (auto x: y) {
    //     cout << x << " ";
    //   }
    //   cout << endl;
    // }
    
    // Calc total weights to vertices
    int visitedVertexCount = 0;
    Vertex vertex = startVertex;
    int vertexIndex = startVertexIndex;
    vertexInfos[vertexIndex].second = 0;
    do {
      // Stage 1. Update near vertices.
      auto weightToNearVertices = graphMatrix[vertexIndex];
      for (int i = 0; i < vertices.size(); ++i) {
        int weightToNearVertex = weightToNearVertices[i];
        if (weightToNearVertex == -1)
          continue;
        int totalWeightToNearVertex = weightToNearVertex + vertexInfos[vertexIndex].second;
        if (totalWeightToNearVertex < vertexInfos[i].second)
          vertexInfos[i].second = totalWeightToNearVertex;
      }
      vertexInfos[vertexIndex].first = true;
      ++visitedVertexCount;
      if (visitedVertexCount == vertices.size())
        break;

      // Stage 2. Hop next vertex.
      int nextVertexIndex = -1;
      for (int i = 0; i < vertices.size(); ++i) {
        // Skip if visited.
        if (vertexInfos[i].first)
          continue; 
        // Skip if not connected with visited.
        bool nearVisitedVertex = false;
        for (int j = 0; j < vertices.size(); ++j) {
          if (graphMatrix[i][j] != -1 && vertexInfos[j].first) {
            nearVisitedVertex = true;
            break;
          }
        }
        if (!nearVisitedVertex)
          continue;
        // Minimum update.
        if (nextVertexIndex == -1 || vertexInfos[i].second < vertexInfos[nextVertexIndex].second)
          nextVertexIndex = i;
      }
      // Check for graph connectivity.
      if (nextVertexIndex == -1) {
        if (!vertexInfos[endVertexIndex].first) {
          throw std::logic_error(std::string("No path from ").append(1, startVertex).append(" to ").append(1, endVertex).append("."));
        }
        break;
      }
      // Hop
      vertexIndex = nextVertexIndex;
      vertex = vertices[vertexIndex];
    } while (true);

    // // Print vertex infos
    // for (int i = 0; i < vertices.size(); ++i) {
    //   cout << vertices[i] << " " << vertexInfos[i].first << " " << vertexInfos[i].second << endl;
    // }

    // Make shortest path from startVertex to endVertex
    vector<Edge> shortestPath;
    vertex = endVertex;
    vertexIndex = endVertexIndex;
    do {
      // Find next hop
      int nextVertexIndex = -1;
      auto weightToNearVertices = graphMatrix[vertexIndex];
      for (int i = 0; i < vertices.size(); ++i) {
        int weightToNearVertex = weightToNearVertices[i];
        if (weightToNearVertex == -1)
          continue;
        if (vertexInfos[vertexIndex].second == weightToNearVertex + vertexInfos[i].second) {
          nextVertexIndex = i;
          break;
        }
      }
      if (nextVertexIndex == -1)
        throw std::runtime_error("Not found next hop on shortest path make.");
      // Add edge
      Edge edge{ vertex, vertices[nextVertexIndex] };
      int edgeIndex = findIndex(edges, std::function([&edge](Edge e){ return equalUnorderedEdges(e, edge); }));
      shortestPath.push_back(edges[edgeIndex]);
      // Hop
      vertexIndex = nextVertexIndex;
      vertex = vertices[vertexIndex];
    } while (vertex != startVertex);

    return std::vector(shortestPath.rbegin(), shortestPath.rend());
}
