#include "GraphFactory.h"
#include "CompleteGraph.h"

TGraph* GraphFactory::Create(std::string type) {
    if (type == "complete") {
        return new CompleteGraph();
    }
    return nullptr;
};
