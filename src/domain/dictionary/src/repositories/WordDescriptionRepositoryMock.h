#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionRepository.h"

namespace glossary::dictionary
{
class WordDescriptionRepositoryMock : public WordDescriptionRepository
{
public:
    MOCK_METHOD1(addWordDescription, void(const WordDescription&));
    MOCK_CONST_METHOD1(getWordDescription, std::optional<WordDescription>(const std::string&));
    MOCK_CONST_METHOD1(contains, bool(const std::string&));
};

}
