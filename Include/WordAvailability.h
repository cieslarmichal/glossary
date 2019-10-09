#pragma once

#include <string>
#include "EnglishWord.h"

struct WordAvailability
{
    std::string toString() const
    {
        return name + " " + std::to_string(descriptionExists);
    }

    EnglishWord name;
    bool descriptionExists;
};

inline bool operator==(const WordAvailability& lhs, const WordAvailability& rhs)
{
    return (lhs.name == rhs.name && lhs.descriptionExists == rhs.descriptionExists);
}

inline std::ostream& operator<<(std::ostream& os, const WordAvailability& wordAvailability)
{
    os << wordAvailability.toString();
    return os;
}
