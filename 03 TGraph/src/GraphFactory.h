#include "TGraph.h"
#include "CompleteGraph.h"
#include <string>

class GraphFactory {
public:
    template<typename T>
    TGraph* Create(std::string type, std::initializer_list<T> args);
};
