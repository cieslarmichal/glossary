#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionLoader.h"

namespace glossary
{
class WordDescriptionLoaderMock : public WordDescriptionLoader
{
public:
    MOCK_METHOD1(loadWordsDescriptions, void(
                                                const wordDescriptionRepository::EnglishWords&));
};
}