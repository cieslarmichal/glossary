#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionService.h"

namespace glossary::wordDescriptionService
{
class WordDescriptionServiceMock : public WordDescriptionService
{
public:
    MOCK_METHOD(wordDescriptionRepository::WordDescription, retrieveWordDescription,
                (const wordDescriptionRepository::EnglishWord&), (noexcept));
    MOCK_METHOD(boost::optional<wordDescriptionRepository::WordDescription>, downloadWordDescription,
                (const wordDescriptionRepository::EnglishWord&), ());
    MOCK_METHOD(WordsApiStatus, connectionToWordsApiAvailable, (), (const));
    MOCK_METHOD(void, updateApiKeyLocation, (const std::string& apiKeyLocation), ());
};
}