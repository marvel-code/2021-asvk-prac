#include "TGraph.h"
#include "CompleteGraph.h"
#include <string>

class GraphFactory {
public:
    TGraph* Create(std::string type, std::initializer_list<char> vertices);
    TGraph* Create(std::string type, std::initializer_list<const char*> edges);
    // TGraph* Create(std::string type, std::initializer_list<char> vertices, std::initializer_list<char16_t> edges);
    // TGraph* Create(std::string type, std::initializer_list<char> vertices, std::initializer_list<int> weights);
};
