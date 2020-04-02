#pragma once

#include <map>
#include <ostream>

namespace glossary::dictionaryRepository
{
enum class ValidationResult
{
    Invalid,
    Valid
};

inline std::ostream& operator<<(std::ostream& os, const ValidationResult& result)
{
    std::map<ValidationResult, std::string> resultsStringMapping{{ValidationResult::Invalid, "Invalid"},
                                                                 {ValidationResult::Valid, "Valid"}};
    return os << resultsStringMapping.at(result);
}
}