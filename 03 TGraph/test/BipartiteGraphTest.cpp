#include <gtest/gtest.h>
#include "../src/h/utils.h"
#include "../src/h/graphUtils.h"
#include <functional>
#include "../src/h/BipartiteGraph.h"

TEST(BipartiteGraphTest, Creation) {
    auto a = BipartiteGraph();
    auto b = BipartiteGraph({ 'A', 'B'}, { 'C' });
    EXPECT_TRUE(true);
}

TEST(BipartiteGraphTest, ErrorGeneration) {
    try {
        BipartiteGraph({ 'A', 'B' }, { 'B', 'C' });
        FAIL();
    } catch (std::invalid_argument& ex) {
        SUCCEED();
    }
}

TEST(BipartiteGraphTest, GetVertices) {
    std::vector<Vertex> vertices{ 'A', 'B', 'C', 'D' };
    BipartiteGraph c({ 'A', 'B' }, { 'C', 'D' });
    for (Vertex v: c.GetVertices()) {
        if (findIndex(vertices, v) == -1)
            FAIL();
    }
    SUCCEED();
}

TEST(BipartiteGraphTest, GetEdges) {
    std::vector<Vertex> vertices{ 'A', 'B', 'C' };
    std::vector<Edge> edges{{'A','C'},{'B','C'}};
    BipartiteGraph c({'A', 'B'}, { 'C' });
    for (Edge e: c.GetEdges()) {
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

TEST(BipartiteGraphTest, ToString) {
    BipartiteGraph c({ 'A', 'B' }, { 'C' });
    EXPECT_EQ("Top: { A, B }. Bottom: { C }.", c.ToString());
}

TEST(BipartiteGraphTest, Sum) {
    BipartiteGraph c1({ 'A', 'B' }, { 'C' });
    BipartiteGraph c2({ 'A', 'E' }, { 'D' });
    auto c = c1 + c2;
    EXPECT_EQ("Top: { A, B, E }. Bottom: { C, D }.", c.ToString());
}

TEST(BipartiteGraphTest, Difference) {
    BipartiteGraph c1({ 'A', 'B' }, { 'C' });
    BipartiteGraph c2({ 'D', 'B' }, { 'E' });
    auto c = c1 - c2;
    EXPECT_EQ("Top: { A }. Bottom: { C }.", c.ToString());
}


