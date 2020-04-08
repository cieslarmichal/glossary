#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionRetrieverService.h"

namespace glossary::wordDescriptionService
{
class WordDescriptionRetrieverServiceMock : public WordDescriptionRetrieverService
{
public:
    MOCK_METHOD1(retrieveWordDescription,
                 wordDescriptionRepository::WordDescription(const wordDescriptionRepository::EnglishWord&));
};
}