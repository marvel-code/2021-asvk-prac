#include <string>
#include <vector>
#include <functional>

std::string charJoin(const std::vector<char>& vec, const std::string& splitter = " ");

std::string stringJoin(const std::vector<std::string>& vec, const std::string& splitter = " ");

template<typename T>
int findIndex(const std::vector<T>& vec, T value);

template<typename T>
int findIndex(const std::vector<T>& vec, std::function<bool(T)> predicate);

template<typename T>
std::vector<T> intersection(std::vector<T> &v1, std::vector<T> &v2);
