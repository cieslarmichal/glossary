#pragma once

#include "gmock/gmock.h"

#include "UpdateWordTranslationInDictionaryCommand.h"

namespace glossary::dictionary
{
class UpdateWordTranslationInDictionaryCommandMock : public UpdateWordTranslationInDictionaryCommand
{
public:
    MOCK_METHOD(void, updateWordTranslation,
                (const std::string& dictionaryName, const std::string& englishWord, const std::string& translation),
                ());
};
}
