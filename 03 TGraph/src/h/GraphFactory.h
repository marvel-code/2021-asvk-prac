#include "TGraph.h"
#include <string>

class GraphFactory {
public:
    TGraph* Create(std::string type, std::initializer_list<char> vertices);
    TGraph* Create(std::string type, std::initializer_list<const char*> edges);
    TGraph* Create(std::string type, std::initializer_list<const char*> edges, std::initializer_list<int> weights);
    TGraph* Create(std::string type, std::initializer_list<char> vertices1, std::initializer_list<char> vertices2);
};
