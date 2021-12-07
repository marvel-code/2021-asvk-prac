#include <iostream>
#include "h/GraphFactory.h"
#include "h/SimpleGraph.h"
#include <vector>

using std::cout, std::cin, std::endl;

int main(int argc, char** argv) {
    GraphFactory graphFactory;

    auto cg1 = (CompleteGraph*)graphFactory.Create("complete", { 'A', 'B', 'C', 'D' });
    auto cg2 = (CompleteGraph*)graphFactory.Create("complete", { 'A', 'B', 'C' });
    cout << (*cg1 + *cg2).ToString() << endl;
    cout << (*cg1 - *cg2).ToString() << endl;
}
