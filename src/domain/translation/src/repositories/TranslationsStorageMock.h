#pragma once

#include "gmock/gmock.h"

#include "TranslationsStorage.h"

namespace glossary::translation
{
class TranslationsStorageMock : public TranslationsStorage
{
public:
    MOCK_METHOD1(addTranslation, void(Translation));
    MOCK_CONST_METHOD1(getTranslation, std::optional<Translation>(const std::string&));
    MOCK_CONST_METHOD0(getTranslations, std::vector<Translation>());
    MOCK_CONST_METHOD1(contains, bool(const std::string&));
    MOCK_CONST_METHOD0(size, std::vector<Translation>::size_type());
    MOCK_CONST_METHOD0(empty, bool());
};
}
