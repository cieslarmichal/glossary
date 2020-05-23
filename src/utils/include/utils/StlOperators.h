#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <vector>

template <typename Iterator>
std::ostream& printRange(std::ostream& os, Iterator begin, Iterator end)
{
    os << "{";
    if (begin != end)
    {
        os << *begin;
        for (auto it = std::next(begin); it != end; ++it)
        {
            os << ", " << *it;
        }
    }
    return os << "}";
}

namespace std
{

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    return ::printRange(os, v.begin(), v.end());
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::map<T, S>& m)
{
    os << "{";
    if (not m.empty())
    {
        os << "[" << m.begin()->first << "->" << m.begin()->second << "]";
        for (auto it = std::next(m.begin()); it != m.end(); ++it)
        {
            os << ", "
               << "[" << it->first << "->" << it->second << "]";
        }
    }
    return os << "}";
}
}

template <class T>
static bool compareVectors(std::vector<T> a, std::vector<T> b)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return (a == b);
}

template <typename T>
std::string toStringArray(const std::vector<T>& v)
{
    std::stringstream ss;
    ss << "[";
    if (v.begin() != v.end())
    {
        ss << *v.begin();
        for (auto it = std::next(v.begin()); it != v.end(); ++it)
        {
            ss << ", " << *it;
        }
    }
    ss << "]";
    return ss.str();
}

template <typename T>
std::string toStringSeparated(const std::vector<T>& v)
{
    std::stringstream ss;
    ss << "{\n";
    if (v.begin() != v.end())
    {
        ss << *v.begin();
        for (auto it = std::next(v.begin()); it != v.end(); ++it)
        {
            ss << "\n" << *it;
        }
    }
    ss << "}";
    return ss.str();
}