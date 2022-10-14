#pragma once

#include <string>
#include <vector>

namespace glossary::dictionary
{
class DictionaryObserver
{
public:
    virtual ~DictionaryObserver() = default;

    virtual void update(const std::vector<std::string>&) = 0;
};
}