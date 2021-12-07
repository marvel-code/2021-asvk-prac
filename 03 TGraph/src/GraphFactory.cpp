#include "h/GraphFactory.h"
#include "h/CompleteGraph.h"
#include "h/SimpleGraph.h"
#include "h/WeightedGraph.h"


TGraph* GraphFactory::Create(std::string type, std::initializer_list<char> vertices) {
    if (type == "complete") {
        return new CompleteGraph(vertices);
    }
    return nullptr;
};

TGraph* GraphFactory::Create(std::string type, std::initializer_list<const char*> edges) {
    if (type == "simple") {
        return new SimpleGraph(edges);
    }
    return nullptr;
};

TGraph* GraphFactory::Create(std::string type, std::initializer_list<const char*> edges, std::initializer_list<int> weights) {
    if (type == "weighted") {
        return new WeightedGraph(edges, weights);
    }
    return nullptr;
};

// TGraph* GraphFactory::Create(std::string type, std::initializer_list<char> vertices) {
//     if (type == "complete") {
//         return new CompleteGraph(arg1);
//     }
//     return nullptr;
// };

