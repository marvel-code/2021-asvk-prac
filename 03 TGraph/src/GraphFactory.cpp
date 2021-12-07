#include "h/GraphFactory.h"
#include "h/CompleteGraph.h"


TGraph* GraphFactory::Create(std::string type, std::initializer_list<char> args...) {
    if (type == "complete") {
        return new CompleteGraph(args);
    }
    return nullptr;
};
