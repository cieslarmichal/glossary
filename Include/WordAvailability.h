#pragma once

#include <string>
#include "EnglishWord.h"

struct WordAvailability
{
    std::string toString() const
    {
        return name + " " + std::to_string(descriptionExists) + "\n";
    }

    bool operator==(const WordAvailability& rhs)
    {
        return (name == rhs.name && descriptionExists == rhs.descriptionExists);
    }

    EnglishWord name;
    bool descriptionExists;
};
