#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionService.h"

class WordDescriptionServiceMock : public WordDescriptionService
{
public:
    MOCK_METHOD1(getWordDescription,
                 boost::optional<wordsDescriptionsDb::WordDescription>(
                     const wordsDescriptionsDb::EnglishWord&));
};
