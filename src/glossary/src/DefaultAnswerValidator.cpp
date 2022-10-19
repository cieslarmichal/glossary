#include "DefaultAnswerValidator.h"

#include "boost/algorithm/string.hpp"

#include "collection/StringHelper.h"

namespace glossary
{
bool DefaultAnswerValidator::validateAnswer(const std::string& userInput,
                                            const std::string& expectedAnswer) const
{
    return common::getLowerCases(userInput) == common::getLowerCases(expectedAnswer);
}

}