#include "h/utils.h"
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

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

template<typename T>
std::vector<T> intersection(std::vector<T> &v1, std::vector<T> &v2) {
    std::vector<T> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}

template std::vector<char> intersection<char>(std::vector<char> &v1, std::vector<char> &v2);
