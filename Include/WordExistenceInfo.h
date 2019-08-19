#pragma once

#include <string>
#include "boost/optional.hpp"

struct WordExistenceInfo
{
    std::string toString() const
    {
        if(!name)
        {
            throw "no name";
        }
        return *name + " " + std::to_string(descriptionExists) + "\n";
    }

    boost::optional<std::string> name;
    bool descriptionExists;
};