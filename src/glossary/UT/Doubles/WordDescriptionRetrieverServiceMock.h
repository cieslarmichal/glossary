#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionRetrieverService.h"

class WordDescriptionRetrieverServiceMock : public WordDescriptionRetrieverService
{
public:
    MOCK_METHOD1(retrieveWordDescription, boost::optional<wordDescriptionRepository::WordDescription>(
                                              const wordDescriptionRepository::EnglishWord&));
};
