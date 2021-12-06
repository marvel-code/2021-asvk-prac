#include "utils.h"
#include <string>
#include <vector>

std::string stringJoin(const std::vector<char>& vec, const std::string& splitter) {
    if (vec.size() == 0)
        return "";
    std::string result{ vec[0] };
    for (int i = 1; i < vec.size(); ++i) {
        result.append(splitter).push_back(vec[i]);
    }
    return result;
}
