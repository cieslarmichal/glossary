#pragma once

#include "gmock/gmock.h"

#include "TranslationRepository.h"

namespace glossary::translation
{

class TranslationRepositoryMock : public TranslationRepository
{
public:
    MOCK_METHOD1(addTranslation, void(Translation));
    MOCK_CONST_METHOD1(getTranslation, std::optional<Translation>(const std::string&));
    MOCK_CONST_METHOD1(containsTranslation, bool(const std::string&));
};
}
