
#include <gtest/gtest.h>
#include "../src/h/utils.h"
#include "../src/h/GraphFactory.h"

TEST(UtilsTest, DijkstraShortestPath1) {
    auto wg = WeightedGraph(
        { "AB", "BC", "AC", "CD", "CF", "DF", "AF", "DE", "EZ" }, 
        { 1, 3, 3, 100, 2, 1, 100, 4, 1 }
    );
    auto path = makeDijkstraShortestPath(wg, 'A', 'Z');
    EXPECT_EQ("{ AC, CF, DF, DE, EZ }", makeEdgesString(path));
}

TEST(UtilsTest, DijkstraShortestPath2) {
    auto wg = WeightedGraph(
        { "AB", "BC", "AC", "CD", "CF", "DF", "AF", "DE", "EZ" }, 
        { 1, 3, 3, 1, 2, 1, 1, 4, 1 }
    );
    auto path = makeDijkstraShortestPath(wg, 'A', 'Z');
    EXPECT_EQ("{ AF, DF, DE, EZ }", makeEdgesString(path));
}
