#pragma once

#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& elements)
{
    os << "{";
    for (size_t currentIndex = 0; currentIndex < elements.size(); ++currentIndex)
    {
        os << elements[currentIndex];
        if (currentIndex != elements.size() - 1)
        {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::map<T, S>& elements)
{
    os << "{";
    for (auto iter = elements.begin(); iter != elements.end(); iter++)
    {
        os << iter->first << " : " << iter->second;
        if ((std::next(iter) != elements.end()))
        {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& elements)
{
    os << "{";
    for (auto it : elements)
    {
        os << it;
        if (it != *elements.rbegin())
        {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

template <class T>
static bool compareVectors(std::vector<T> a, std::vector<T> b)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return (a == b);
}