#pragma once

#include <string>

struct WordExistenceInfo
{
    std::string toString() const
    {
        return name + " " + std::to_string(descriptionExists) + "\n";
    }

    bool operator==(const WordExistenceInfo& rhs)
    {
        return (name == rhs.name && descriptionExists == rhs.descriptionExists);
    }

    std::string name;
    bool descriptionExists;
};
