#pragma once

#include "gmock/gmock.h"

#include "DescriptionParser.h"

class DescriptionParserMock : public DescriptionParser
{
public:
    MOCK_CONST_METHOD1(parse, boost::optional<Description>(const std::vector<std::string>&));
};
