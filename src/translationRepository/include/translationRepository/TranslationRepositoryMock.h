#pragma once

#include "gmock/gmock.h"

#include "TranslationRepository.h"

namespace translationRepository
{

class TranslationRepositoryMock : public TranslationRepository
{
public:
    MOCK_METHOD1(addTranslation, void(Translation));
    MOCK_CONST_METHOD1(getTranslation, boost::optional<Translation>(const SourceText&));
    MOCK_CONST_METHOD0(getTranslations, Translations());
};
}
