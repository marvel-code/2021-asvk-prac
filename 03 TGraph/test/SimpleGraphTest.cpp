#include <gtest/gtest.h>
#include "../src/h/utils.h"
#include "../src/h/graphUtils.h"
#include <functional>
#include "../src/h/SimpleGraph.h"

TEST(SimpleGraphTest, Creation) {
    auto a = SimpleGraph();
    auto b = SimpleGraph({ "AB", "BC", "CD" });
    SUCCEED();
}

TEST(SimpleGraphTest, ErrorGeneration) {
    try {
        SimpleGraph({ "Ab" });
        FAIL();
    } catch (std::invalid_argument& ex) {
        SUCCEED();
    }
}

TEST(SimpleGraphTest, GetVertices) {
    SimpleGraph s(std::vector<const char*>{"AB", "BC" });
    std::vector<Vertex> vertices{ 'A', 'B', 'C' };
    for (Vertex v: s.GetVertices()) {
        if (findIndex(vertices, v) == -1)
            FAIL();
    }
    SUCCEED();
}

TEST(SimpleGraphTest, GetEdges) {
    std::vector<Edge> edges{{'A','B'},{'B','C'},{'A','C'}};
    SimpleGraph s(edges);
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

TEST(SimpleGraphTest, ToString) {
    SimpleGraph s(std::vector<const char*>{ "AB", "BC", "CD" });
    EXPECT_EQ("{ AB, BC, CD }", s.ToString());
}

TEST(SimpleGraphTest, Sum) {
    SimpleGraph c1(std::vector<const char*>{ "AB", "BC" });
    SimpleGraph c2(std::vector<const char*>{ "AB", "CF" });
    auto c = c1 + c2;
    EXPECT_EQ("{ CF, BC, AB }", c.ToString());
}

TEST(SimpleGraphTest, Difference) {
    SimpleGraph c1(std::vector<const char*>{ "AB", "BC", "CD" });
    SimpleGraph c2(std::vector<const char*>{ "AB", "BC", "CE" });
    auto c = c1 - c2;
    EXPECT_EQ("{ CD }", c.ToString());
}


