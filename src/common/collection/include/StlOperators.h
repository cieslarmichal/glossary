#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <vector>

template <typename Iterator>
std::ostream& printRange(std::ostream& os, Iterator begin, Iterator end)
{
    os << "[";
    if (begin != end)
    {
        os << *begin;
        for (auto it = std::next(begin); it != end; ++it)
        {
            os << "," << *it;
        }
    }
    return os << "]";
}

namespace std
{

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    return ::printRange(os, v.begin(), v.end());
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<std::vector<T>>& vOpt)
{
    if (vOpt)
    {
        return os << *vOpt;
    }

    return os << "none";
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

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::optional<std::map<T, S>>& mOpt)
{
    if (mOpt)
    {
        return os << *mOpt;
    }
    
    return os << "none";
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
