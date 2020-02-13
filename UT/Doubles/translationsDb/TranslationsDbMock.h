#pragma once

#include "gmock/gmock.h"

#include "translationsDb/TranslationsDb.h"

namespace translationsDb
{

class TranslationsDbMock : public TranslationsDb
{
public:
    MOCK_METHOD1(addTranslation, void(Translation));
    MOCK_CONST_METHOD1(getTranslation,
                       boost::optional<Translation>(const PolishWord&));
    MOCK_CONST_METHOD0(getTranslations, Translations());
};
}
