#pragma once

#include "gmock/gmock.h"

#include "TranslationsStorage.h"

namespace glossary::translationRepository
{
class TranslationsStorageMock : public TranslationsStorage
{
public:
    MOCK_METHOD1(addTranslation, void(Translation));
    MOCK_CONST_METHOD1(getTranslation, boost::optional<Translation>(const SourceText&));
    MOCK_CONST_METHOD0(getTranslations, Translations());
    MOCK_CONST_METHOD1(contains, bool(const SourceText&));
    MOCK_CONST_METHOD0(size, Translations::size_type());
    MOCK_CONST_METHOD0(empty, bool());
};
}
