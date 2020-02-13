#pragma once

#include "gmock/gmock.h"

#include "translationsDb/TranslationsStorage.h"

namespace translationsDb
{

class TranslationsStorageMock : public TranslationsStorage
{
public:
    MOCK_METHOD1(addTranslation, void(Translation));
    MOCK_CONST_METHOD1(getTranslation,
                       boost::optional<Translation>(const PolishWord&));
    MOCK_CONST_METHOD0(getTranslations, Translations());
    MOCK_CONST_METHOD1(contains, bool(const PolishWord&));
    MOCK_CONST_METHOD0(size, Translations::size_type());
    MOCK_CONST_METHOD0(empty, bool());
    MOCK_CONST_METHOD0(begin, Translations::const_iterator());
    MOCK_CONST_METHOD0(end, Translations::const_iterator());
};
}
