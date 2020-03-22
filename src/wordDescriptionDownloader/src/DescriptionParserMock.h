#pragma once

#include "gmock/gmock.h"

#include "DescriptionParser.h"

namespace wordDescriptionDownloader
{
class DescriptionParserMock : public DescriptionParser
{
public:
    MOCK_CONST_METHOD1(parse,
                       boost::optional<wordDescriptionRepository::Description>(const std::vector<std::string>&));
};
}