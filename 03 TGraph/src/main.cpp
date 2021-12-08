#include <iostream>
#include "h/GraphFactory.h"
#include "h/CompleteGraph.h"
#include "h/SimpleGraph.h"
#include "h/WeightedGraph.h"
#include "h/BipartiteGraph.h"
#include <vector>

using std::cout, std::cin, std::endl;

int main(int argc, char** argv) {
    GraphFactory graphFactory;

    auto cg1 = (CompleteGraph*)graphFactory.Create("complete", { 'A', 'B', 'C', 'D' });
    auto cg2 = (CompleteGraph*)graphFactory.Create("complete", { 'A', 'B', 'C' });
    cout << (*cg1 + *cg2).ToString() << endl;
    cout << (*cg1 - *cg2).ToString() << endl;
    
    auto sg1 = (SimpleGraph*)graphFactory.Create("simple", { "AB", "DE", "BC" });
    auto sg2 = (SimpleGraph*)graphFactory.Create("simple", { "BC", "CD" });
    cout << (*sg1 + *sg2).ToString() << endl;
    cout << (*sg1 - *sg2).ToString() << endl;

    auto bg1 = (BipartiteGraph*)graphFactory.Create("bipartite", { 'A', 'B' }, { 'C', 'D', 'E' });
    auto bg2 = (BipartiteGraph*)graphFactory.Create("bipartite", { 'A', 'B', 'C' }, { 'D', 'E' });
    cout << (*bg1 + *bg2).ToString() << endl;
    cout << (*bg1 - *bg2).ToString() << endl;
    
    auto wg1 = (WeightedGraph*)graphFactory.Create("weighted", { "AB", "BC", "EA" }, { 1, 2, 3 });
    auto wg2 = (WeightedGraph*)graphFactory.Create("weighted", { "BC", "CD", "AB" }, { 1, 5, 3 });
    cout << (*wg1 + *wg2).ToString() << endl;
    cout << (*wg1 - *wg2).ToString() << endl;
    cout << (*wg1 - *sg1).ToString() << endl;
    cout << (*sg1 - *wg1).ToString() << endl;
}
