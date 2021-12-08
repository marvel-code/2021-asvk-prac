#include "h/utils.h"
#include <string>
#include <vector>
#include <functional>

std::string charJoin(const std::vector<char>& vec, const std::string& splitter) {
    if (vec.size() == 0)
        return "";
    std::string result{ vec[0] };
    for (int i = 1; i < vec.size(); ++i) {
        result.append(splitter).push_back(vec[i]);
    }
    return result;
}

std::string stringJoin(const std::vector<std::string>& vec, const std::string& splitter) {
    if (vec.size() == 0)
        return "";
    std::string result{ vec[0] };
    for (int i = 1; i < vec.size(); ++i) {
        result.append(splitter).append(vec[i]);
    }
    return result;
}

int findIndex(const std::vector<std::vector<char>>& vec, std::function<bool(std::vector<char>)> predicate) {
    for (int i = 0; i < vec.size(); ++i) {
        if (predicate(vec[i]))
            return i;
    }
    return -1;
}
