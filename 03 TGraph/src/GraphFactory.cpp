#include "GraphFactory.h"
#include "CompleteGraph.h"


template<typename T>
TGraph* GraphFactory::Create(std::string type, std::initializer_list<T> args) {
    if (type == "complete") {
        return new CompleteGraph(args);
    }
    return nullptr;
};
