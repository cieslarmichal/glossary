#include "DefaultAnswerValidator.h"

#include "boost/algorithm/string.hpp"

#include "utils/StringHelper.h"

namespace glossary
{
bool DefaultAnswerValidator::validateAnswer(const std::string& userInput,
                                            const std::string& expectedAnswer) const
{
    return utils::getLowerCases(userInput) == utils::getLowerCases(expectedAnswer);
}

}