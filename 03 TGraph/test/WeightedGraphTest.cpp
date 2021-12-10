#include <gtest/gtest.h>
#include "../src/h/utils.h"
#include "../src/h/graphUtils.h"
#include <functional>
#include "../src/h/WeightedGraph.h"

TEST(WeightedGraphTest, Creation) {
    auto a = WeightedGraph();
    auto b = WeightedGraph({ "AB", "BC", "CD" }, std::vector<int>{ 1, 2, 3 });
    SUCCEED();
}

TEST(WeightedGraphTest, ErrorGeneration) {
    try {
        WeightedGraph s(std::vector<const char*>{ "AB", "CD" }, std::vector<int>{ 1 });
        FAIL();
    } catch (std::invalid_argument& ex) {
        SUCCEED();
    }
}

TEST(WeightedGraphTest, GetVertices) {
    WeightedGraph s(std::vector<const char*>{ "AB", "BC" }, std::vector<int>{ 1, 2 });
    std::vector<Vertex> vertices{ 'A', 'B', 'C' };
    for (Vertex v: s.GetVertices()) {
        if (findIndex(vertices, v) == -1)
            FAIL();
    }
    SUCCEED();
}

TEST(WeightedGraphTest, GetEdges) {
    std::vector<Edge> edges{{'A','B'},{'B','C'},{'A','C'}};
    WeightedGraph s(edges, std::vector<int>{ 1, 2, 3 });
    for (Edge e: s.GetEdges()) {
        bool ok = false;
        for (Edge edge: edges) {
            if (equalUnorderedEdges(e, edge)) {
                ok = true;
                break;
            }
        }
        if (!ok)
            FAIL();
    }
    SUCCEED();
}

TEST(WeightedGraphTest, ToString) {
    WeightedGraph s(std::vector<const char*>{ "AB", "BC", "CD" }, std::vector<int>{ 1, 2, 3 });
    EXPECT_EQ("{ AB:1, BC:2, CD:3 }", s.ToString());
}

TEST(WeightedGraphTest, Sum) {
    WeightedGraph c1(std::vector<const char*>{ "AB", "BC" }, std::vector<int>{ 2, 2 });
    WeightedGraph c2(std::vector<const char*>{ "AB", "CF" }, std::vector<int>{ 1, 2 });
    auto c = c1 + c2;
    EXPECT_EQ("{ CF:2, BC:2, AB:1 }", c.ToString());
}

TEST(WeightedGraphTest, Difference) {
    WeightedGraph c1(std::vector<const char*>{ "AB", "BC", "CD" }, std::vector<int>{ 1, 2, 3 });
    WeightedGraph c2(std::vector<const char*>{ "AB", "BC", "CE" }, std::vector<int>{ 1, 2, 3 });
    auto c = c1 - c2;
    EXPECT_EQ("{ CD:3 }", c.ToString());
}


