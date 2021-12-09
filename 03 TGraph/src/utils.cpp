#include "h/utils.h"
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include "h/graphTypes.h"

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

template<typename T>
int findIndex(const std::vector<T>& vec, std::function<bool(T)> predicate) {
    for (int i = 0; i < vec.size(); ++i) {
        if (predicate(vec[i]))
            return i;
    }
    return -1;
}

template<typename T>
int findIndex(const std::vector<T>& vec, T value) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == value)
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

template int findIndex<Vertex>(const std::vector<Vertex>& vec, Vertex value);
template int findIndex<int>(const std::vector<int>& vec, std::function<bool(int)> predicate);
template int findIndex<Vertex>(const std::vector<Vertex>& vec, std::function<bool(Vertex)> predicate);
template int findIndex<Edge>(const std::vector<Edge>& vec, std::function<bool(Edge)> predicate);
template std::vector<Vertex> intersection<Vertex>(std::vector<Vertex> &v1, std::vector<Vertex> &v2);
