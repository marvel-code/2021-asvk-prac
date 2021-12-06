#include "TGraph.h"
#include "CompleteGraph.h"
#include <string>

class GraphFactory {
public:
    TGraph* Create(std::string type);
};
