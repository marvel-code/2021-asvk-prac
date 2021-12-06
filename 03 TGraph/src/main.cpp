#include <iostream>
#include "GraphFactory.h"
#include <vector>

using std::cout, std::cin, std::endl;

int main(int argc, char** argv) {
    GraphFactory graphFactory;

    auto cg = graphFactory.Create("complete", { 'A', 'B', 'C' });
}
