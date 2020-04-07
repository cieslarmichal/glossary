#pragma once

#include "gmock/gmock.h"

#include "TranslationLoader.h"

namespace glossary
{
class TranslationLoaderMock : public TranslationLoader
{
public:
    MOCK_METHOD1(loadMissingTranslations, void(const wordDescriptionRepository::EnglishWords&));
};
}