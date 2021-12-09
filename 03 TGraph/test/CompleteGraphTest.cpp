#include <gtest/gtest.h>
#include "../src/h/utils.h"
#include "../src/h/graphUtils.h"
#include <functional>
#include "../src/h/CompleteGraph.h"

TEST(CompleteGraphTest, Creation) {
    auto a = CompleteGraph();
    auto b = CompleteGraph({ 'A', 'B', 'C' });
    EXPECT_TRUE(true);
}

TEST(CompleteGraphTest, ErrorGeneration) {
    try {
        CompleteGraph({ 'a' });
        FAIL();
    } catch (std::invalid_argument& ex) {
        SUCCEED();
    }
}

TEST(CompleteGraphTest, GetVertices) {
    std::vector<Vertex> vertices{ 'A', 'B', 'C', 'D' };
    CompleteGraph c(vertices);
    for (Vertex v: c.GetVertices()) {
        if (findIndex(vertices, v) == -1)
            FAIL();
    }
    SUCCEED();
}

TEST(CompleteGraphTest, GetEdges) {
    std::vector<Vertex> vertices{ 'A', 'B', 'C' };
    std::vector<Edge> edges{{'A','B'},{'B','C'},{'A','C'}};
    CompleteGraph c(vertices);
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

TEST(CompleteGraphTest, ToString) {
    CompleteGraph c({ 'A', 'B', 'C' });
    EXPECT_EQ("{ A, B, C }", c.ToString());
}

TEST(CompleteGraphTest, Sum) {
    CompleteGraph c1({ 'A', 'B' });
    CompleteGraph c2({ 'C', 'D' });
    auto c = c1 + c2;
    EXPECT_EQ("{ A, B, C, D }", c.ToString());
}

TEST(CompleteGraphTest, Difference) {
    CompleteGraph c1({ 'A', 'B', 'C' });
    CompleteGraph c2({ 'A', 'D', 'B' });
    auto c = c1 - c2;
    EXPECT_EQ("{ C }", c.ToString());
}


