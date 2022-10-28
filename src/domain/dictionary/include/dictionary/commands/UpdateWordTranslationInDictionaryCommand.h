#pragma once

#include <string>

namespace glossary::dictionary
{
class UpdateWordTranslationInDictionaryCommand
{
public:
    virtual ~UpdateWordTranslationInDictionaryCommand() = default;

    virtual void updateWordTranslation(const std::string& dictionaryName, const std::string& englishWord,
                                       const std::string& translation) = 0;
};
}
